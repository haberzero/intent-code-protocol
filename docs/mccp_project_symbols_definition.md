# MCCP 符号表描述文件 (`mccp_symbols.json`) 规范

本规范详细定义了 MCCP 项目中的符号表文件 `mccp_symbols.json` 的结构、内容及其在整个开发流程中的作用，特别是其如何与 MCCP 的分层结构、文件命名约定和 `mccp_config.json` 配置协同工作。

**注：未来符号表文件应该会经历一次简化，目前的符号表描述过于冗杂，可能不利于开发人员的快速审阅**

## 1. 文件目的与定位

`mccp_symbols.json` 的文件功能贯穿 MCCP 工程的所有构建流程。它集中记录了项目中跨越不同层级（行为描述层 `.mcbh`、符号-伪代码层 `.mcpc` 和目标代码层 `src_target`）的所有关键**符号**（Symbol）信息。

符号包括但可以不限于：

*   函数 (Functions)
*   方法 (Methods)
*   类 (Classes)
*   结构体 (Structs)
*   枚举 (Enums)
*   变量 (Variables, 包括全局变量、成员变量、局部变量)
*   常量 (Constants)
*   接口 (Interfaces)

该文件的主要作用是：

*   **提供符号的单一真相来源 (Single Source of Truth)**：确保不同层级对同一符号的引用具有一致的名称、类型和定义位置。
*   **实现层级间的符号映射**：明确一个符号在其对应的 `.mcbh` 文件、`.mcpc` 文件以及最终 `src_target` 文件中的定义位置，便于工具链进行层间导航和验证。
*   **为 LLM 提供结构化上下文**：在代码生成过程中，LLM 可以查阅符号表，获取关于符号的详细元数据（如类型、参数、返回类型、描述等），从而生成更精确、符合预期的代码。
*   **辅助工具链功能**：支持如符号查找、交叉引用、自动完成、重构等开发工具特性。
*   **辅助反向构建**: 在反向构建现有代码时，符号表是优先被构建的关键组件，它承载了对现有代码结构和符号的初步识别结果。

`mccp_symbols.json` 与 `mccp_config.json` 协同工作：`mccp_config.json` 定义了项目的宏观配置，包括目标语言和文件命名规则 (`is_extra_suffix` 等)，而 `mccp_symbols.json` 则提供了项目内部具体代码元素的详细信息，这些信息会受 `mccp_config.json` 中语言和命名规则的影响（例如，源文件路径的记录方式）。

## 2. 文件位置

根据 MCCP 项目结构约定，`mccp_symbols.json` 文件应存放在项目的配置文件夹中。标准存放路径建议为：

`config/mccp_symbols.json`

这是一个相对于项目根目录的路径，与 `mccp_config.json` 存放于同一目录下，便于集中管理项目配置。

```
/ 项目根目录
├── config/
│   ├── mccp_config.json
│   └── mccp_symbols.json  <-- 文件位置
├── src_mbh/
├── src_mpc/
├── src_target/
└── ...
```

## 3. 总体结构

`mccp_symbols.json` 的顶层结构为一个 JSON **对象**，包含 `project_symbols` 和可选的 `metadata` 字段。`project_symbols` 对象中包含项目级别的符号信息以及按文件组织的符号信息。

```json
{
  "project_symbols": {
    "project_name": "string", // 项目名称
    "global_symbols": [ // 项目全局符号列表
      { /* 符号定义对象 */ }
    ],
    "files": [ // 按文件组织的符号列表
      {
        "file_identifier": "string", // 文件标识符
        "file_path_hint": "string", // 对应目标代码文件路径提示 (相对于 src_target/)
        "file_symbols": [ // 文件内部符号列表
          { /* 符号定义对象 */ }
        ]
      }

    ]
  },
  "metadata": { // 元数据 (可选)
    "description": "string",
    "version": "string",
    "timestamp": "string"

  }
}
```

这种结构便于组织和查找符号，特别是将文件内部符号与全局符号分开管理。

## 4. 符号对象核心字段定义

无论是全局符号还是文件内部符号，每个符号条目（数组中的对象）应包含以下核心字段：

*   **`name`**:
    *   类型: `string`
    *   描述: 符号的名称。这是在代码中引用该符号时使用的标识符。名称应符合目标语言的命名规范。
    *   示例: `"calculate_sum"`, `"UserModel"`, `"MAX_BUFFER_SIZE"`, `"myVariable"`

*   **`type`**:
    *   类型: `string`
    *   描述: 符号的类型或种类。用于区分函数、类、变量等。
    *   常用值示例: `"Function"`, `"Method"`, `"Class/Struct"`, `"Enum"`, `"Variable"`, `"Constant"`, `"Interface"`, `"Typedef"`, `"Boolean"`, `"Integer"`, `"Double"`, `"String"`, `"List<...>"H`, `"PointerTo <...>"H`, `"ConstString"` 等，具体应与目标语言相关。

*   **`scope`**:
    *   类型: `string`
    *   描述: 符号的作用域。指明该符号在哪个范围内是可见和有效的。
    *   常用值示例: `"global"`, `"file"`, `"module"`, `"class"`, `"function"`, `"local"`, `"file_static"`, `"public"`, `"private"`。更精确的描述可以包含文件、类或函数名，例如 `"file:utils_c.mcpc"`, `"class:UserModel"`, `"function:calculate_sum"`。

*   **`description`**:
    *   类型: `string` (可选)
    *   描述: 符号的简要文字描述。可以包含其用途、行为等信息，用于文档生成或LLM理解。
    *   示例: `"Calculates the sum of two integers."`

*   **`value_hint`**:
    *   类型: `string` (可选, 主要用于 `Constant`, `Variable` 类型)
    *   描述: 对于常量或具有默认值的变量，提供其值的提示字符串。
    *   示例: `"\"todos.json\""`, `"0"`, `"3.14159"`

*   **`members`**:
    *   类型: `array of objects` (可选, 主要用于 `Class/Struct`, `Enum` 类型)
    *   描述: 类/结构体成员或枚举项列表。数组中的每个对象描述一个成员或项，其结构类似简化版的符号定义（包含 `name`, `type`, `description` 等）。
    *   示例: `[{"name": "description", "type": "Variable String", "description": "任务描述"}, {"name": "is_completed", "type": "Variable Boolean", "description": "完成状态"}]`

*   **`parameters`**:
    *   类型: `array of objects` (可选, 主要用于 `Function`, `Method` 类型)
    *   描述: 函数或方法的参数列表。数组中的每个对象描述一个参数。
    *   参数对象子字段:
        *   `name`: `string` (参数名称)
        *   `type`: `string` (参数的数据类型，应与符号类型一致)
        *   `description`: `string` (参数描述, 可选)
    *   示例: `[{"name": "a", "type": "Integer"}, {"name": "b", "type": "Integer"}]`

*   **`return_type`**:
    *   类型: `string` (可选, 主要用于 `Function`, `Method` 类型)
    *   描述: 函数或方法的返回类型。应与符号类型一致。
    *   示例: `"Integer"`, `"Void"`, `"List<TodoItem>"`

*   **`dependencies`**:
    *   类型: `array of strings` (可选)
    *   描述: 该符号直接依赖的其他符号的名称列表。用于分析代码结构和依赖关系。这里的名称应是 `name`。
    *   示例: `["add_numbers", "log_message"]`

*   **`language_specific_details`**:
    *   类型: `object` (可选)
    *   描述: 包含针对特定目标语言的额外信息，这些信息不属于通用符号属性。其结构和内容完全取决于目标语言和具体需求。
    *   示例 (C++): `{"is_virtual": true, "access_specifier": "public"}`
    *   示例 (Python): `{"is_static_method": false, "decorators": ["@classmethod"]}`

## 5. 与层级文件路径的关联

虽然新的符号表结构将符号按文件分组，并通过 `file_path_hint` 给出目标代码文件路径提示，但为了明确符号在 MCCP 各层级描述文件中的对应位置，符号定义对象中**可以**（或在未来的规范中将强制）包含以下字段：

*   **`source_file_behavioral`**:
    *   类型: `string`
    *   描述: 包含此符号行为描述的 `.mcbh` 文件的路径。路径应为相对于 `src_mbh/` 目录的路径。如果某个符号只在 `.mcpc` 或 `src_target` 中有明确体现（例如某个局部变量），而 `.mcbh` 中没有直接对应的描述，此字段可为空字符串或省略。
    *   示例: `"demo_projects/demo1_todo_app/todo_app_py.mcbh"`

*   **`source_file_symbolic`**:
    *   类型: `string`
    *   描述: 包含此符号详细符号-伪代码描述的 `.mcpc` 文件的路径。路径应为相对于 `src_mpc/` 目录的路径。这是最重要的关联字段之一，通常每个符号都会对应一个 `.mcpc` 文件位置。
    *   示例: `"demo_projects/demo1_todo_app/todo_app_py.mcpc"`

*   **`source_file_target`**:
    *   类型: `string`
    *   描述: 包含此符号最终目标语言代码的文件的路径。路径应为相对于 `src_target/` 目录的路径。此字段与文件对象中的 `file_path_hint` 相同，提供冗余以方便直接在符号级别查找。
    *   示例: `"demo_projects/demo1_todo_app/todo_app.py"`

**与文件命名约定和 `is_extra_suffix` 的关联：**

`mccp_symbols.json` 中的 `source_file_behavioral` 和 `source_file_symbolic` 字段必须准确地反映项目中实际存在并遵循命名约定的 `.mcbh` 和 `.mcpc` 文件路径。

关键点在于：

*   **`.mcbh` 和 `.mcpc` 文件路径中是否包含额外后缀 (`_h`, `_c`, `_cpp`, `_py`, `_java` 等) 完全取决于 `mccp_config.json` 中指定的 `targetLanguage` 和 `fileSystemMapping.is_extra_suffix` 的规则**，以及原始目标文件 (`src_target`) 的扩展名。
*   **符号表文件 (`mccp_symbols.json`) 本身不决定命名约定，它只是记录由约定产生的实际文件路径。**
*   在符号条目中记录的路径（`source_file_behavioral`, `source_file_symbolic`, `source_file_target`）应是**相对于**其各自层级根目录 (`src_mbh/`, `src_mpc/`, `src_target/`) 的路径。

工具链在生成或更新 `mccp_symbols.json` 时，会根据 `mccp_config.json` 的文件系统映射规则来计算出正确的 `.mcbh` 和 `.mcpc` 文件路径，并将其记录到符号表中。

## 6. 符号表在 MCCP 工作流程中的作用

符号表是 MCCP 各个抽象层级协同工作的核心构件，尤其在行为描述层和符号-伪代码层的构建与迭代中起着至关重要的作用：

1.  行为描述层构建阶段:
    * 在大模型将自然语言需求拆解为行为描述并构建初步软件框架（文件、类、函数等）时，会初步创建符号表。
    * 此时，符号表会记录行为描述中显式提到的或根据描述推断出的主要符号（如类名、函数名、重要变量名）及其所属文件和大致作用域。这一阶段的符号表可能不包含详细的局部变量，但框架结构和关键全局/文件级符号已被捕捉。

2.  符号-伪代码层构建阶段:
    * 大模型根据行为描述层的内容生成符号-伪代码层时，会进一步填充和更新符号表。
    * 这个阶段会细化符号表，记录伪代码中出现的更具体的符号，例如函数参数、局部变量、类成员变量、以及伪代码中体现出的函数/方法调用和类实例化等关系。
    * 伪代码中的导入/依赖声明（如 `import X from "file"`）会用于填充或更新符号表中的 `file_depend` 字段，明确文件间的依赖关系。

3.  迭代与更新过程:
    * 无论是开发人员在行为描述层进行的修改，还是大模型在生成伪代码后进行的自我修正，任何引入新符号、删除符号、修改符号名称/作用域、或改变依赖关系的操作，都应触发符号表的迭代更新。
    * 大模型负责分析这些修改，并同步反映到符号表中。例如，如果行为描述增加了某个功能模块的描述，大模型可能会在符号表中新增对应的文件、类和函数条目。如果修改了某个函数的实现方式，引入了新的局部变量，符号表该函数条目下的 `var` 列表就应被更新。
    * 在每次重要的生成或修改后，符号表都应被重新验证，确保其与当前的行为描述和符号-伪代码层内容一致。

4.  符号-伪代码层的使用与验证:
    * 在生成符号-伪代码时，大模型会参考符号表，使用其中记录的规范符号名称，并根据依赖关系组织伪代码结构。
    * 生成伪代码后，可以根据符号表对伪代码中的符号引用进行静态检查，验证所有调用的函数、访问的变量是否都在符号表中存在且在当前作用域可访问，从而捕获潜在的“幻觉”引用。

5.  文件依赖管理 (`file_depend`):
    * 符号表中的 `file_depend` 字段明确记录了文件间的显式依赖。
    * 这对于大模型在最终代码生成阶段组织文件、确定编译/解释顺序（如果适用）以及生成正确的导入语句至关重要。它确保了代码生成过程能够遵循项目定义的模块化结构和依赖关系。

简而言之，符号表是 MCCP 实现“精确化、可信化、可控化”的关键技术载体，它为大模型的代码生成和项目结构的理解提供了必要且精确的元数据支持。

## 7. 示例

以下提供一个 `mccp_symbols.json` 的示例，基于 refactored demo 1 (Python 项目)。

**注：未来符号表文件应该会经历一次简化，目前的符号表描述过于冗杂，可能不利于开发人员的快速审阅**

```json
{
  "project_symbols": {
    "project_name": "demo1_todo_app",
    "global_symbols": [
      {
        "name": "DATA_FILE_PATH",
        "type": "Constant String",
        "scope": "global",
        "description": "存储待办事项数据的文件路径",
        "value_hint": "\"todos.json\"",
        "source_file_behavioral": "", // Global constant might not have a specific MBH file
        "source_file_symbolic": "demo_projects/demo1_todo_app/todo_app_py.mcpc", // Used in MPC
        "source_file_target": "demo_projects/demo1_todo_app/todo_app.py" // Used in target code
      }
    ],
    "files": [
      {
        "file_identifier": "main_application_logic",
        "file_path_hint": "demo_projects/demo1_todo_app/todo_app.py",
        "file_symbols": [
          {
            "name": "todo_list",
            "type": "Variable List<TodoItem>",
            "scope": "file",
            "description": "用于存储所有待办事项对象的列表",
            "source_file_behavioral": "demo_projects/demo1_todo_app/todo_app_py.mcbh", // Mentioned in behavior?
            "source_file_symbolic": "demo_projects/demo1_todo_app/todo_app_py.mcpc",
            "source_file_target": "demo_projects/demo1_todo_app/todo_app.py"
          },
          {
            "name": "TodoItem",
            "type": "Class/Struct",
            "scope": "file",
            "description": "表示一个待办事项的数据结构",
            "members": [
              {
                "name": "description",
                "type": "Variable String",
                "description": "待办事项的具体文本描述"
              },
              {
                "name": "is_completed",
                "type": "Variable Boolean",
                "description": "标记待办事项是否已完成的状态"
              }
            ],
             "source_file_behavioral": "demo_projects/demo1_todo_app/todo_app_py.mcbh",
             "source_file_symbolic": "demo_projects/demo1_todo_app/todo_app_py.mcpc",
             "source_file_target": "demo_projects/demo1_todo_app/todo_app.py"
          },
          {
            "name": "load_todos",
            "type": "Function",
            "scope": "file",
            "description": "从预定义文件路径加载待办事项列表",
            "parameters": [],
            "return_type": "List<TodoItem>",
            "source_file_behavioral": "demo_projects/demo1_todo_app/todo_app_py.mcbh",
            "source_file_symbolic": "demo_projects/demo1_todo_app/todo_app_py.mcpc",
            "source_file_target": "demo_projects/demo1_todo_app/todo_app.py",
            "local_symbols": [] // Local symbols can be nested or listed here
          },
          {
             "name": "main_program_loop",
             "type": "Function",
             "scope": "file",
             "description": "应用程序的主循环，处理用户命令",
             "parameters": [],
             "return_type": "Void", // Corrected return type for a loop function
             "source_file_behavioral": "demo_projects/demo1_todo_app/todo_app_py.mcbh",
             "source_file_symbolic": "demo_projects/demo1_todo_app/todo_app_py.mcpc",
             "source_file_target": "demo_projects/demo1_todo_app/todo_app.py",
             "local_symbols": [
               {
                 "name": "user_command",
                 "type": "Variable String",
                 "scope": "local",
                 "description": "用户输入的命令字符串"
               },
                {
                 "name": "parts",
                 "type": "Variable List<String>",
                 "scope": "local",
                 "description": "分割用户命令得到的字符串列表"
               }
             ]
          }

        ]
      }
    ]
  },
  "metadata": {
    "description": "基于MCCP demo1_todo_app的符号表，定义了项目中使用的主要变量、函数和结构体及其作用域。",
    "version": "1.0"
  }
}
```
*注意：示例中的 `source_file_*` 路径是相对于 `src_mbh/`, `src_mpc/`, `src_target/` 目录的完整路径，包含了示例项目的子目录结构 (`demo_projects/demo1_todo_app/`)。*

## 8. 更新与维护

`mccp_symbols.json` 文件需要与项目的 `.mcbh`, `.mcpc` 文件以及最终的 `src_target` 代码保持同步。随着项目的开发，新的符号会被添加，现有符号可能会被修改或删除。维护符号表的准确性至关重要。

符号表的更新与维护可以采用以下策略：

1.  **手动维护**: 开发者在添加、修改或删除符号时，手动编辑 `mccp_symbols.json` 文件。这种方式适用于小型项目或早期原型，开发人员对符号表的控制力度最大，但同样工作量也最大。
2.  **半自动维护**: 利用工具链提供辅助功能。例如，工具可以扫描 `.mcpc` 文件，检测新增或修改的符号，并提示开发者更新符号表；或者提供命令行工具，通过特定语法从 `.mcpc` 或 `src_target` 提取符号信息并生成/更新 JSON 条目，开发者再进行审阅和确认。
3.  **全自动生成/更新**: 工具链能够自动扫描 `.mcpc` 或 `src_target` 文件，识别符号及其属性（类型、作用域、位置、参数等），并自动生成或更新 `mccp_symbols.json` 文件。这是最理想的状态，减少了人为错误和维护负担，但需要强大的解析和分析能力。对于从 `.mcpc` 到 `mccp_symbols.json` 的正向生成是比较直接的；从 `src_target` 到 `mccp_symbols.json` 的反向生成则需要依赖特定语言的解析器 (Parsers)。

符号表的准确性和完整性直接关系到整个 MCCP 工程的可信度。基于 MCCP 的设计哲学，其维护应遵循以下原则：

* 主要由大模型维护和更新: 符号表的创建、填充、以及随着行为描述层和符号-伪代码层迭代而产生的更新，应主要由大语言模型自动执行。大模型能够更全面地分析各层级内容，并根据预设规则进行符号提取和关系构建。
* 开发人员的核心职责是审查: 开发人员不应该频繁地手动修改符号表 JSON 文件。他们的核心职责是审查大模型生成的行为描述层、符号-伪代码层以及随之更新的符号表。开发人员应重点检查符号命名是否合理、作用域是否正确、依赖关系是否准确，以及符号表是否完整反映了当前的项目结构。推荐结合半自动和全自动的方式，例如主要通过扫描 `.mcpc` 文件自动生成，但允许开发者手动添加额外信息（如 `description`）或覆盖自动提取的细节。
* 手动修改应尽量避免: 直接手动编辑 `mccp_symbols.json` 文件应尽量避免。如果开发人员发现符号表有误或需要调整，最优的方式是回到行为描述层进行相应的修改（因为行为描述层是开发者核心的投入领域），然后触发大模型根据行为描述的更新来自动修正符号表和符号-伪代码层。只有在少数、明确需要直接干预元数据的情况下，才考虑手动修改，且修改后必须通知大模型或工具进行同步和校验。

这种维护模式让符号表的更新能够配合行为描述层和伪代码层的变化，减轻人为工作，并充分利用大模型的能力。
