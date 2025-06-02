# MCCP - Model Context Code Protocol 模型上下文代码协议

欢迎来到 MCCP 项目！本仓库包含了关于 MCCP 这一概念性软件开发框架的核心文档以及示例项目，旨在帮助您理解 MCCP 的理念、结构及其工作流程。

本项目正处于基础的初始构建阶段，内容存在一定程度的不确定性。我们欢迎任何感兴趣的人士参与。

当前版本: 0.0.2

版本计划（暂定）:

-   v0.0.1: 新建仓库，包含基础文档和示例项目概念。主要文件由AI辅助生成，可能存在语法和格式问题。项目处于演示结构阶段，尚未实现完整的正向/反向构建和可运行Demo。
-   **v0.0.2**: 修复现有文档的语法问题，完善 `mccp_config.json` 和 `mccp_symbols.json` 的初步定义（示意性的demo_proj暂时未完善，等待正向构建运行后直接替换）。
-   v0.0.3: 初步实现 MCCP 的正向构建功能，目前计划将MCCP-ToolChain放置在新repo（**暂缓**，优先尝试直接将MCCP协议嵌入Trae的工作流，直接把MCCP当作完整提示词工程使用，提供早期预览并进行宣传）。
-   v0.0.4: 基于标准工程文件夹结构，构建并实现第一个可运行的 Demo 应用。MCCP 的工程文件夹结构初步固定。
-   v0.0.5: 基于新的标准工程文件夹结构，构建并实现第二个可运行的 Demo 应用。初步固定正向构建功能的行为逻辑。
-   v0.1.0: 大更新，初步实现反向构建功能（从目标代码生成 MCCP 层文件）。MCCP 的工程文件夹结构进一步完善。
-   v0.1.1: 完善反向构建功能，特别是反向构建过程中的符号定义表生成功能。
-   v0.1.2: 初步固定反向构建功能的行为逻辑，会正式创建demo repo并引入更多demo。
-   v0.2.1: 大更新，正向/反向构建功能的基本稳定可控。

## 1. MCCP 项目简介

MCCP (Model Context Code Protocol) 是一个构想中的半自然语言编程描述系统，本质上是一种面向大语言模型 (LLM) 的提示词协议。它并非一门新的编程语言，也永远不应该成为可以直接“运行”或“编译”的编程语言。我们期望MCCP的开发思想能被任何开发者甚至是初学者在**30分钟**以内理解，并且能在1小时内实现一个简单的Demo。因此，极端复杂的规则文件编写等操作将被摒弃，ai辅助开发的思想将会深度嵌入到MCCP工程的构建过程。

核心理念:

-   超级中间件： MCCP 的核心定位是成为一个“超级中间件”，构建在大模型与传统编程语言之间。它通过一种结构化的、介于自然语言和代码之间的“伪代码”形式的中间层，同时借助分布式符号表的概念，实现大模型对实际代码的“精确化、可信化、可控化”生成与修改。
-   层级间同步： 开发者可以在 MCCP 的不同抽象层级上进行精细化修改，这些修改能在LLM的帮助下关联影响到其他相关层级的内容，并由大模型协调更新。
-   快速演进： MCCP 的设计理念内嵌了快速演进的属性。它将紧密跟随大模型能力的进化而发展，避免过度僵化的语法结构，确保协议的灵活性和适应性。

MCCP 是在 LLM 时代对传统软件开发工程构建哲学的重构，旨在普及一种新的编程范式，将开发重心从低层级的代码实现转移到高层级的需求分析、系统设计和行为规划，同时通过 MCCP 保持对代码生成过程的高度控制。

## 2. MCCP 的抽象层级结构

MCCP 包含三个核心抽象层级和一个贯穿全局的符号表概念。

三个抽象层构成了从人类需求到接近可执行代码的逐级细化路径：

1.  自然语言提示词层 (`requirements.md`):
    -   描述: 用户以自由、自然的语言描述软件的需求或编程意图。这是 MCCP 工程的起点，侧重于“要做什么”。
    -   示例: *“创建一个简单的命令行工具，提示用户输入姓名，然后打印一句个性化的问候语。”*
    -   对应文件: 通常体现在项目的 `requirements.md` 文件中。

2.  半自然语言行为描述层 (`src_mcbc/*.mcbc`):
    -   描述: 对自然语言需求的结构化拆解，具象化软件框架、运行流程、模块定义（类、函数）、业务逻辑处理方式。侧重于“如何通过步骤和行为实现”。应当允许使用中文/英文进行构建，遥远的未来可能会尝试适配多种语言。文件扩展名缩写含义：model context behavior code。
    -   核心: 定义项目的基本结构、流程控制，并在此层级生成代码的关键符号表框架。
    -   对应文件: 位于 `src_mcbc/` 目录下，使用 `.mcbc` 扩展名。

3.  符号-伪代码层 (`src_mcpc/*.mcpc`):
    -   描述: 已非常接近实际编程语言的结构，具备基本常用的语法概念（如分支、循环、变量、函数调用、类定义等），但仍是抽象的、与特定语言解耦的伪代码。侧重于“用接近代码的结构表达行为”。应当允许使用中文/英文进行构建，遥远的未来可能会尝试适配多种语言。文件扩展名缩写含义：model context pseudo code。
    -   核心: 精确使用符号表，保证代码生成的符号一致性。开发者在此层级通常无需精细微调。
    -   对应文件: 位于 `src_mcpc/` 目录下，使用 `.mcpc` 扩展名。

这三个层级协同工作，由 MCCP 工具链（会大量涉及 LLM）进行层间转换、同步与校验，最终生成目标编程语言代码。

符号表是MCCP的核心idea，它是一个分布式的、层次化的符号定义表，用于记录项目中所有的符号（包括类、函数、变量等）及其关系，符号表的存在能够限制并规范大模型的代码生成行为，并确保生成的代码调用始终和开发人员所需的符号定义保持一致。

## 3. MCCP 关键组成部分与文件

MCCP 工程依赖于一系列关键文件和概念，它们共同构成了协议的核心：

-   核心文档体系:
    -   [`mccp_documentation.md`](docs/mccp_documentation.md): MCCP 的总体介绍、理念、抽象层级和基本特征。
    -   [`mccp_project_structure_definition.md`](docs/mccp_project_structure_definition.md): 定义标准的 MCCP 项目文件结构和命名约定。
    -   [`mccp_project_config_definition.md`](docs/mccp_project_config_definition.md): 详细说明项目的核心配置文件 `mccp_config.json` 的结构和用途。
    -   [`mccp_project_symbols_definition.md`](docs/mccp_project_symbols_definition.md): 详细说明项目符号表文件 `mccp_symbols.json`
    -   [`mccp_project_compatibility_definition.md`](docs/mccp_project_compatibility_definition.md): 详细说明项目兼容性文件 `mccp_compatibility.json` 的结构和用途。目前仅作为占位符，当未来明确如何在MCCP版本间进行工程迁移时，此文件将会被重新完善。

-   项目配置文件 (`config/`):
    -   `mccp_config.json`: 定义项目级别的核心参数，如目标语言、兼容工具链版本、预期 LLM。
    -   `mccp_compatibility.json`: 定义项目所需的 MCCP 协议版本、目标语言、兼容工具链版本、预期 LLM 等兼容性元数据，确保跨环境一致性。

-   符号表文件 (`src_mcbc/` 和 `src_mcpc/`):
    -   `mccp_symbols.json`: 定义项目的符号表结构，包括文件结构、符号定义、依赖关系等。

具体的配置文件结构示例请参考对应文档中的详细说明。

## 4. 标准项目工程文件夹结构

一个标准的 MCCP 工程应遵循以下推荐的文件组织结构：

```plaintext
/ 项目根目录
├── readme.md             # 项目说明文件
├── license               # 项目许可证文件
├── requirements.md       # 自然语言需求描述层文件
├── src_mcbc/             # 行为描述层源码目录（包括符号表文件）
├── src_mcpc/             # 符号-伪代码层源码目录（包括符号表文件）
├── src_target/           # 生成的目标源代码目录
├── config/               # 项目参数文件夹
│   ├── mccp_config.json      # 项目核心配置文件
│   └── mccp_compatibility.json # 项目兼容性文件
└── temp/                 # 临时文件目录（可忽略，用于构建中间产物）
```

-   `requirements.md`: 存放项目的原始需求，自然语言表述。
-   `src_mcbc/`: 存放行为描述层文件，使用 `.mcbc` 扩展名。
-   `src_mcpc/`: 存放符号-伪代码层文件，使用 `.mcpc` 扩展名。
-   `src_target/`: 存放 MCCP 工具链生成的目标编程语言源代码。
-   `config/`: 集中存放 `mccp_config.json`, `mccp_compatibility.json` 等项目参数和元数据文件。
-   `temp/`: 存放构建过程中产生的临时文件，通常应被版本控制系统忽略（如在 `.gitignore` 中配置）。

目录布局原则:

-   `src_mcbc/`, `src_mcpc/`, `src_target/` 三个目录下的文件结构和文件名（除扩展名外）应保持一一对应。
-   针对不同目标语言，`.mcbc` 和 `.mcpc` 文件的命名可能需要额外后缀，具体规则详见 [`mccp_project_structure_definition.md`](docs/mccp_project_structure_definition.md)。

## 5. 示例工程介绍

本项目提供了多个示例工程，用以演示 MCCP 的应用和各层级文件的协同工作。（待完善）

## 6. 如何使用与理解

要有效理解和使用 MCCP，建议遵循以下步骤：

1.  理解核心概念: 从 [`mccp_documentation.md`](docs/mccp_documentation.md) 入手，掌握 MCCP 的愿景、三层抽象和基本功能。
2.  熟悉规范定义: 深入阅读 [`mccp_project_structure_definition.md`](docs/mccp_project_structure_definition.md)、[`mccp_project_config_definition.md`](docs/mccp_project_config_definition.md)和[`mccp_project_symbols_definition.md`](docs/mccp_project_symbols_definition.md) ，了解 MCCP 工程的规范细节。
3.  探索示例工程: 选择一个或多个示例项目。
    -   首先阅读项目的 `requirements.md`，理解其原始需求。
    -   查看 `src_mcbc/` 目录下的 `.mcbc` 文件，观察需求是如何被拆解为结构化行为的。注意其中的提示词注释。
    -   阅读 `src_mcpc/` 目录下的 `.mcpc` 文件，了解行为描述如何被转化为更接近代码的伪代码结构，以及如何使用符号。
    -   同时查阅 `mccp_config/mccp_symbols.json` 和 `mccp_config/mccp_config.json`，理解符号表和项目配置如何支持上述层级。
    -   最后，查看 `src_target/` 目录下生成的目标代码，对比其与 `.mcpc` 文件的关系，理解生成过程。
4.  对比与关联: 在探索过程中，重点对比同一功能在不同层级（需求、行为描述、符号-伪代码、符号表）的表达方式，理解信息是如何逐级细化和关联的。
5.  实践 (未来): 随着 MCCP 工具链的逐步完善，您可以尝试使用工具对这些示例项目进行正向构建（从 MCCP 文件生成代码）或反向构建（从现有代码生成 MCCP 文件），亲身体验 MCCP 的工作流程。

通过上述步骤，您将能够系统地理解 MCCP 的设计思想、文件结构以及它如何实现对大模型代码生成的精确控制。
