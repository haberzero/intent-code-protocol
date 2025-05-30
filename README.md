# MCCP - Model Context Code Protocol

欢迎来到 MCCP 项目！本仓库包含了关于 MCCP 这一概念性软件开发框架的核心文档以及两个示例项目，旨在帮助您理解 MCCP 的理念、结构及其工作流程。

Current Version: 0.0.1 

This project is undergoing the most basic initial construction, and its content has a certain degree of uncertainty. We welcome anyone interested to participate

## 1. MCCP 项目简介

MCCP (Model Context Code Protocol) 是一个构想，是一种多层次的半自然语言编程描述系统，亦或者说是一种提示词协议。它并非一门新的编程语言，也永远不应该成为可以直接“运行”或“编译”的编程语言。其设计的核心理念在于成为一种超级中间件，旨在让大语言模型能够与这个世界上的任何编程语言进行“精确化、可信化、可控化沟通”。

MCCP 具备三层抽象层: 自然语言提示词层、行为描述层、符号-伪代码层，三层抽象层具备各自的分工，并成为连接传统编程语言和大模型的桥梁。通过引入 MCCP，大模型生成的代码将更加稳定可控，且允许开发人员在多个抽象层次进行精细、高效的修改。每一层级的修改将同时关联影响到其它层级的内容。

MCCP 从诞生之初就注定了它的快速演进性质，将跟随大模型本身的进化而快速发展，也就注定了无法也不应该形成过于僵硬的语法规定。其中的工程哲学远比语法定义本身要重要。

MCCP 是在大语言模型大行其道的时代下，对传统软件开发的工程构建方法论的拆解重构，旨在改变未来的软件开发范式，真正允许开发者能够将有限的精力更专注于高层级的需求分析、系统设计和行为规划，将繁琐的、低层级的代码实现细节交给大模型。

## 2. 关键文档概览

本仓库包含以下核心定义文档，它们详细阐述了 MCCP 的各个组成部分：

*   [`MCCP_Documentation.md`](./MCCP_Documentation.md)
    *   用途: MCCP 的核心概念文档，详细介绍了 MCCP 的愿景、核心理念、三个抽象层级（自然语言提示词层、行为描述层、符号-伪代码层）、基本功能特征（层级修改反应、兼容性描述文件、符号表、结构化注释、宏定义）以及反向构建过程。它是理解 MCCP 全貌的起点。

*   [`symbol_table_definition.md`](./symbol_table_definition.md)
    *   用途: 符号表定义文档，详细解释了 MCCP 符号表 (`mccp_symbols.json`) 的目的、重要性、JSON 结构示例及其关键字段的定义与用途（包括全局符号、文件内符号、类及函数内部符号）。该文档强调了符号表在确保符号引用可信性，以及跨层级、跨模型一致性等方面的作用。

*   [`compatibility_file_definition.md`](./compatibility_table_definition.md)
    *   用途: 兼容性描述文件定义文档，详细解释了 MCCP 配置文件 (`mccp_config.json`) 的目的、JSON 结构及其核心字段的定义与用途（包括目标大模型、目标编程语言、依赖库/源代码库、MCCP 版本、项目名称、构建设置）。该文件是一种工程描述文件，是MCCP确保项目构建的一致性、可预测性和兼容性的关键配置描述文件。

## 3. 示例项目

目前，本仓库提供了两个完整的 MCCP 示例项目，用于演示 MCCP 工程中符号表和配置文件的使用，以及从自然语言需求，到行为描述层，再到符号-伪代码层，最后到实际可执行代码的完整工程构建流程。

### a. 简易待办事项清单应用 (`demo1_todo_app`)

这是一个基础的命令行待办事项应用，具备添加、查看、标记完成/未完成、删除任务以及数据持久化等功能。它是 MCCP 的第一个示例项目，旨在演示 MCCP 如何将自然语言需求转化为结构化的行为和伪代码。

项目文件位于 `./demo_projects/demo1_todo_app/` 目录下，包含以下文件：

*   [`requirements.md`](./demo_projects/demo1_todo_app/requirements.md)
    *   用途: 自然语言需求描述。以人类易懂的语言描述了待办事项应用的各项功能需求、用户交互方式、错误处理以及启动退出流程。这是整个 MCCP 构建过程的起点。

*   [`todo_app.mccp_b`](./demo_projects/demo1_todo_app/todo_app.mccp_b)
    *   用途: 行为描述层文件。基于自然语言需求，使用半自然语言描述了应用的软件基本构成框架、关键运行流程、初步定义的类/函数/变量及其作用，以及核心业务逻辑分支。该文件是生成符号表和符号-伪代码层的基础。

*   [`todo_app.mccp_p`](./demo_projects/demo1_todo_app/todo_app.mccp_p)
    *   用途: 符号-伪代码层文件。根据行为描述层的内容生成，使用结构化的伪代码语法，描述了应用的具体实现逻辑，包括类定义、方法定义、函数定义、变量声明以及详细的控制流程。此层级非常接近实际代码结构，并引用了符号表中定义的符号。

*   [`mccp_symbols.json`](./demo_projects/demo1_todo_app/mccp_symbol.json)
    *   用途: 符号表文件。记录了项目中定义的所有关键符号（变量、类、函数、结构体）及其作用域信息。它是确保符号-伪代码层和最终代码生成中符号引用准确性的重要元数据。

*   [`mccp_config.json`](./demo_projects/demo1_todo_app/mccp_config.json)
    *   用途: 兼容性描述文件。指定了该 MCCP 工程的目标编程语言（Python）、预期使用的大模型、项目依赖库（如 json 标准库）等环境信息，指导代码生成过程。

### b. 基础计算器应用 (`demo2_calculator_app`)

这是一个基础的命令行计算器应用，支持加、减、乘、除基本运算，并包含连续计算和错误处理功能。它提供了另一个 MCCP 工作流程的示例。

项目文件位于 `./demo_projects/demo2_calculator_app/` 目录下，包含以下文件：

*   [`requirements.md`](./demo_projects/demo2_calculator_app/requirements.md)
    *   用途: 自然语言需求描述。描述了计算器应用的功能需求、用户交互、错误处理（如除零、无效输入）以及退出方式。

*   [`calculator_app.mccp_b`](./demo_projects/demo2_calculator_app/calculator_app.mccp_b)
    *   用途: 行为描述层文件。定义了计算器应用的模块划分（输入获取、解析、计算、输出显示、错误处理、主控逻辑）、关键运行流程（主循环）以及初步设计的关键函数和变量。

*   [`calculator_app.mccp_p`](./demo_projects/demo2_calculator_app/calculator_app.mccp_p)
    *   用途: 符号-伪代码层文件。将行为描述转化为结构化伪代码，详细描述了输入解析逻辑（包括连续计算的解析）、运算分发、错误处理逻辑以及主循环的控制流程。

*   [`mccp_symbols.json`](./demo_projects/demo2_calculator_app/mccp_symbols.json)
    *   用途: 符号表文件。记录了计算器项目中使用的所有符号，包括全局常量、伪代码中定义的结构体、函数及其内部变量。

*   [`mccp_config.json`](./demo_projects/demo2_calculator_app/mccp_config.json)
    *   用途: 兼容性描述文件。指定了该计算器 MCCP 工程的目标语言、预期使用的大模型等配置信息。

## 4. 项目结构说明

推荐的项目文件夹组织结构如下所示：

```
/
├── MCCP_Documentation.md         # MCCP 核心概念文档
├── symbol_table_definition.md    # 符号表定义文档
├── compatibility_file_definition.md # 兼容性文件定义文档
├── demo_projects/                # 示例项目目录
│   ├── demo1_todo_app/         # 简易待办事项清单应用示例
│   │   ├── requirements.md     # 自然语言需求
│   │   ├── todo_app.mccp_b     # 行为描述层文件
│   │   ├── todo_app.mccp_p     # 符号-伪代码层文件
│   │   ├── mccp_symbols.json   # 符号表
│   │   └── mccp_config.json    # 兼容性文件
│   └── demo2_calculator_app/   # 基础计算器应用示例
│       ├── requirements.md     # 自然语言需求
│       ├── calculator_app.mccp_b # 行为描述层文件
│       ├── calculator_app.mccp_p # 符号-伪代码层文件
│       ├── mccp_symbols.json   # 符号表
│       └── mccp_config.json    # 兼容性文件
└── readme.md                     # 当前文件
```

## 5. 如何使用

要理解和使用这些 MCCP 材料，建议按照以下步骤进行：

1.  阅读核心概念: 首先，从 [`MCCP_Documentation.md`](./MCCP_Documentation.md) 入手，理解 MCCP 的基本思想、分层结构和主要特征。
2.  学习定义规范: 接着，阅读 [`symbol_table_definition.md`](./symbol_table_definition.md) 和 [`compatibility_file_definition.md`](./compatibility_table_definition.md)，了解 MCCP 中两个关键元数据文件的结构和作用。
3.  探索示例项目: 选择一个示例项目（例如 `demo1_todo_app`）。
    *   从 [`requirements.md`](./demo_projects/demo1_todo_app/requirements.md) 开始，理解应用的原始需求。
    *   然后，查看 [`todo_app.mccp_b`](./demo_projects/demo1_todo_app/todo_app.mccp_b)，观察需求是如何被转化为结构化的行为描述和初步框架的。
    *   接着，阅读 [`todo_app.mccp_p`](./demo_projects/demo1_todo_app/todo_app.mccp_p)，了解行为描述是如何进一步细化为结构化伪代码的。注意伪代码中使用的符号。
    *   同时，查看 [`mccp_symbols.json`](./demo_projects/demo1_todo_app/mccp_symbols.json) 和 [`mccp_config.json`](./demo_projects/demo1_todo_app/mccp_config.json)，了解符号表和配置文件如何记录项目的元数据和环境信息。
4.  比较层级: 对比同一个示例项目中不同层级的文件，理解信息是如何从抽象逐级具象化的。例如，对比 `requirements.md`、`.mccp_b` 和 `.mccp_p` 文件中对同一个功能的描述。
5.  重复步骤 3 和 4: 探索另一个示例项目 (`demo2_calculator_app`)，加深理解。

通过循序渐进地阅读这些文档和示例文件，您将能逐步掌握 MCCP 的核心思想和工作方式。
