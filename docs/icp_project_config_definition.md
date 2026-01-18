# ICP 配置文件 (`icp_config.json`) 规范

`icp_config.json` 文件是 ICP 项目中的核心组成部分，作为项目特定的配置清单。它定义了 ICP 工程的一些基本信息，比如项目文件的额外后缀名定义、目标语言、工程名称等。

## 文件位置

根据 ICP 项目结构约定，`icp_config.json` 文件应存放在项目的配置文件夹中。标准存放路径建议为：

`config/icp_config.json`

这是一个相对于项目根目录的路径，与 `icp_symbols.json` 存放于同一目录下，便于集中管理项目配置。

```text
/ 项目根目录
├── config/
│   └── icp_config.json  <-- 文件位置
├── src_ibc/
└── src_target/
```

对于包含多个独立模块/应用的更大型项目，或者像本仓库中的示例项目那样，可能在每个模块/应用自己的目录下包含一个 `config/` 文件夹及其对应的 `icp_config.json` 和 `icp_symbols.json`，以实现模块级别的配置管理。例如：`demo_projects/demo1_todo_app/config/icp_config.json`。

## 字段定义

以下是 `icp_config.json` 中包含的字段：

* **`projectName`**:
  * 类型: `string`
  * 描述: ICP 项目的人类可读名称。用于标识和文档生成。
  * 示例: `"basic_calculator_app"`

* **`icpVersion`**:
  * 类型: `string`
  * 描述: 指定项目所基于的 ICP 框架或协议版本。有助于确保与工具链的兼容性。
  * 示例: `"0.0.2"`

* **`targetLanguage`**:
  * 类型: `string`
  * 描述: 定义生成的目标源代码的编程语言。
  * 示例: `"C"`

## 文件系统映射和命名约定 (`fileSystemMapping` 对象)

这是一个可选但强烈推荐的对象，它定义了 `src_mbh` 和 `src_mpc` 中的结构如何映射到 `src_target`
如果省略，将应用默认的工程结构。本项参数的设计目的是为了适应不同的历史代码结构和项目需求。
例如，在一个大型项目中，开发者只希望在某个小模块中使用 ICP 技术，而不希望对整个项目进行全面改造。
此时，可以通过 `fileSystemMapping` 来指定该小模块的 ICP 层文件的目录结构，以及目标代码的目录结构，从而实现对特定模块的 ICP 支持，同时又不过多影响原始项目的文件目录结构

```json
"fileSystemMapping": {
  "behavioral_layer_dir": "src_ibc/", // 行为描述层目录，允许存在不同的工程结构，便于适配不同的历史性代码
  "target_layer_dir": "src_target/",  // 目标代码目录，允许存在不同的工程结构，便于适配不同的历史性代码
  "is_extra_suffix": false // 默认值，与文件命名有关，见下方规则
}
```

* **`behavioral_layer_dir`**:
  * 类型: `string`
  * 描述: 行为描述层文件的根目录。
  * 标准值: `"src_ibc/"`

* **`target_layer_dir`**:
  * 类型: `string`
  * 描述: 目标源代码文件的根目录。
  * 标准值: `"src_target/"`

* **`is_extra_suffix`**:
  * 类型: `boolean`
  * 描述: 此字段控制是否在对应的 `.ibc` 文件的基本文件名之后添加一个派生自原始目标文件扩展名的额外后缀。这对于区分对应不同目标文件类型（例如 C 语言中的 `.c` 和 `.h`）的 ibc 文件至关重要。事实上，此字段主要是针对C/C++进行设计的。

  * **通用行为 (应用时):** 如果为 `true`，则在 ibc 层扩展名 (`.ibc`) 之前，会在基本文件名后附加一个下划线 (`_`) 跟着原始目标文件的扩展名（不包含开头的点）。
    * 示例: 目标文件 `file.ext` -> ibc 文件 `file_ext.ibc`。

  * **C 语言家族 (`C`, `C++`, 等):**
    * 对于 `targetLanguage` 设置为 C 语言家族（例如 `"C"`, `"C++"`）时，`is_extra_suffix` 的行为是**隐式为 `true`** 的，并且通常不应在配置中显式设置为 `false`，因为工具链会强制执行特定的 C 语言家族命名规则，而无论此标志在 JSON 中的值如何。
    * 额外后缀是根据 C/C++ 文件类型**固定**的：
      * 对于头文件（例如 `.h`, `.hpp`）：额外后缀是 `_h`。
        * 示例: `utils.h` -> `utils_h.ibc`。
      * 对于源文件（例如 `.c`, `.cpp`, `.cc`, `.cxx`）：额外后缀分别是 `_c` 或 `_cpp`。
        * 示例: `main.c` -> `main_c.ibc`。
        * 示例: `module.cpp` -> `module_cpp.ibc`。

  * **其他语言（例如 `Python`, `Java`, `JavaScript`）:**
    * 对于其他语言，`is_extra_suffix` 字段是**可配置的**。
    * 如果 `is_extra_suffix` 为 `true`：额外后缀直接派生自目标文件的扩展名（例如 `.py` -> `_py`）。
      * 示例: `script.py` -> `script_py.ibc`。
    * 如果 `is_extra_suffix` 为 `false` 或字段被省略（默认行为）：不添加额外后缀。
      * 示例: `script.py` -> `script.ibc`。
