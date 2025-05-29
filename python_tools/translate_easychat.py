import openpyxl
import re
import os

current_folder = os.path.dirname(os.path.abspath(__file__))

# 文件路径
xlsx_path = os.path.join(current_folder, "src", "easychat.xlsx")
h_file_paths = {
    "对战开拓区": os.path.join(os.path.dirname(current_folder), "src", "data", "battle_frontier", "battle_frontier_trainers.h"),
    "对战帐篷": os.path.join(os.path.dirname(current_folder), "src", "data", "battle_frontier", "battle_tent.h"),
    "训练家之丘": os.path.join(os.path.dirname(current_folder), "src", "data", "battle_frontier", "trainer_hill.h"),
    "徒弟": os.path.join(os.path.dirname(current_folder), "src", "data", "battle_frontier", "battle_frontier_trainers.h")
}

# 读取 Excel 文件
wb = openpyxl.load_workbook(xlsx_path, data_only=True)

# 提取并替换内容的函数
def replace_h_file(sheet_name, h_file_path):
    sheet = wb[sheet_name]
    speech_lines = {
        ".speechBefore": [],
        ".speechWin": [],
        ".speechLose": [],
        ".speechAfter": [],
        ".speechLost": []
    }

    # 提取指定列中以指定前缀开头的内容
    for cell in sheet["AA"]:
        if cell.value:
            for key in speech_lines.keys():
                if cell.value.startswith(key):
                    speech_lines[key].append(cell.value)
                    break

    # 读取 .h 文件内容
    with open(h_file_path, "r", encoding="utf-8") as file:
        h_file_lines = file.readlines()

    # 替换 .h 文件中的内容
    for key, replacements in speech_lines.items():
        if replacements:
            replacement_index = 0
            for i, line in enumerate(h_file_lines):
                if key in line:
                    if replacement_index < len(replacements):
                        # 保留原行的缩进
                        indent = re.match(r"^\s*", line).group()
                        h_file_lines[i] = f"{indent}{replacements[replacement_index]}\n"
                        replacement_index += 1

    # 写回 .h 文件
    with open(h_file_path, "w", encoding="utf-8") as file:
        file.writelines(h_file_lines)

    print(f"{sheet_name} 替换完成！")

# 执行替换操作
for sheet_name, h_file_path in h_file_paths.items():
    replace_h_file(sheet_name, h_file_path)