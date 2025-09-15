# ICP - Intent Code Protocol 模型上下文代码协议

注意！本项目正处于初期构建阶段，内容存在一定程度的不确定性

欢迎来到 ICP 项目，本仓库包含了关于 ICP 这一概念性软件开发框架的核心文档以及示例项目，旨在帮助您理解 ICP 的理念、结构及其工作流程

[ICP-Toolchain](https://github.com/haberzero/icp-toolchain) 构建中，这是用于实现ICP工程的核心工具。

当前版本: 0.0.2

当 ICP-Toolchain 的第一个demo版本完善、说明书编写完成后，本仓库版本号将会来到v0.0.3

## 1. ICP 项目简介

ICP (Intent Code Protocol) 是一种代码描述约定，本质上是一种面向大语言模型 (LLM) 的提示词协议，其主体为两个核心抽象层：半自然语言行为描述层和符号-伪代码层。通过这两个抽象层，开发人员能够对大模型的代码生成过程实现相对精确的控制

ICP并不是一门新的编程语言，更像是一种在 LLM 时代的软件开发哲学，一种规范的vibe coding模式。ICP-Toolchain则将成为这种开发模式的“助手”，承担类似于“编译器/解释器”的责任，将ICP的抽象层内容转化为真正的目标代码

我们期望ICP的开发思想能被任何开发者甚至是初学者在**30分钟**以内理解，并且能在1小时内实现一个简单的Demo

ICP希望解决当前vibe coding的主要困境：

- 开发人员无法精确控制ai的生成行为
- 开发人员难以快速阅读ai生成的代码
- 在线服务的token成本过高且难以保证隐私
- 本地部署的模型生成能力和上下文能力不足
- ai生成的代码难以复用，风格不易统一，团队协作能力差

ICP的核心理念:

- 超级中间件： ICP 的核心定位是“超级中间件”，成为大模型与传统编程语言之间的标准化桥梁
- 易于开发： 采用半自然语言式的行为描述作为开发核心，避免掉进“语法和特性的黑洞”
- 快速演进： ICP 将紧密跟随大模型的能力进化而发展，适应ai编程时代的快速技术演进
- 模型兼容： ICP 在设计之初就希望让不同尺寸、特征各异的模型都能合理介入对大型工程的高效开发，使部署过程灵活且易于进行成本控制
- 非侵入性： 允许开发者部分或完全剥离ICP的工程内容，仅保留所需的目标代码，从而能够在未来轻易转向可能存在的更先进的技术

## 2. ICP 的抽象层级结构

ICP 包含三个抽象层级和一个贯穿全局的符号表概念。

三个抽象层构成了从人类需求到接近可执行代码的逐级细化路径：

1.  自然语言提示词层 (`requirements.md`):
    - 描述: 用户以自由、自然的语言描述软件的需求或编程意图。这是 ICP 工程的起点，侧重于“要做什么”，类似于提供给大模型的`README.md`。这是一个初始化层，非核心层级，非必须
    - 示例: “创建一个简单的命令行工具，提示用户输入姓名，然后打印一句个性化的问候语。”
    - 对应文件: 通常体现在项目的 `requirements.md` 文件中

2.  半自然语言行为描述层 (`src_icb/*.icb`):
    - 描述: 对自然语言需求的结构化拆解，具象化软件框架、运行流程、模块定义（类、函数）、业务逻辑处理方式。侧重于“如何通过步骤和行为实现”。允许使用中文/英文进行编写和构建
    - 核心: 定义项目的基本结构、流程控制，并在此层级生成代码的关键符号表框架
    - 对应文件: 位于 `src_icb/` 目录下，使用 `.icb` 扩展名。缩写含义：model context behavior code

3.  （规划中，未实现）符号-伪代码层 (`src_mcpc/*.mcpc`):
    - 描述: 已非常接近实际编程语言的结构，具备基本常用的编程语法概念（如分支、循环、变量、函数调用、类定义等），但仍是抽象的、与特定语言解耦的伪代码
    - 核心: 精确使用符号表，保证代码生成的符号一致性。开发者在此层级通常无需精细微调
    - 对应文件: 位于 `src_mcpc/` 目录下，使用 `.mcpc` 扩展名。缩写含义：model context pseudo code

半自然语言行为描述层和符号-伪代码层作为ICP的核心进行协同工作，由 icp-toolchain 进行层间转换、同步与校验，最终生成目标代码

符号表也是ICP的核心思想之一，它是一个分布式的、层次化的符号记录表，用于记录项目中所有的符号（包括类、函数、变量等）及其关系，符号表的存在能够限制并规范大模型的代码生成行为，减少幻觉并确保其生成的符号调用始终和开发人员所需的符号定义保持一致

## 3. 仓库构成与重要文件

ICP 的约定依赖于一系列定义文件，它们一同构成对ICP的定义与描述：

- 核心文档体系:
    - [`icp_documentation.md`](docs/icp_documentation.md): ICP 的总体介绍、理念、抽象层级和基本特征。
    - [`icp_icb_definition.md`](docs/icp_icb_definition.md): ICP的半自然语言行为描述层语法约定。（重要）
    - [`icp_project_structure_definition.md`](docs/icp_project_structure_definition.md): 定义标准的 ICP 项目文件结构和命名约定。
    - [`icp_project_config_definition.md`](docs/icp_project_config_definition.md): 详细说明项目的核心配置文件 `icp_config.json` 的结构和用途。
    - [`icp_project_symbols_definition.md`](docs/icp_project_symbols_definition.md): 详细说明项目符号表文件 `icp_symbols.json`
    - [`icp_project_compatibility_definition.md`](docs/icp_project_compatibility_definition.md): 详细说明项目兼容性文件 `icp_compatibility.json` 的结构和用途。目前仅作为占位符，当未来明确如何在ICP版本间进行工程迁移时，此文件将会被重新完善。

- 项目配置文件示例 (`config/`):
    - `icp_config.json` 定义项目级别的核心参数，如目标语言、兼容工具链版本
    - `icp_api_config.json` 储存api-url/key等内容。请确保此文件始终处于.gitignore列表中，避免敏感信息泄露
    - `icp_compatibility.json` （待实现）定义项目所需的 ICP 协议版本、目标语言、兼容工具链版本、预期 LLM 等兼容性元数据，确保跨环境一致性

- 符号表文件示例 (分布在`src_icb/` 和 `src_mcpc/`当中):
    - `icp_symbols.json`: 定义项目的符号表结构，包括文件结构、符号定义、依赖关系等

- 源码文件示例（待完善）

## 4. 标准项目工程文件夹结构

一个标准的 ICP 工程应遵循以下推荐的文件组织结构：

```plaintext
/ 项目根目录
├── readme.md             # 项目说明文件
├── license               # 项目许可证文件
├── requirements.md       # 自然语言需求描述层文件
├── src_icb/             # 行为描述层源码目录（包括符号表文件）
├── src_mcpc/             # 符号-伪代码层源码目录（包括符号表文件）
├── src_target/           # 生成的目标源代码目录
├── config/               # 项目参数文件夹
│   ├── icp_config.json      # 项目核心配置文件
│   └── icp_api_config.json
└── temp/                 # 临时文件目录（可忽略，用于构建中间产物）
```

- `requirements.md`: 存放项目的原始需求，自然语言表述。
- `src_icb/`: 存放行为描述层文件，使用 `.icb` 扩展名。
- `src_mcpc/`: 存放符号-伪代码层文件，使用 `.mcpc` 扩展名。
- `src_target/`: 存放 ICP 工具链生成的目标编程语言源代码。
- `config/`: 集中存放 `icp_config.json`, `icp_compatibility.json` 等项目参数和元数据文件。

目录布局与命名原则:

- `src_icb/`, `src_mcpc/`, `src_target/` 三个目录下的文件结构和文件名（除扩展名外）应保持一一对应。
- 针对不同目标语言 ——主要是C/C++—— `.icb` 和 `.mcpc` 文件的命名可能需要额外后缀，具体规则详见 [`icp_project_structure_definition.md`](docs/icp_project_structure_definition.md)。
- （待实现）旁路式工程不遵循以上工程目录结构定义

## 5. 示例工程介绍

规划中，待完善

本项目提供了多个示例工程，用以演示 ICP 的应用和各层级文件的协同工作。

## 6. 如何使用与理解

要有效理解和使用 ICP，建议遵循以下步骤：

1.  理解核心概念: 从 [`icp_documentation.md`](docs/icp_documentation.md) 入手，掌握 ICP 的愿景、多层抽象概念以及其基本功能。
2.  熟悉规范定义: 深入阅读 [`icp_project_structure_definition.md`](docs/icp_project_structure_definition.md)、[`icp_project_config_definition.md`](docs/icp_project_config_definition.md)和[`icp_project_symbols_definition.md`](docs/icp_project_symbols_definition.md) ，了解 ICP 工程的规范细节。
3.  探索示例工程: 选择一个或多个示例项目。
    - 首先阅读项目的 `requirements.md`，理解其原始需求。
    - 同步查阅 `icp_config/icp_config.json`，理解项目配置文件的内容
    - 阅读 `src_icb/` 目录下的 `.icb` 文件，观察需求是如何被拆解为半自然语言的行为描述
    - 浏览 `src_mcpc/` 目录下的 `.mcpc` 文件，了解行为描述如何被转化为更接近实际代码的伪代码结构
    - 最后，查看 `src_target/` 目录下生成的目标代码，对比其与 `.mcpc` `.icb` 文件的关系
4.  实践 (待完善): 随着 ICP 工具链的逐步完善，您可以尝试使用工具对这些示例项目进行正向构建（从 ICP 文件生成代码）或反向构建（从现有代码生成 ICP 文件），亲身体验 ICP 的工作流程。

通过上述步骤，您将能够系统地理解 ICP 的设计思想、文件结构，并掌握根据行为描述层准确控制大模型的代码生成过程的能力

## 7. 未来展望

ICP 是一个不断演进的项目，我们将持续关注大模型能力的发展，以确保 ICP 能够适应不断变化的编程需求。

未来可能的发展方向包括但不限于：

- 为icp-toolchain设计兼容性接口并对外开放，允许不同开发者能够灵活根据所使用的模型自定义icp-toolchain的行为，同时保持对标准ICP工程的兼容性
- 引入*标准化代码说明书*的概念，允许ICP工程直接借助合理的外部文档完成对第三方库的正确调用而无需观察其源码内容。这也能避免 "大模型没有针对特定编程语言训练就无法形成良好语法支持" 的窘境
- 引入更丰富的语言支持，甚至例如Verilog HDL（芯片设计领域的数字电路描述语言）等
- 引入更多的工程结构支持，如多模块工程、多层次工程等
- 持续加强对团队协作开发的支持

版本计划（暂定）:

- v0.0.1: 新建仓库，包含基础文档和示例项目概念。主要文件由AI辅助生成，可能存在语法和格式问题。项目处于演示结构阶段，尚未实现完整的正向/反向构建和可运行Demo
- **v0.0.2**: 修复现有文档的语法问题，完善 `icp_config.json` 和 `icp_symbols.json` 的初步定义。目前，示意性的demo_proj仅由ai直接生成，等待正向构建成功运行后再进行替换
- v0.0.3: 初步实现 ICP 的正向构建功能。会从行为描述层直接生成目标代码，符号-伪代码层的实现暂时搁置。同时尝试将ICP的部分工作流嵌入到已有的AI-IDE（例如Trae）的工作流中
- v0.0.4: 构建demo工程，在过程中维护bug，并且初步实现icp-toolchain的第一次自举
- v0.1.0: 大更新，初步实现反向构建功能，也即从目标代码生成 ICP 层文件。完善符号-伪代码层的文档定义，同时实现对应工具链功能。实现icp-toolchain的“旁路式”工程目录结构
- v0.1.1: 完善反向构建功能，特别是反向构建过程中的符号表生成功能
- v0.1.2: 固定反向构建功能的行为逻辑，会正式创建demo repo并引入更多demo
- v0.2.1: 大更新，正向/反向构建功能的基本稳定可控
