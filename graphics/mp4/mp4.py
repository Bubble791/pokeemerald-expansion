#!/usr/bin/env python3
"""
MP4转GBA帧序列工具（修正透明色问题）
功能：提取MP4帧 → 调整尺寸 → 256色索引（第一色固定为纯黑色，不被使用）
"""

import cv2
import os
from PIL import Image
import numpy as np
from pathlib import Path

def convert_to_indexed_with_transparent_black(image, color_count=256):
    """
    转换为索引颜色，确保第一色(0)为纯黑色且不被图像使用
    
    参数:
        image: PIL RGB图像
        color_count: 目标颜色数量
    
    返回:
        indexed_image: 索引颜色图像（第一色为纯黑且未使用）
    """
    # 1. 转换为RGB模式确保处理正确
    if image.mode != 'RGB':
        rgb_image = image.convert('RGB')
    else:
        rgb_image = image
    
    # 2. 转换为索引颜色（使用color_count-1个颜色，留出0号位置）
    temp_indexed = rgb_image.convert(
        'P', 
        palette=Image.ADAPTIVE, 
        colors=color_count-1,  # 少1个颜色，留出0号位置
        dither=Image.NONE
    )
    
    # 3. 获取原始调色板数据
    palette = temp_indexed.getpalette()
    if palette is None:
        # 如果无法获取调色板，回退到简单转换
        return rgb_image.convert('P', palette=Image.ADAPTIVE, colors=color_count)
    
    # 4. 创建新调色板，第一色为纯黑色(0,0,0)
    new_palette = [0] * (color_count * 3)  # 初始全黑
    
    # 第一色(0号)保持为纯黑色
    new_palette[0] = 0    # R
    new_palette[1] = 0    # G
    new_palette[2] = 0    # B
    
    # 将原始调色板复制到1号色及之后的位置
    for i in range(len(palette)):
        new_palette[i + 3] = palette[i]  # 从第3个位置开始（跳过第一个颜色的RGB）
    
    # 5. 调整像素索引：将所有像素索引+1，让出0号位置
    indexed_data = bytearray(temp_indexed.tobytes())
    for i in range(len(indexed_data)):
        if indexed_data[i] < color_count - 1:  # 确保在范围内
            indexed_data[i] += 1  # 索引+1，跳过0号黑色
    
    # 6. 创建新图像并应用调色板
    indexed_image = Image.frombytes('P', temp_indexed.size, bytes(indexed_data))
    indexed_image.putpalette(new_palette)
    
    # 7. 验证：确保图像中确实没有使用0号颜色
    unique_colors = set(indexed_data)
    if 0 in unique_colors:
        print("警告：图像中仍在使用0号黑色，重新处理...")
        # 如果还有0号色，将其替换为1号色
        for i in range(len(indexed_data)):
            if indexed_data[i] == 0:
                indexed_data[i] = 1
        indexed_image = Image.frombytes('P', temp_indexed.size, bytes(indexed_data))
        indexed_image.putpalette(new_palette)
    
    return indexed_image

def extract_frames_from_mp4(video_path, target_fps, output_size, color_count=256):
    """
    从MP4提取帧并处理为GBA可用格式（修正透明色）
    """
    print(f"处理视频: {Path(video_path).name}")
    print(f"目标: {target_fps} FPS, 尺寸: {output_size}, 颜色: {color_count}色")
    print(f"注意：第一色(0号)固定为纯黑色且不被图像使用（GBA透明色）")
    
    # 创建输出目录
    base_name = Path(video_path).stem
    output_dir = Path(f"{base_name}_frames")
    indexed_dir = output_dir / "indexed"
    indexed_dir.mkdir(parents=True, exist_ok=True)
    
    # 打开视频文件
    cap = cv2.VideoCapture(video_path)
    if not cap.isOpened():
        print("✗ 无法打开视频文件")
        return 0
    
    # 获取视频信息
    original_fps = cap.get(cv2.CAP_PROP_FPS)
    total_frames = int(cap.get(cv2.CAP_PROP_FRAME_COUNT))
    frame_interval = max(1, int(original_fps / target_fps))
    
    print(f"视频: {original_fps:.1f} FPS, {total_frames}帧")
    print(f"帧间隔: {frame_interval}, 预计提取: {int(total_frames/frame_interval)}帧")
    print("-" * 50)
    
    frame_count = 0
    processed_count = 0
    extracted_frames = []
    
    while True:
        ret, frame = cap.read()
        if not ret:
            break
        
        # 按间隔提取帧
        if frame_count % frame_interval == 0:
            # 1. BGR → RGB
            frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            
            # 2. 转换为PIL图像
            pil_img = Image.fromarray(frame_rgb)
            
            # 3. 调整尺寸
            if pil_img.size != output_size:
                pil_img = pil_img.resize(output_size, Image.Resampling.LANCZOS)
            
            # 4. 转换为RGB（确保颜色正确）
            rgb_img = pil_img.convert('RGB')
            
            # 5. 转换为索引颜色（第一色为纯黑且不被使用）
            indexed_img = convert_to_indexed_with_transparent_black(rgb_img, color_count)
            
            # 6. 验证第一色确实没有被使用
            indexed_data = bytearray(indexed_img.tobytes())
            unique_colors = set(indexed_data)
            
            if 0 in unique_colors:
                print(f"警告: 第{processed_count}帧仍在使用0号黑色，强制修正...")
                # 将所有0号色替换为1号色
                for i in range(len(indexed_data)):
                    if indexed_data[i] == 0:
                        indexed_data[i] = 1
                indexed_img = Image.frombytes('P', indexed_img.size, bytes(indexed_data))
                indexed_img.putpalette(indexed_img.getpalette())
            
            # 7. 保存帧
            frame_filename = f"frame_{processed_count:04d}.png"
            frame_path = indexed_dir / frame_filename
            indexed_img.save(frame_path, 'PNG')
            
            # 8. 记录验证信息
            final_data = bytearray(indexed_img.tobytes())
            final_colors = set(final_data)
            
            extracted_frames.append({
                'index': processed_count,
                'filename': frame_filename,
                'uses_black': 0 in final_colors,
                'color_count': len(final_colors),
                'original_frame': frame_count,
                'time': frame_count / original_fps
            })
            
            if 0 in final_colors:
                print(f"错误: 第{processed_count}帧的0号色仍被使用!")
            
            processed_count += 1
            
            # 显示进度
            if processed_count % 10 == 0:
                progress = (frame_count / total_frames) * 100
                print(f"进度: {processed_count}帧 ({progress:.1f}%)")
        
        frame_count += 1
    
    cap.release()
    
    # 验证所有帧的第一色都没有被使用
    black_used_count = sum(1 for f in extracted_frames if f['uses_black'])
    if black_used_count > 0:
        print(f"警告: {black_used_count}帧仍然在使用0号黑色（透明色）")
    else:
        print("✓ 所有帧的第一色(0号)均为未使用的纯黑色（GBA透明色）")
    
    # 生成头文件
    generate_gba_header(output_dir, base_name, extracted_frames, {
        'video_path': video_path,
        'original_fps': original_fps,
        'target_fps': target_fps,
        'output_size': output_size,
        'color_count': color_count,
        'total_frames': processed_count,
        'black_unused': black_used_count == 0
    })
    
    return processed_count

def generate_gba_header(output_dir, base_name, frames, video_info):
    """生成GBA头文件"""
    # 创建序列数组
    sequence_array = f"static const u16 s{base_name}_FRAMES[] = {{  // 帧文件索引\n"
    for i in range(0, len(frames), 16):
        indices = [f"{i:3d}" for i in range(i, min(i+16, len(frames)))]
        sequence_array += "    " + ", ".join(indices) + ",\n"
    sequence_array = sequence_array.rstrip(",\n") + "\n};"
    
    # 创建调色板信息（固定第一色为黑色）
    palette_info = f"""
// 调色板信息：第一色(0)为纯黑色(0,0,0) - GBA透明色
// 实际使用颜色：{video_info['color_count']-1}色（从1号色开始）
#define {base_name.upper()}_PALETTE_SIZE {video_info['color_count']}
#define {base_name.upper()}_USABLE_COLORS {video_info['color_count']-1}
#define {base_name.upper()}_TRANSPARENT_COLOR 0  // 纯黑色，透明
    
// 注意：图像中不使用0号颜色，所有像素使用1-{video_info['color_count']-1}号颜色
"""
    
    header_content = f"""// {base_name} - GBA视频帧数据
// 自动生成，已修复透明色问题
// 帧数: {len(frames)}
// 尺寸: {video_info['output_size'][0]}x{video_info['output_size'][1]}
// 色板: {video_info['color_count']}色（第一色为透明黑）
// 透明色处理: {'✓ 正确' if video_info['black_unused'] else '✗ 有问题'}

#ifndef _{base_name.upper()}_H_
#define _{base_name.upper()}_H_

#include <gba_types.h>

// 帧数量
#define {base_name.upper()}_FRAME_COUNT {len(frames)}

// 帧序列（按顺序）
{sequence_array}

{palette_info}

// 重要提示：
// 1. 所有图像的第一色(0号)是纯黑色(0,0,0)，在GBA中作为透明色
// 2. 图像中实际只使用1-{video_info['color_count']-1}号颜色
// 3. 加载调色板时，确保0号色保持为(0,0,0)

#endif // _{base_name.upper()}_H_
"""
    
    header_path = output_dir / f"{base_name}.h"
    with open(header_path, 'w', encoding='utf-8') as f:
        f.write(header_content)
    
    print(f"✓ 生成GBA头文件: {header_path}")

def main():
    print("=" * 60)
    print("MP4转GBA工具（修正透明色版）")
    print("重要：第一色(0号)固定为纯黑色且不被图像使用")
    print("=" * 60)
    
    # 输入参数
    video_path = input("MP4文件路径: ").strip()
    if not Path(video_path).exists():
        print("文件不存在"); return
    
    try:
        target_fps = float(input("提取帧率 (FPS): ").strip())
        if not 0.1 <= target_fps <= 60:
            print("帧率需0.1-60"); return
    except:
        print("输入无效"); return
    
    size_input = input("输出尺寸 (宽x高, 默认240x160): ").strip()
    if 'x' in size_input:
        try:
            w, h = map(int, size_input.lower().split('x'))
            output_size = (w, h)
        except:
            output_size = (240, 160)
    else:
        output_size = (240, 160)
    
    color_input = input("颜色数量 (16/256, 默认256): ").strip()
    color_count = 256
    if color_input in ['16', '256']:
        color_count = int(color_input)
    
    print(f"\n开始处理...")
    print(f"尺寸: {output_size[0]}x{output_size[1]}")
    print(f"颜色: {color_count}色（实际使用{color_count-1}色，0号透明）")
    
    frame_count = extract_frames_from_mp4(
        video_path=video_path,
        target_fps=target_fps,
        output_size=output_size,
        color_count=color_count
    )
    
    if frame_count > 0:
        print(f"\n✓ 完成: {frame_count}帧")
        print(f"输出: {Path(video_path).stem}_frames/indexed/")
        print(f"头文件: {Path(video_path).stem}_frames/{Path(video_path).stem}.h")

if __name__ == "__main__":
    try:
        import cv2
        from PIL import Image
    except ImportError:
        print("请安装: pip install opencv-python pillow")
        exit(1)
    
    main()