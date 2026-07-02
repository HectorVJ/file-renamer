# 华傲数据 AI 笔试项目方案

## 项目题目
`批量文件重命名工具`

建议副标题：
`支持前缀后缀添加、关键词替换、批量编号、预览模式与重名冲突检测的命令行工具`

## 为什么选这个题目
- 符合“工具类脚本、轻量项目”的要求，题目不偏大。
- 使用场景直观，便于展示输入、处理逻辑和输出结果。
- 适合拆成多轮 AI 协作开发，方便形成清晰的 Git 历史和 JSONL 记录。
- 功能点足够细，可以体现需求拆解、代码组织和边界处理能力。
- 不依赖复杂第三方框架，适合独立完成。

## 开发语言建议
建议使用 `C++`。

原因：
- 在考核允许语言范围内。
- 很适合实现命令行工具、文件扫描、字符串处理和文件重命名逻辑。
- 可以体现基础工程结构设计能力。
- 便于拆成多轮小步提交。

## 项目目标
做一个命令行工具，扫描指定目录中的文件，并根据给定规则批量生成新文件名。在预览模式下只展示映射关系，在执行模式下真正完成重命名，并输出处理结果报告。

### MVP 功能
1. 支持读取目标目录路径。
2. 支持扫描目录下文件。
3. 支持按扩展名筛选文件。
4. 支持添加前缀。
5. 支持添加后缀。
6. 支持关键词替换。
7. 支持批量编号。
8. 支持预览重命名结果。
9. 支持检测目标文件名冲突。
10. 支持真正执行重命名。
11. 支持导出处理结果报告。

### 建议的输出信息
- 扫描到的文件总数
- 筛选后参与处理的文件数
- 预览成功的文件数
- 检测到的冲突数
- 实际重命名成功数
- 重命名失败数
- 报告文件路径

## 建议目录结构
```text
file-renamer/
  README.md
  CMakeLists.txt
  src/
    main.cpp
    cli.cpp
    file_scanner.cpp
    file_filter.cpp
    rename_rule.cpp
    rename_executor.cpp
    report_writer.cpp
  include/
    cli.h
    file_entry.h
    file_scanner.h
    file_filter.h
    rename_rule.h
    rename_executor.h
    report_writer.h
  sample/
    demo_files/
  docs/
    prompts/
      round-01.txt
      round-02.txt
  records/
    AI开发考核_戴浩天_批量文件重命名工具.jsonl
```

## 你实际操作时的节奏
这次笔试最关键的是：

`一轮交互 = 一次代码修改 = 一次 git commit = 一条 JSONL`

每一轮都按下面流程走：
1. 明确一个很小的目标。
2. 给智能体一段完整 prompt。
3. 审核输出代码。
4. 本地运行验证。
5. `git add .`
6. `git commit -m "..."`
7. 记录一条 JSONL。

## 建议开发轮次

### Round 1
目标：初始化仓库和基础工程

建议 prompt：
```text
请使用 C++ 帮我初始化一个命令行项目，项目名称为 file-renamer。要求：1. 生成 CMakeLists.txt 2. 生成 src/ 和 include/ 基础目录结构 3. main.cpp 先只打印基础帮助信息 4. 保持代码简洁，便于后续扩展
```

建议提交：
`chore: initialize file-renamer project`

### Round 2
目标：增加命令行参数解析

建议 prompt：
```text
请在当前 C++ 项目中增加命令行参数解析。要求：1. 支持输入目录路径参数 2. 支持预览模式和执行模式参数 3. 支持扩展名筛选参数 4. 参数缺失时打印清晰提示 5. 暂时不要实现具体重命名逻辑，只完成参数校验
```

建议提交：
`feat: add cli argument parsing`

### Round 3
目标：实现目录扫描

建议 prompt：
```text
请在当前 C++ 项目中实现目录扫描功能。要求：1. 校验输入目录是否存在 2. 只扫描普通文件 3. 输出扫描到的文件数量 4. 对非法目录给出清晰错误提示 5. 尽量使用标准库实现
```

建议提交：
`feat: add file scanning support`

### Round 4
目标：增加文件筛选

建议 prompt：
```text
请为当前工具增加文件筛选能力。要求：1. 支持按扩展名筛选文件 2. 支持按文件名关键字筛选文件 3. 只保留符合条件的文件参与后续处理 4. 保持逻辑清晰，便于扩展
```

建议提交：
`feat: add extension and keyword filtering`

### Round 5
目标：实现前缀和后缀规则

建议 prompt：
```text
请为当前工具增加前缀和后缀重命名规则。要求：1. 支持给文件名添加前缀 2. 支持给文件名添加后缀 3. 保持原扩展名不变 4. 输出原文件名和新文件名映射结果
```

建议提交：
`feat: add prefix and suffix rename rules`

### Round 6
目标：实现关键词替换

建议 prompt：
```text
请为当前工具增加文件名关键词替换功能。要求：1. 支持将文件名中的指定关键词替换为新内容 2. 不修改扩展名 3. 如果文件名中不存在关键词，则保持原样 4. 保持实现简洁可读
```

建议提交：
`feat: add keyword replacement rule`

### Round 7
目标：实现批量编号

建议 prompt：
```text
请为当前工具增加批量编号功能。要求：1. 支持按顺序给文件添加编号 2. 支持设置起始编号 3. 支持固定宽度编号格式，例如 001 4. 编号规则应能和已有重命名规则配合使用
```

建议提交：
`feat: add sequential numbering rule`

### Round 8
目标：增加预览模式

建议 prompt：
```text
请为当前工具增加预览模式。要求：1. 在不修改真实文件的前提下，展示原文件名和新文件名映射 2. 输出参与处理的文件数 3. 输出预览结果，便于人工检查 4. 不要执行实际重命名
```

建议提交：
`feat: add rename preview mode`

### Round 9
目标：增加冲突检测

建议 prompt：
```text
请为当前工具增加目标文件名冲突检测。要求：1. 检查生成的新文件名是否重复 2. 检查目标路径中是否已存在同名文件 3. 冲突时给出明确提示 4. 保持逻辑尽量独立，便于后续执行阶段复用
```

建议提交：
`feat: add rename conflict detection`

### Round 10
目标：执行真正重命名

建议 prompt：
```text
请为当前工具实现实际重命名功能。要求：1. 在执行模式下真正修改文件名 2. 逐个输出成功和失败结果 3. 失败时保留错误原因 4. 不要影响预览模式
```

建议提交：
`feat: add rename execution workflow`

### Round 11
目标：导出处理报告

建议 prompt：
```text
请为当前工具增加结果报告导出能力。要求：1. 将本次处理结果写入文本或 Markdown 报告 2. 报告中包含原文件名、新文件名、处理状态、失败原因 3. 输出报告文件路径 4. 保持格式清晰易读
```

建议提交：
`feat: export rename result report`

### Round 12
目标：补充示例与 README

建议 prompt：
```text
请为当前项目补充示例目录说明和 README。要求：1. 说明项目用途 2. 写清编译方式和运行方式 3. 写清参数说明 4. 给出预览模式和执行模式示例 5. 保持文档简洁实用
```

建议提交：
`docs: add sample usage and README`

### Round 13
目标：处理边界情况

建议 prompt：
```text
请检查当前工具的边界情况，并做最小必要修复。重点关注：1. 空目录 2. 非法路径 3. 重复目标文件名 4. 无权限重命名 5. 缺少筛选结果时的提示。请只做必要修复，不要大改结构。
```

建议提交：
`fix: handle edge cases for file renaming`

### Round 14
目标：最终整理交付

建议 prompt：
```text
请帮我对当前 C++ 项目做一次轻量整理。要求：1. 检查 README 是否完整 2. 检查命令行输出文案是否一致 3. 检查命名是否清晰 4. 不要引入额外复杂依赖 5. 仅做适合笔试提交的整理
```

建议提交：
`chore: finalize project for assessment submission`

## Git 操作步骤

### 1. 初始化仓库
在项目目录执行：

```powershell
git init
git branch -m main
```

### 2. 每一轮开发都这样提交
```powershell
git status
git add .
git commit -m "feat: add cli argument parsing"
git rev-parse HEAD
git show --stat --oneline HEAD
```

你需要把 `git rev-parse HEAD` 得到的哈希填入对应 JSONL 记录。

### 3. 本地构建与运行
```powershell
cmake -S . -B build
cmake --build build
.\build\file-renamer.exe --input sample\demo_files --preview
```

### 4. 最后推到远程仓库
```powershell
git remote add origin <你的仓库地址>
git push -u origin main
```

## JSONL 记录怎么写
每一行一条 JSON，对应一轮交互。

字段固定为：
- `round_id`
- `prompt_content`
- `modify_diff`
- `commit_hash`
- `modify_time`
- `agent_type`
- `dev_language`

## 如何拿到 diff
提交前看工作区 diff：

```powershell
git diff
```

提交后拿本轮 commit diff：

```powershell
git show --unified=3 --format= HEAD
```

建议最终写进 JSONL 的 `modify_diff` 使用上面这条命令的输出。

## 最后提交前检查清单
- Git 仓库可访问
- 每一轮都有 commit
- 每一轮都有 JSONL
- JSONL 是 UTF-8 编码
- JSONL 文件名符合规范
- README 能说明怎么编译和运行
- 示例目录可复现预览和执行效果
- 简历已附上

## 最后提醒
这次考核本质上在看三件事：
- 你会不会把一个小需求拆成可执行的小步骤
- 你会不会正确使用 AI 编程智能体
- 你能不能对 AI 产出的代码负责

所以不要追求花哨，重点是：

`小而完整、过程真实、记录严谨`
