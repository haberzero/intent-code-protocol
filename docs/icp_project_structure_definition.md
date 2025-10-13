# ICP项目工程文件夹结构定义

本文档详细定义了基于ICP（Model-Context-Code Protocol）的新工程文件夹标准结构、文件命名约定及核心组成部分，旨在作为后续所有ICP项目构建、文件重构和配置优化的核心参照标准

## 1. 整体项目结构概览

一个典型的ICP项目应采用分层、模块化的文件夹结构，以清晰地组织不同层级的代码、配置和文档。其顶级目录主要包含项目元信息文件、三个相互对应的源码层级目录、一个项目参数配置目录以及一个临时文件目录

```text
/ 项目根目录
├── README.md
├── license
├── requirements.md # 自然语言需求描述层文件
├── src_icb/       # 行为描述层源码目录（包括符号表文件）
├── src_target/     # 目标源代码目录
├── .icp_config/         # 项目参数文件夹
├── temp/           # 临时文件文件夹
└── ...             # 其他项目相关文件，如gitgnore等（可选）
```

## 2. 主项目根目录内容

项目根目录存放项目的元信息文件：

- `requirements.md`: **需求描述文件**。此文件应包含项目的原始、高层次的自然语言需求描述。这是一个可选文件，通常作为icp项目开发的最初起点
- `README.md`: 项目描述文本文件。提供项目的简介、构建/运行指南、贡献方式等信息。此文件主要面向开发者和用户，不参与ICP的自动化生成流程
- `license`: 许可证文件。包含项目的开源或许可信息
- `.gitignore`: 以gitignore为例的其它可选文件等

## 3. 两个主要源码文件夹

ICP的核心在于两个层级的源码文件，它们代表了从高层行为描述到最终可执行代码的转换过程

这两个层级的文件应分别存放在独立的文件夹中，但其内部的目录结构和文件名称（除后缀外）必须保持**完全一致**，形成严格的一一对应关系

文件夹推荐命名如下：

- `src_icb/`: 行为描述层源码目录。存放行为描述层文件，后缀名为 `.icb`。缩写含义：model context behavior
- `src_target/` 或 `src_tmain/`: 目标源代码目录。存放最终生成或手动编写的目标语言源代码文件（如 `.c`, `.cpp`, `.py`, `.java` 等）

**重要原则：** 

`src_icb/`, `src_target/` 目录下的子目录结构必须完全相同，且位于相同路径下的文件应具有相同的文件名，仅文件后缀不同

除此之外，符号表文件也会同时分布在src_icb的各个子文件夹下，每一层级的文件夹内的icp_symbols将会各自独立管理其当前路径内文件的对应符号表
具体内容请查阅[`icp_project_symbols_definition.md`](docs/icp_project_symbols_definition.md)

例如，如果 `src_target/utils/math.c以及math.h` 存在，则必须对应存在：

- `src_icb/utils/math_c.icb` 
- `src_icb/utils/math_h.icb`

(C语言的文件后缀处理)

如果 `src_target/scripts/process.py` 存在且兼容性配置要求额外后缀，则对应：

- `src_icb/scripts/process_py.icb`
如果 `src_target/scripts/process.py` 存在且兼容性配置不要求额外后缀，则对应：

- `src_icb/scripts/process.icb`

## 4. 文件命名约定

文件的命名必须遵循以下约定，特别是对于 `.icb` 文件，需要根据对应的目标源代码文件类型进行特殊处理，以确保唯一性和清晰度

a.  **基本后缀名**
    - 行为描述层文件后缀名：固定为 `.icb`。

b.  **针对C/C++语言系列的特殊处理**
    如果目标源代码文件属于C语言系列（常见的后缀有 `.c`, `.cpp`, `.h`, `.hpp` 等），其对应的行为描述层 (`.icb`) 文件名，应在原文件名末尾、扩展名（`.icb`）之前，增加一个特定的额外后缀。这个额外后缀根据原C/C++文件的类型决定：
    - `.h`, `.hpp` (头文件) -> 额外后缀 `_h`
    - `.c` (C源文件) -> 额外后缀 `_c`
    - `.cpp`, `.cc`, `.cxx` (C++源文件) -> 额外后缀 `_cpp` `_cc` `_cxx`

例如:
    - 目标文件 `main.h` -> 对应ICB文件: `main_h.icb`
    - 目标文件 `utils.c` -> 对应ICB文件: `utils_c.icb`
    - 目标文件 `geometry.cpp` -> 对应ICB文件: `geometry_cpp.icb`

    在工程配置文件（参见第5项）中，对于C语言系列（如语言类型标记为 `"c"`, `"cpp"` 等），其 `is_extra_suffix` 属性应**固定为 `true`**，且其额外后缀的生成规则硬编码为上述逻辑

c.  **针对其他语言系列的处理**
    对于非C/C++的其他目标语言（如 Python, Java, JavaScript 等），其对应的行为描述层 (`.icb`) 文件名是否添加额外后缀，由工程配置配置文件中的 `is_extra_suffix` 布尔属性控制

    - 如果在工程配置文件中，对应语言的 `is_extra_suffix` 属性为 `true`：
        在应在原文件名末尾、扩展名（`.icb`）之前，增加一个额外后缀
        示例:
        - 目标文件 `script.py`, `is_extra_suffix: true` -> 对应ICP文件: `script_py.icb`
        - 目标文件 `App.java`, `is_extra_suffix: true` -> 对应ICP文件: `App_java.icb`

    - 如果在工程配置文件中，对应语言的 `is_extra_suffix` 属性为 `false` 或未设置：
        无额外后缀
        示例:
        - 目标文件 `script.py`, `is_extra_suffix: false` -> 对应ICP文件: `script.icb`

**文件命名示例总结表:**

| 目标文件 (示例) | 目标文件类型 / 扩展名 | 兼容性配置 `is_extra_suffix` | `.icb` 文件 (示例) | 规则依据 |
| :-------------- | :-------------------- | :--------------------------- | :---------------------- | :---------------------- | :------- |
| `header.h`      | C/C++ Header (`.h`)   | `true` (固定)                | `header_h.icb`          | C/C++ 规则 (`_h`) |
| `source.c`      | C Source (`.c`)       | `true` (固定)                | `source_c.icb`          | C/C++ 规则 (`_c`) |
| `module.cpp`    | C++ Source (`.cpp`)   | `true` (固定)                | `module_cpp.icb`        | C/C++ 规则 (`_cpp`) |
| `util.py`       | Python (`.py`)        | `true`                       | `util_py.icb`           | 其他语言规则 (`_py`) |
| `util.py`       | Python (`.py`)        | `false` 或 未设置             | `util.icb`              | 其他语言规则 (无额外后缀) |

## 5. 项目配置文件夹

建议的文件夹名称为 `icp_config/`。此文件夹用于集中存放项目的各类配置和参数文件，这些文件通常不直接参与代码生成，而是为ICP工具链提供必要的上下文信息或规则

主要内容包括：

- 工程配置文件`icp_config.json`: 定义ICP如何处理不同目标语言的规则，包括但不限于文件后缀映射、特定文件名处理规则（如 `is_extra_suffix` 的默认值/行为） 等
- 未来可能新出现的其它配置/参数文件: 例如，代码风格指南配置、特定生成器的参数配置等
