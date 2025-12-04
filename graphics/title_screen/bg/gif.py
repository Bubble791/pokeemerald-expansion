#!/usr/bin/env python3
"""
GIF转GBA动画工具 - 精简版
功能：提取GIF → 去重 → 索引色转换（首色固定为黑色） → 生成GBA/C头文件
"""

from PIL import Image
import os
import hashlib
import json
from pathlib import Path

def extract_and_deduplicate_gif(gif_path):
    """
    提取GIF并去除重复帧
    返回: (去重后的帧列表, 播放序列, 帧时长列表)
    """
    print(f"处理GIF: {Path(gif_path).name}")
    
    try:
        gif = Image.open(gif_path)
        all_frames = []
        all_durations = []
        
        print("提取原始帧...")
        frame_count = 0
        
        while True:
            try:
                frame = gif.copy()
                if frame.mode != 'RGBA':
                    frame = frame.convert('RGBA')
                
                all_frames.append(frame)
                all_durations.append(gif.info.get('duration', 100))
                
                frame_count += 1
                if frame_count % 10 == 0:
                    print(f"  已提取 {frame_count} 帧...")
                
                gif.seek(gif.tell() + 1)
                
            except EOFError:
                break
        
        print(f"✓ 提取 {len(all_frames)} 帧")
        
    except Exception as e:
        print(f"✗ 打开GIF失败: {e}")
        return None, None, None
    
    # 去重
    print("去重处理...")
    frame_hashes = {}
    unique_frames = []
    unique_durations = []
    frame_sequence = []
    
    for i, (frame, duration) in enumerate(zip(all_frames, all_durations)):
        img_byte_arr = hashlib.md5(frame.tobytes()).hexdigest()
        
        if img_byte_arr in frame_hashes:
            unique_index = frame_hashes[img_byte_arr]
            frame_sequence.append(unique_index)
        else:
            unique_index = len(unique_frames)
            frame_hashes[img_byte_arr] = unique_index
            unique_frames.append(frame)
            unique_durations.append(duration)
            frame_sequence.append(unique_index)
    
    print(f"✓ 去重完成: {len(all_frames)} → {len(unique_frames)} 帧")
    return unique_frames, frame_sequence, unique_durations

def convert_to_indexed_with_black_first(image, color_count):
    """
    转换为索引颜色，确保第一色为纯黑色(#000000)
    
    参数:
        image: PIL图像 (RGBA模式)
        color_count: 目标颜色数量
    
    返回:
        indexed_image: 索引颜色图像
    """
    # 1. 处理透明度：透明区域转换为白色，以便后续处理
    if image.mode == 'RGBA':
        # 创建白色背景
        background = Image.new('RGB', image.size, (255, 255, 255))
        # 如果有透明度通道，使用它作为蒙版
        if image.getchannel('A').getextrema() != (255, 255):
            background.paste(image.convert('RGB'), mask=image.split()[3])
        else:
            background.paste(image.convert('RGB'))
        rgb_image = background
    else:
        rgb_image = image.convert('RGB')
    
    # 2. 转换为索引颜色（比目标少1色，因为要留位置给黑色）
    temp_indexed = rgb_image.convert(
        'P', 
        palette=Image.ADAPTIVE, 
        colors=color_count-1,  # 先使用少一色
        dither=Image.NONE
    )
    
    # 3. 获取并修改调色板：在第一位置插入纯黑色
    palette = temp_indexed.getpalette()
    if palette:
        # 创建新的调色板，大小为 color_count * 3
        new_palette = [0] * (color_count * 3)  # 初始全黑
        
        # 第一色设置为纯黑色 (0,0,0)
        new_palette[0] = 0
        new_palette[1] = 0
        new_palette[2] = 0
        
        # 将原调色板复制到后面位置（偏移3个位置）
        for i in range(len(palette)):
            new_palette[i + 3] = palette[i]
        
        # 创建新图像并应用调色板
        indexed_image = temp_indexed.copy()
        
        # 调整颜色索引：原图中的所有颜色索引+1（为黑色让出0号位置）
        data = bytearray(indexed_image.tobytes())
        for j in range(len(data)):
            if data[j] < color_count - 1:  # 确保在有效范围内
                data[j] = data[j] + 1  # 索引+1
        
        indexed_image = Image.frombytes('P', indexed_image.size, bytes(data))
        indexed_image.putpalette(new_palette)
    else:
        # 回退方案：创建简单调色板
        indexed_image = rgb_image.convert(
            'P', 
            palette=Image.ADAPTIVE, 
            colors=color_count,
            dither=Image.NONE
        )
    
    return indexed_image

def save_gba_animation(base_name, unique_frames, frame_sequence, durations, output_dir, color_count=0):
    """
    保存GBA动画所需的所有文件
    """
    output_path = Path(output_dir)
    output_path.mkdir(exist_ok=True)
    
    print(f"保存到: {output_path}")
    
    frame_files = []
    
    # 1. 保存原始帧（去重后）
    print("保存原始帧...")
    for i, frame in enumerate(unique_frames):
        filename = f"original_{i:03d}.png"
        filepath = output_path / filename
        frame.save(filepath, 'PNG')
        frame_files.append(filename)
    
    # 2. 如果指定了颜色数量，保存索引帧
    indexed_files = []
    if color_count > 0:
        print(f"转换索引模式 ({color_count}色，首色为黑)...")
        indexed_dir = output_path / "indexed"
        indexed_dir.mkdir(exist_ok=True)
        
        for i, frame in enumerate(unique_frames):
            indexed_image = convert_to_indexed_with_black_first(frame, color_count)
            filename = f"indexed_{i:03d}.png"
            filepath = indexed_dir / filename
            indexed_image.save(filepath, 'PNG')
            indexed_files.append(filename)
        
        print(f"✓ 已保存 {len(indexed_files)} 个索引图像")
    
    # 创建序列数组定义
    sequence_array = f"static const u8 s{base_name}_ANIM_SEQUENCE[] = {{\n    "
    sequence_lines = []
    for i in range(0, len(frame_sequence), 16):
        chunk = frame_sequence[i:i+16]
        sequence_lines.append(", ".join(f"{x:3d}" for x in chunk))
    sequence_array += ",\n    ".join(sequence_lines)
    sequence_array += "\n};"
    
    print(sequence_array)
    
    return output_path

def main():
    """主函数"""
    print("=" * 60)
    print("GIF转GBA动画工具 - 精简版")
    print("=" * 60)
    
    # 输入GIF文件路径
    gif_path = input("GIF文件路径: ").strip()
    if not os.path.exists(gif_path):
        print(f"✗ 文件不存在: {gif_path}")
        return
    
    # 输入颜色数量
    color_input = input("颜色数量 (0=不转换，1-256=索引颜色): ").strip()
    try:
        color_count = int(color_input)
        if color_count < 0 or color_count > 256:
            print("✗ 颜色数量需在0-256之间")
            return
    except ValueError:
        print("✗ 输入无效")
        return
    
    # 处理GIF
    unique_frames, frame_sequence, durations = extract_and_deduplicate_gif(gif_path)
    if not unique_frames:
        return
    
    # 生成输出目录名
    base_name = Path(gif_path).stem
    if color_count > 0:
        output_dir = f"{base_name}_gif"
    else:
        output_dir = f"{base_name}_original"
    
    # 保存所有文件
    save_gba_animation(base_name, unique_frames, frame_sequence, durations, output_dir, color_count)
    
    # 显示摘要
    print("\n" + "=" * 60)
    print("处理完成!")
    print("=" * 60)
    print(f"输出目录: {output_dir}")
    print(f"唯一帧数: {len(unique_frames)}")
    print(f"序列长度: {len(frame_sequence)}")
    
    if color_count > 0:
        print(f"颜色模式: {color_count}色索引 (首色#000000透明)")
        print(f"索引图像: {output_dir}/indexed/")
    
    print(f"原始图像: {output_dir}/")
    print(f"头文件: {output_dir}/gba_animation.h")
    
    # 显示序列前部分
    sample = frame_sequence[:min(15, len(frame_sequence))]
    print(f"序列预览: {sample}{'...' if len(frame_sequence) > 15 else ''}")

if __name__ == "__main__":
    main()