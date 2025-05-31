# MCCP (Model Context Code Protocol) 文档

## 1. MCCP 简介与核心理念

构想中的一种半自然语言编程描述系统，目前，我将其命名为 MCCP: Model Context Code Protocol。这事实上不是一门新的编程语言，且永远都不应该成为一种可以直接“运行”或者“编译”的编程语言。

核心理念:

*   超级中间件: 它应当是一种让大语言模型能够和实际编程语言进行“精确化、可信化、可控化沟通”的约定，是一种伪代码形式的提示词协议，是一种沟通传统编程语言和大模型的超级中间件。
*   稳定可控与精细修改: 更通俗地来讲，它应该能让大模型生成的代码变得稳定可控，且允许开发人员进行精细化修改、在多个抽象层次修改，并关联影响到其它层级的内容。
*   快速演进: 这个协议自诞生之初就注定了它的快速演进性质，它永远都会跟随大模型本身的进化而快速地演进，任何被彻底定义的语法结构都会导致其丧失快速迭代进化的能力。

从抽象分层的描述中可以看出，MCCP 几乎就是对传统软件开发的工程构建哲学的具象化拆解重构。它“几乎就是”一门新的编程语言，一门针对现代大模型构建的编程语言。

## 2. MCCP 的基本结构 - 三个抽象层级

MCCP 包含三个核心抽象层级，由高到低分别是：自然语言提示词层，半自然语言行为描述层，符号-伪代码层。这三个层级共同构成了从人类需求到接近可执行代码的逐级细化路径。

### i. 自然语言提示词层

自然语言提示词层就是人类之间相互沟通、人类和语言模型进行直接沟通的最基本自然的口语化语法。对于 MCCP 而言，本层指代了对“软件需求/编程需求”的直接口语化描述。

这是用户与 MCCP 系统交互的起点，用户以自由的自然语言表达他们的编程意图和需求。

简单示例:

*   `创建一个计算两个数字之和的 Python 函数。`
*   `帮我写一个读取配置文件的类，并提供获取配置项的方法。`

### ii. 半自然语言行为描述层

半自然语言行为描述层是对自然语言提示词层的具象化需求拆解。在此层级，最初的软件框架将会形成。

核心构建内容:

*   项目文件夹的结构
*   软件的基本构成框架
*   软件的运行流程描述
*   软件中的类、函数、变量定义
*   业务分支逻辑的处理方式

所有这些内容，都是对软件结构的实际行为描述。在构建此层级时，代码的关键符号表将会被生成，包括但不限于关键的全局变量、全局单例等符号会被精确描述，从而能够在后续生成可信的伪代码间的关联结构，防止模型幻觉带来的调用不存在的函数/变量/实例等问题。

我们可以用一种不完全准确的形容：半自然语言行为描述层就像是一种对于软件源代码的完备注释。在与大模型的首次几轮的需求对话结束后，开发人员应该花费超过总工程一半的时间在半自然语言行为描述层进行进一步开发。

注: 为了方便起见，本层级在后续内容将被称为行为描述层。

行为描述层概念示例:

```behaviorcode

等待填充

```


结构化注释:

结构化注释主要在行为描述层中出现。注释主要会被分为两种类型：人员注释 `//` 和模型注释 `@`。所有注释都可以被封装在一个“符号”中，使用 `#` 作为这个“符号”的标注。这类似于 C 语言的宏定义，在构建时会将 `#` 定义的内容替换到对应的位置。`#`、`//`、`@` 都只在每一行的开头出现时才具备其功能性含义。

*   `//`: 人员注释，提供给开发者阅览，在符号-伪代码层的生成过程中会被原封不动地传递，永远不会被大模型看见。
*   `@`: 模型注释，提供给大模型进行额外的行为调整。当有对代码结构的特化需求，不方便或不想直接嵌入行为描述时，可以在关键符号上方增加模型注释来特化模型行为。
*   `#`: 封装符号，用于定义结构化注释块，如 `#define 注释名称: { ... }`。在行为描述中使用 `# 注释名称` 时，该位置将被定义块 `{ ... }` 的内容替换。

### iii. 符号-伪代码层

符号-伪代码层已经非常接近实际的可编译/可运行代码。实际上，本层是具备标准客观的语法结构的层级，具备现代编程语言中最常见的所有元概念和结构，包括但不限于：分支/循环语法，顺序执行结构，变量定义，函数定义，类定义，配置定义，宏定义，等等。

对于任何一个具备良好编程素养的开发人员来说，他们应该能够根据此层级的伪代码结构编写出具备完全相同逻辑功能的代码，仅仅在少量细节语法结构等内容上存在区别。

此外，本层级应该已经具备近乎完整的符号表记录和符号使用，包括但不限于变量命名、函数命名、类命名等。伪代码中的互相依赖关系应该能够完全和符号表进行一一对应，从而确保后续大模型根据伪代码生成实际代码时，几乎一定能够构建出具备正确依赖关系和正确语法的可编译/可执行代码，最大限度地避免幻觉问题，同时最大限度地减少不同语言模型之间的代码内容差异，使符号-伪代码层具备良好的可迁移性。

需要特别注意: 理论上来讲，开发人员不应该在符号-伪代码层投入过多的精力进行精细化微调，也不应该过分纠结于符号-伪代码层的具体语法。本层级的构建结果在未来一定会随着大模型的进化而演进。开发人员应该进行思路的转变，我们需要成为过去类似“产品经理”的角色，被精细化调整的应当是需求、行为描述，而不是太过于细节和具体的业务代码。

符号-伪代码层概念示例 (基于上述计算器示例):

```pseudocode

等待填充

```

与符号表的精确对应:
伪代码中的所有符号（如 `Calculator`, `add`, `num1`, `config_filepath`, `read_config`, `calc_instance`, `operation`, `file_handle` 等）都应该在符号表中有所记录，并且伪代码中的调用 (`calc_instance.add(...)`, `new Calculator()`, `read_all(...)`) 都应该能够通过符号表进行查找和验证其存在性及依赖关系。例如，`import Calculator from "src.calculator"` 语句暗示 `main.mccp_pseudo` 文件依赖于 `src.calculator` 文件，并且使用了其中定义的 `Calculator` 类。符号表中的 `file_depend` 字段可以记录这种文件间的显式依赖。

## 3. MCCP 具备的基本功能/特征

### i. 不同层级之间的修改反应机制

MCCP 的一个核心特征是支持在任何一个抽象层级（包括最终生成的实际代码）进行的修改都能直接反应到相关联的抽象层上，并由大模型进行协调更新。

修改场景示例及流程:

当一个开发人员修改了行为描述层的内容，比如修改了对某个函数实现方式的描述（例如，修改了 `add` 函数的描述，要求它处理大整数）：

1.  大模型判断与反馈（针对自然语言提示词层）:
    *   大模型开始一轮判断：软件的核心功能是否被修改？这个修改是否重要到需要在用户最初的自然语言提示/需求中添加一个特别的备注，注明某函数应该用被修改后的特定方式（如支持大整数）实现。
    *   根据判断内容，向用户提交修改结果（如提议在原需求旁增加一个备注 `(注: 计算函数需支持大整数运算)`），交由开发者判断修改是否成立。

2.  符号-伪代码层对应修改:
    *   符号-伪代码层应该被对应修改，使得伪代码能够准确对应开发人员在行为描述层进行的新修改（例如，修改伪代码中的 `add` 方法实现或增加对大整数库的依赖描述）。
    *   修改结果应交由开发者判断是否成立。

3.  符号表对应修改:
    *   假如修改中涉及到了对符号表的修改（例如，引入了一个新的大整数处理类或函数），则符号表（`symbol_table.json`）中的符号以及依赖关系等也应当被对应修改。

上述所有操作，在理论中都应该被大语言模型自动执行。

概念性修改流程描述 (Conceptual Pseudocode/Steps):

```text
// 函数: ProcessModification(modification_details)
// 输入: modification_details - 描述修改内容和所在层级的信息

function ProcessModification(modification_details):
    layer = modification_details.source_layer
    content = modification_details.content
    target_element = modification_details.target_element // e.g., "Calculator.add function"

    print("Modification detected in layer: " + layer)
    print("Target element: " + target_element)

    // Step 1: Analyze impact and update Natural Language layer (conceptual)
    if is_core_function_impacted(modification_details):
        proposed_nl_note = generate_nl_note(modification_details)
        submit_for_developer_review("Propose adding note to Natural Language requirement:", proposed_nl_note)

    // Step 2: Update Behavior Description layer (already done by developer, analyze for context)
    // No explicit action here, as this function is triggered *by* the BD layer modification.
    analyze_behavior_description_context(content, target_element)

    // Step 3: Update Symbol-Pseudocode layer
    proposed_pseudocode_changes = generate_pseudocode_changes(modification_details)
    submit_for_developer_review("Propose changes to Symbol-Pseudocode layer:", proposed_pseudocode_changes)

    // Step 4: Update Symbol Table if necessary
    if requires_symbol_table_update(modification_details):
        proposed_symbol_table_changes = generate_symbol_table_changes(modification_details)
        submit_for_developer_review("Propose changes to Symbol Table:", proposed_symbol_table_changes)

    // Wait for developer approval on proposed changes...
    // Upon approval, apply changes to corresponding files.

    print("Modification processing complete.")

// Helper conceptual functions (executed by LLM):
function is_core_function_impacted(details):
    // LLM logic to analyze if the change significantly alters a primary feature
    return boolean

function generate_nl_note(details):
    // LLM logic to draft a concise note for the NL requirement
    return string

function generate_pseudocode_changes(details):
    // LLM logic to modify relevant pseudocode section based on BD changes
    return pseudocode_diff_or_new_snippet

function requires_symbol_table_update(details):
    // LLM logic to check if new symbols are introduced or relationships changed
    return boolean

function generate_symbol_table_changes(details):
    // LLM logic to propose JSON patches or new entries for symbol table
    return json_patch_or_new_entries
```

### ii. 兼容性描述文件

MCCP 包含一个兼容性描述文件，此文件对应于传统软件工程中的“配置文件”的概念。此文件在当前的初步定义中是一个 `json` 文件。

用途: 描述当前 MCCP 工程构建所需的关键外部依赖和环境信息，确保协作的一致性和构建的可预测性。

文件内容:

*   当前 MCCP 工程调用的具体大模型: （`"llm_used"`）
    *   示例: `Qwen/ChatGPT/DeepSeek` 等。
    *   用途: 确保协作的人员在对 MCCP 工程进行构建时不会因为具体使用的模型的差异造成难以解决的合并冲突问题。
*   当前 MCCP 工程最终所能生成的具体编程语言: （`"target_language"`）
    *   示例: `Python/C++/JAVA` 等。
    *   用途: 虽然理论上任何一个 MCCP 工程都应该能被构建为任何一门具备完备性的现代编程语言，但考虑到不同语言的特定功能意义、独特的语法定义/函数库/功能糖 等，限定最终的目标语言是对兼容性和可构建性的考量。
*   当前 MCCP 需要调用的功能库/源代码库: （`"dependencies"`）
    *   示例: `requests=2.28.1`, `pytest=7.0.0`, `my_internal_lib=1.2.0` 等。可以指定版本。
    *   用途: 现代软件工程离不开各种软件库。MCCP 也应当对当前工程所依赖的库/现有代码等内容做出定义，并且进行版本对齐，避免重复造轮子。

概念性 `mccp_config.json` 示例结构:

```json
{
    "mccp_version": "0.1",
    "project_name": "SimpleCalculator",
    "llm_used": "GPT-4o",
    "target_language": "Python",
    "dependencies": {
        "standard_libraries": [
            "json",
            "sys"
        ],
        "third_party_libraries": {
            "requests": "2.28.1",
            "pytest": "7.0.0"
        },
        "local_code_bases": [
            {
                "name": "my_common_utils",
                "path": "../my_common_utils_repo",
                "version": "1.2.0"
            }
        ]
    },
    "build_settings": {
        "output_directory": "generated_src",
        "enable_optimizations": false
    }
}
```

### iii. 符号表

符号表是一个贯穿整个 MCCP 工程的 `json` 文件。它是行为描述层和符号-伪代码层之间以及符号-伪代码层与最终代码生成之间进行精确沟通和依赖检查的核心。

重要性与迭代过程:

*   贯穿: 符号表在行为描述层和符号-伪代码层被构建的过程中应该被反复迭代。
*   初步构建: 生成行为描述层之后应该生成一个初步的符号表。
*   更新完善: 生成符号-伪代码层以后，符号表将会被再进行一次更新。
*   持续迭代: 在后续开发人员进行反复迭代的过程中，符号表会逐渐趋于完整，并且逐渐将 MCCP 工程中所有可能涉及到的符号内容都存储起来。
*   依赖存储: 除了符号本身，符号表中还会存储一些文件之间的依赖关系（`file_depend`），供代码生成过程参考使用。
*   LLM 主导更新: 符号表不应该被开发人员过多地手动修改。我们应该尽可能多地借助大模型的能力对符号表进行更新，审查才是重点，手动修改不应该成为重点。

用户提供的 JSON 示例结构及说明:

```json
{
    "global": {
        "var": [
            "some global var"
        ],
        "class": [
            "some class name"
        ],
        "func": [
            "some func name"
        ]
    },
    "file1": {
        "path":"path to file 1",
        "file_depend":"file2",
        "class_a": {
            "func": [],
            "var": []
        },
        "class_b": {
            "func": [],
            "var": []
        },
        "func_a": {
            "var": []
        },
        "var": []
    },
    "file2": {
        "path":"path to file 2",
        "class_c": {
            "func": [],
            "var": []
        },
        "func_b": {
            "var": []
        },
        "var": []
    }
}
```

*   `global`: 存储全局范围内可访问的符号，如全局变量 (`var`)、全局类 (`class`)、全局函数 (`func`)。
*   `fileX`: 每个顶级键（除 `global` 外）代表一个 MCCP 工程中的文件（通常是行为描述层文件或符号-伪代码层文件）。
    *   `path`: 该文件在项目中的相对路径。
    *   `file_depend`: 该文件显式依赖的其他文件。这有助于大模型在生成代码时按正确的顺序处理文件或理解跨文件调用。
    *   `class_a`, `class_b`, `class_c` 等: 文件内部定义的类。每个类下包含其成员函数 (`func`) 和成员变量 (`var`) 的列表。
    *   `func_a`, `func_b` 等: 文件内部定义的独立函数。每个函数下包含其局部变量 (`var`) 的列表。
    *   `var`: 文件作用域内的变量列表（不属于任何类或函数）。

这个结构清晰地展示了符号的作用域（全局、文件、类、函数）以及文件间的依赖关系，为大模型生成具有正确符号引用和依赖的代码提供了精确的指导。

### iv. 结构化注释

详见本节 2.ii 中关于结构化注释的描述。

补充说明:

*   人员注释 `//`: 完全是给人看的，不会影响模型行为或最终代码生成逻辑。
*   模型注释 `@`: 用于向模型传递额外的、不适合放在行为描述主体中的指令或约束。例如，指定特定算法、性能要求、安全考虑等。
*   `#define` 机制: 提供了一种在行为描述层中复用常用注释块的方式，使得文档更整洁。在构建过程中，`#define 注释名称: { ... }` 定义的内容会替换所有 ` # 注释名称` 出现的文本位置。

范例回顾:

```text
#define 注释1:
{
// 这只是一段给后来者看的玩笑性注释
@ 此处必须使用双向链表进行实现
}

// 在行为描述中使用:
// class MyDataStructure:
//     # 注释1
//     def process_elements():
//         pass
```
在构建时，`# 注释1` 会被替换为 `{ // ... \n @ ... }`。

### v. 宏定义 (暂定)

宏定义，即 `#` 开头定义的符号在构建过程中会被替换为实际的代码或文本内容。结构化注释的 `#define` 形式就是宏定义的一种表现形式。

引入原因:

*   MCCP 的最初定义者（是的就是我）在定义 MCCP 时主要是一个嵌入式 C++ 程序员，认为宏定义对于 MCCP 而言有很大可能是一种必需品，没有任何理由，仅仅是一种强烈的直觉。
*   MCCP 本质上是一种约定、一个协议，不是真正的编程语言，可以在未来弃用该特性，只需将历史版本的宏定义直接替换为实际文字即可。

潜在争议与必要性:

宏定义是一种有很大争议的语言特性，大多数现代编程语言不鼓励乃至不支持大范围使用。然而，在 MCCP 这种非编译/运行的协议中，宏定义可能提供一种灵活的文本替换或结构复用机制。其必要性仍需在实践中检验。

引入限制:

为了避免宏定义这一概念的滥用，必须做出以下限制（部分限制在未来可能成为强制性的）：

*   a. 内容行数限制: 宏定义的内容*不应该*超过 7 行，除开大括号 `{}` 所占据的行以外，实际具备含义的宏定义内容不应该超过 5 行。这不是一个强制限制，而是超过 80% 情况下应遵守的约定。
*   b. 嵌套深度限制: 宏定义的嵌套*不能*大于 3 次。这在未来应当会成为一个强制性的限制。超过 3 层的宏定义嵌套应该导致 MCCP 的构建器报错警告并停止运行。这是为了避免复杂的、难以理解的嵌套结构。
*   c. 用途限制: 宏定义*不是*拿来定义变量的，也*不是*拿来定义配置的。对于 C/C++ 程序员而言，请不要写出 `#define mian main` 的想法。宏定义用于定义变量或配置会导致陷入“过分具体的代码”中，并可能导致文件间的强依赖。请善用兼容性描述文件（用于配置）和符号表（用于变量/符号定义和管理）。
*   d. 文件间传递限制: 除结构化注释以外的宏定义*不应该*在两个文件之间传递。这同样是为了避免文件间的强耦合。在未来，这一限制也许会成为强制限制。事实上，注释型宏定义也不应该在超过两个文件被使用，这不是强制限制，但应遵守，以保持行为描述层内容的整洁简洁。

非注释类型宏定义概念示例:

考虑一个常见的代码模式，如安全地获取字典中的值并提供默认值。这可能在行为描述层被描述为：

```text
// 在字典 safe_get_value(my_dict, key, default_value) 中安全获取 key 对应的值，若 key 不存在则返回 default_value。
```

或者，如果这是一个常用的模式，可以定义一个宏：

```text
#define SAFE_DICT_GET:
{
    // @ 模型请生成安全获取字典值的代码，使用 .get() 方法。
    get_value_safely(dict, key, default):
        return dict.get(key, default)
}
```

然后在行为描述层中使用：

```text
// 文件: utils.py
# SAFE_DICT_GET

// 在 ConfigReader 中使用这个模式来读取配置
class ConfigReader:
    # ... (constructor) ...
    def read_config():
        # ... (file reading logic) ...
        config_data = parse_json(file_content)
        // 获取日志级别配置
        log_level = safe_get_value(config_data, "log_level", "INFO")
        // ... (rest of the function) ...
```

在构建时，`# SAFE_DICT_GET` 会被替换为宏定义块中的内容，从而在符号-伪代码层生成一个 `get_value_safely` 函数的定义，并在 `read_config` 中生成对该函数的调用（尽管宏定义里只描述了行为，伪代码层需要将其转化为具体的函数定义和调用）。这是一种文本层面的复用。

### vi. 反向构建过程 (待完善，最高优先级)

反向构建是将现有历史代码适配到 MCCP 框架的过程。这一功能是 MCCP 期望成为通用中间件的关键组成部分，其目标在于将庞大的现有历史代码纳入 MCCP 的统一框架中。这能最大限度地利用已有的工程/源码，也有利于大量企业最大限度地发挥 MCCP 的功能，为自己的历史工程插上大模型的翅膀。

这一过程同样应该由大模型进行。

概念步骤描述:

1.  迭代读取源码: 一系列用于反向构建的脚本会迭代地、按照一定规则读取现有代码工程内的所有源码文件。
2.  转译至符号-伪代码层: 首先将源码文件反向转译至 MCCP 的符号-伪代码层。这是一个将具体编程语言语法转换为 MCCP 伪代码语法结构的过程，同时识别代码中的类、函数、变量等符号。
3.  构建符号表和兼容性文件: 在将源码转译至符号-伪代码层的过程中，符号表文件 (`symbol_table.json`) 和兼容性描述文件 (`mccp_config.json`) 会被优先构建并完成确定。符号表会记录所有识别出的符号及其作用域和文件依赖，兼容性文件会识别目标编程语言、可能的库依赖等。
4.  转译至行为描述层: 在进一步将符号-伪代码层反向转译至行为描述层的过程中，符号表文件和兼容性描述文件都不再会被更新（它们在步骤 3 已确定）。这一步需要大模型根据伪代码的结构和符号信息，生成更具描述性、更接近人类思维的半自然语言行为描述。这可能涉及推断代码段的业务意义和高级逻辑。

概念性反向构建流程描述 (Conceptual Pseudocode):

```text
// 函数: ReverseBuild(source_code_directory)
// 输入: source_code_directory - 现有代码工程的根目录

function ReverseBuild(source_code_directory):
    print("Starting reverse build process from: " + source_code_directory)

    source_files = find_all_source_files(source_code_directory) // Step 1: Iterate and read source files
    intermediate_pseudocode_files = {} // Dictionary to store {original_path: pseudocode_content}
    initial_symbol_table = empty_symbol_table()
    initial_config_file = empty_config_file()

    // Step 2 & 3: Translate to Symbol-Pseudocode layer and build Symbol Table/Config
    for each file_path in source_files:
        print("Processing file: " + file_path)
        source_content = read_file(file_path)

        // LLM translates source code to pseudocode
        pseudocode_content = LLM_translate_to_pseudocode(source_content, target_mccp_pseudo_format)
        intermediate_pseudocode_files[file_path] = pseudocode_content

        // LLM extracts symbols and dependencies, updates symbol table and config
        extracted_symbols = LLM_extract_symbols(source_content, pseudocode_content)
        update_symbol_table(initial_symbol_table, file_path, extracted_symbols)
        update_config_file(initial_config_file, source_content) // Extract language, dependencies etc.

    finalize_symbol_table(initial_symbol_table)
    save_symbol_table(initial_symbol_table, "symbol_table.json")
    save_config_file(initial_config_file, "mccp_config.json")

    behavior_description_files = {} // Dictionary to store {original_path: behavior_description_content}

    // Step 4: Translate from Symbol-Pseudocode layer to Behavior Description layer
    for each file_path, pseudocode_content in intermediate_pseudocode_files:
         print("Generating behavior description for: " + file_path)
         // LLM translates pseudocode to behavior description
         // Use finalized symbol table and config as context
         behavior_content = LLM_translate_to_behavior_description(
                                pseudocode_content,
                                initial_symbol_table,
                                initial_config_file,
                                original_source_content = read_file(file_path) // Provide original source for context if needed
                            )
         behavior_description_files[file_path] = behavior_content
         save_behavior_description(behavior_content, generate_mccp_bd_path(file_path))

    print("Reverse build process finished.")

// Helper conceptual functions:
function find_all_source_files(directory):
    // Scan directory for files with common source code extensions (.py, .cpp, .java etc.)
    return list_of_file_paths

function LLM_translate_to_pseudocode(source_code, target_format):
    // Use LLM call with prompt to convert source_code to MCCP pseudocode format
    return string_pseudocode

function LLM_extract_symbols(source_code, pseudocode):
    // Use LLM call to identify and extract symbols, scope, dependencies from source/pseudocode
    return structured_symbol_data

function update_symbol_table(table, file_path, symbols_data):
    // Integrate extracted symbols_data into the symbol table JSON structure
    // Update global, file-specific entries, file_depend
    pass // modifies table

function update_config_file(config, source_code):
     // Analyze source_code to identify language, common libraries, frameworks
     // Update config JSON structure
     pass // modifies config

function finalize_symbol_table(table):
     // Perform cross-file dependency checks, consistency checks etc.
     pass // refines table

function save_symbol_table(table, path):
     // Write table JSON to file
     pass

function save_config_file(config, path):
     // Write config JSON to file
     pass

function LLM_translate_to_behavior_description(pseudocode, symbol_table, config, optional_source):
    // Use LLM call with prompt and context (symbol_table, config) to convert pseudocode to behavior description
    // This requires understanding the logical steps and purpose conveyed by the pseudocode structure
    return string_behavior_description

function generate_mccp_bd_path(original_path):
    // Determine the appropriate file path for the generated behavior description file (e.g., change extension)
    return string_path

function save_behavior_description(content, path):
    // Write behavior description content to file
    pass
```

这项工作目前处于“待完善，最高优先级”的状态，其成功对于 MCCP 的广泛应用至关重要。

## 4. MCCP 的构建哲学、快速演进性质以及对开发人员角色转变的思考

构建哲学:

MCCP 几乎就是对传统软件开发的工程构建哲学的具象化拆解重构。它将传统开发过程中的“需求分析”、“概要设计”、“详细设计”等阶段，映射到了“自然语言提示词层”、“行为描述层”、“符号-伪代码层”这三个明确的抽象层级。通过引入大模型作为核心协调和转换工具，旨在实现这些阶段的自动化和协同化。

快速演进性质:

*   MCCP 自诞生之初就注定了它的快速演进性质。它不是一门需要固定语法进行编译的编程语言，而是一种协议和约定。
*   它永远都会跟随大模型本身的进化而快速地演进。任何被彻底定义的、僵化的语法结构都会导致其丧失快速迭代进化的能力。这种灵活性使其能够适应未来大模型能力的飞速提升。

开发人员角色转变:

*   我们需要进行思路的转变。开发人员不应该在符号-伪代码层投入过多的精力进行精细化微调，也不应该过分纠结于符号-伪代码层的具体语法。
*   本层级的构建结果在未来一定会随着大模型的进化而演进。开发人员应该成为过去类似“产品经理”的角色。
*   被精细化调整的应当是需求、行为描述（行为描述层），而不是太过于细节和具体的业务代码（符号-伪代码层和最终代码）。
*   这是因为人脑是有限的，我们有限的生命不应该被淹没在无限的代码中。MCCP 旨在将繁琐的、低层级的代码实现细节交给大模型，让开发人员更专注于高层级的需求分析、系统设计和行为规划。

MCCP 代表了一个美好的愿景，期望能够将历史性的代码纳入广袤的人工智能的版图当中来，并改变未来的软件开发范式，让开发者能够更高效、更具创造性地工作。