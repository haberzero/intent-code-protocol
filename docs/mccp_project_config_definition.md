# MCCP 配置文件 (`mccp_config.json`) 规范

`mccp_config.json` 文件是 MCCP 项目中的核心组成部分，作为项目特定的配置清单。它定义了指导 MCCP 工具链处理项目的行为描述层 (`.mcbh`) 和符号描述层 (`.mcpc`) 文件以及生成目标源代码 (`src_target`) 所必需的基本参数。

该文件指定了项目元数据、目标编程语言、构建参数、依赖项，以及将 MCCP 层文件映射到目标文件系统结构的规则，包括重要的命名约定。

## 文件位置

根据 MCCP 项目结构约定，`mccp_config.json` 文件应存放在项目的配置文件夹中。标准存放路径建议为：

`config/mccp_config.json`

这是一个相对于项目根目录的路径，与 `mccp_symbols.json` 存放于同一目录下，便于集中管理项目配置。

```
/ 项目根目录
├── config/
│   └── mccp_config.json  <-- 文件位置
├── src_mbh/
├── src_mpc/
└── src_target/
```

对于包含多个独立模块/应用的更大型项目，或者像本仓库中的示例项目那样，可能在每个模块/应用自己的目录下包含一个 `config/` 文件夹及其对应的 `mccp_config.json` 和 `mccp_symbols.json`，以实现模块级别的配置管理。例如：`demo_projects/demo1_todo_app/config/mccp_config.json`。

## 核心字段定义

以下是 `mccp_config.json` 中需要包含的基本字段：

*   **`projectName`**:
    *   类型: `string`
    *   描述: MCCP 项目的人类可读名称。用于标识和文档生成。
    *   示例: `"My MCCP Project"`

*   **`mccpVersion`**:
    *   类型: `string`
    *   描述: 指定项目所基于的 MCCP 框架或协议版本。有助于确保与工具链的兼容性。
    *   示例: `"0.1.0"`

*   **`targetLanguage`**:
    *   类型: `string`
    *   描述: 定义生成的目标源代码的编程语言。此设置是**区分大小写**的，并决定了工具链应用的语言特定规则，包括某些文件命名约定。
    *   常见示例: `"C"`, `"C++"`, `"Python"`, `"Java"`, `"JavaScript"`

*   **`targetModel`**:
    *   类型: `string`
    *   描述: 指定 MCCP 层设计所面向的或工具链应使用的目标 AI 模型或“蓝图”作为上下文。这影响抽象描述 (`.mcbh`, `.mcpc`) 如何被解释和转换为目标语言。
    *   示例: `"default_mccp_model"`

## 文件系统映射和命名约定 (`fileSystemMapping` 对象)

这是一个可选但强烈推荐的对象，它定义了 `src_mbh` 和 `src_mpc` 中的结构如何映射到 `src_target`，以及文件在这些层级之间的命名方式。如果省略，将应用默认值和命名逻辑。

```json
"fileSystemMapping": {
  "behavioralLayerDir": "src_mbh/", // 行为描述层目录
  "symbolicLayerDir": "src_mpc/",   // 符号描述层目录
  "targetLayerDir": "src_target/",  // 目标代码目录
  "behavioralLayerExtension": ".mcbh", // 行为描述层文件后缀
  "symbolicLayerExtension": ".mcpc",   // 符号描述层文件后缀
  "is_extra_suffix": false // 默认值，见下方规则
}
```

*   **`behavioralLayerDir`**:
    *   类型: `string`
    *   描述: 行为描述层文件的根目录。
    *   标准值: `"src_mbh/"` (惯例包含尾部斜杠)。

*   **`symbolicLayerDir`**:
    *   类型: `string`
    *   描述: 符号-伪代码层文件的根目录。
    *   标准值: `"src_mpc/"` (惯例包含尾部斜杠)。

*   **`targetLayerDir`**:
    *   类型: `string`
    *   描述: 目标源代码文件的根目录。
    *   标准值: `"src_target/"` (惯例包含尾部斜杠)。

*   **`behavioralLayerExtension`**:
    *   类型: `string`
    *   描述: 行为描述层文件的文件扩展名。
    *   标准值: `".mcbh"`

*   **`symbolicLayerExtension`**:
    *   类型: `string`
    *   描述: 符号-伪代码层文件的文件扩展名。
    *   标准值: `".mcpc"`

*   **`is_extra_suffix`**:
    *   类型: `boolean`
    *   描述: 此字段控制是否在对应的 `.mcbh` 和 `.mcpc` 文件的基本文件名之后添加一个派生自原始目标文件扩展名的额外后缀。这对于区分对应不同目标文件类型（例如 C 语言中的 `.c` 和 `.h`）的 MCCP 文件至关重要。

    *   **通用行为 (应用时):** 如果为 `true`，则在 MCCP 层扩展名 (`.mcbh` 或 `.mcpc`) 之前，会在基本文件名后附加一个下划线 (`_`) 跟着原始目标文件的扩展名（不包含开头的点）。
        *   示例: 目标文件 `file.ext` -> MCCP 文件 `file_ext.mcbh`, `file_ext.mcpc`。

    *   **C 语言家族 (`C`, `C++`, 等):**
        *   对于 `targetLanguage` 设置为 C 语言家族（例如 `"C"`, `"C++"`）时，`is_extra_suffix` 的行为是**隐式为 `true`** 的，并且通常不应在配置中显式设置为 `false`，因为工具链会强制执行特定的 C 语言家族命名规则，而无论此标志在 JSON 中的值如何。
        *   额外后缀是根据 C/C++ 文件类型**固定**的：
            *   对于头文件（例如 `.h`, `.hpp`）：额外后缀是 `_h`。
                *   示例: `utils.h` -> `utils_h.mcbh`, `utils_h.mcpc`。
            *   对于源文件（例如 `.c`, `.cpp`, `.cc`, `.cxx`）：额外后缀分别是 `_c` 或 `_cpp`。
                *   示例: `main.c` -> `main_c.mcbh`, `main_c.mcpc`。
                *   示例: `module.cpp` -> `module_cpp.mcbh`, `module_cpp.mcpc`。

    *   **其他语言（例如 `Python`, `Java`, `JavaScript`）:**
        *   对于其他语言，`is_extra_suffix` 字段是**可配置的**。
        *   如果 `is_extra_suffix` 为 `true`：额外后缀直接派生自目标文件的扩展名（例如 `.py` -> `_py`）。
            *   示例: `script.py` -> `script_py.mcbh`, `script_py.mcpc`。
        *   如果 `is_extra_suffix` 为 `false` 或字段被省略（默认行为）：不添加额外后缀。
            *   示例: `script.py` -> `script.mcbh`, `script.mcpc`。

## 其他标准字段

*   **`dependencies`**:
    *   类型: `array of strings`
    *   描述: 列出了目标代码依赖的外部库、框架或模块。这些信息可用于指导代码生成（例如，建议导入）或由构建脚本使用。
    *   示例 (Python): `["json", "requests"]`
    *   示例 (C): `["math", "pthread"]` (可能因系统/构建设置而异)

*   **`buildSettings`**:
    *   类型: `object`
    *   描述: 包含与构建目标源代码相关的设置。此对象的结构和内容高度依赖于 `targetLanguage`。
    *   示例 (C/C++): `{"compilerFlags": "-Wall -Wextra -pedantic", "linkerFlags": "-lm"}`
    *   示例 (Python): `{"installCommand": "pip install -r requirements.txt"}`
    *   示例 (Java): `{"buildTool": "maven", "mavenGoals": ["clean", "install"]}`

*   **`fileSpecificSettings`**:
    *   类型: `array of objects`
    *   描述: 一个可选数组，允许为单个目标文件提供特定配置，覆盖通用项目设置。每个对象通常标识一个目标文件并为其提供设置。每个对象中设置的结构将是领域特定的。
    *   示例 (概念性): `[ { "targetFile": "src_target/utils.c", "settings": { "generateHeaderGuard": true } } ]`

*   **`symbolSpecificSettings`**:
    *   类型: `array of objects`
    *   描述: 一个可选数组，用于为 `mccp_symbols.json` 中定义的单个符号提供特定配置或提示。这可以包括特定变量、函数或类的初始化值、类型提示或生成约束。
    *   示例 (概念性): `[ { "symbolName": "MAX_RETRIES", "settings": { "initialValue": 5 } } ]`

## 示例

以下是针对不同场景的 `mccp_config.json` 示例，基于 MCCP 示例项目和规范。

### 示例 1: C 项目 (基础计算器 - `demo2_calculator_app`)

基于 refactored demo 2 的配置。请注意，对于 C 语言，`is_extra_suffix` 通常被省略或忽略，因为命名约定是根据 `.c` 或 `.h` 扩展名硬编码在工具链中的。示例中的路径已更新为遵循新的项目结构标准（包含 `demo_projects/demo2_calculator_app/` 子路径）。

```json
{
  "projectName": "Basic Calculator App",
  "mccpVersion": "0.0.1",
  "targetLanguage": "C",
  "targetModel": "default_mccp_model",
  "dependencies": [


  ],
  "buildSettings": {
    "compilerFlags": "-Wall -Wextra -pedantic",
    "linkerFlags": ""
  },
  "fileSystemMapping": {
    "behavioralLayerDir": "src_mbh/",
    "symbolicLayerDir": "src_mpc/",
    "targetLayerDir": "src_target/",
    "behavioralLayerExtension": ".mcbh",
    "symbolicLayerExtension": ".mcpc"

  },
  "fileSpecificSettings": [],
  "symbolSpecificSettings": []
}
```

*对应 `src_target/demo_projects/demo2_calculator_app/calculator.c` 和 `src_target/demo_projects/demo2_calculator_app/calculator.h` 的文件映射：*

*   `src_mbh/demo_projects/demo2_calculator_app/calculator_c.mcbh`
*   `src_mpc/demo_projects/demo2_calculator_app/calculator_c.mcpc`
*   `src_mbh/demo_projects/demo2_calculator_app/calculator_h.mcbh`
*   `src_mpc/demo_projects/demo2_calculator_app/calculator_h.mcpc`

### 示例 2: Python 项目 (`demo1_todo_app`)

基于 refactored demo 1 的配置。这里 `is_extra_suffix` 被省略，对于 Python 默认为 `false`。示例中的路径已更新为遵循新的项目结构标准（包含 `demo_projects/demo1_todo_app/` 子路径）。

```json
{
  "projectName": "Simple Todo App",
  "mccpVersion": "0.0.1",
  "targetLanguage": "Python",
  "targetModel": "default_mccp_model",
  "dependencies": [
    "json"
  ],
  "buildSettings": {

  },
  "fileSystemMapping": {
    "behavioralLayerDir": "src_mbh/",
    "symbolicLayerDir": "src_mpc/",
    "targetLayerDir": "src_target/",
    "behavioralLayerExtension": ".mcbh",
    "symbolicLayerExtension": ".mcpc"

  },
  "fileSpecificSettings": [],
  "symbolSpecificSettings": []
}
```

*对应 `src_target/demo_projects/demo1_todo_app/todo_app.py` 的文件映射：*

*   `src_mbh/demo_projects/demo1_todo_app/todo_app.mcbh`
*   `src_mpc/demo_projects/demo1_todo_app/todo_app.mcpc`

### 示例 3: Python 项目，但强制 `is_extra_suffix: true` (假设)(demo3 暂未编写，仅作展示is_extra_suffix的作用)

这是一个假设的 Python 项目示例，其中显式地将文件扩展名添加到 MCCP 文件名中以增加清晰度。

```json
{
  "projectName": "Python Utils Library",
  "mccpVersion": "0.1.0",
  "targetLanguage": "Python",
  "targetModel": "advanced_mccp_model_v2",
  "dependencies": [
    "numpy",
    "scipy"
  ],
  "buildSettings": {
    "installCommand": "pip install --no-deps ."
  },
  "fileSystemMapping": {
    "behavioralLayerDir": "src_mbh/",
    "symbolicLayerDir": "src_mpc/",
    "targetLayerDir": "src_target/",
    "behavioralLayerExtension": ".mcbh",
    "symbolicLayerExtension": ".mcpc",
    "is_extra_suffix": true // 显式为 Python 启用
  },
  "fileSpecificSettings": [],
  "symbolSpecificSettings": []
}
```

*对应 `src_target/path/to/math_utils.py` 的文件映射：*

*   `src_mbh/path/to/math_utils_py.mcbh`
*   `src_mpc/path/to/math_utils_py.mcpc`

本文档提供了使用 `mccp_config.json` 文件配置 MCCP 项目所需的结构和字段定义，特别详细说明了关键的 `fileSystemMapping` 和 `is_extra_suffix` 在不同目标语言下的行为。
