# MCCP 半自然语言行为描述层语法约定文档

## 前言

`.mcbc` 文件是 MCCP 协议中行为描述层的核心载体。它位于自然语言需求层 (`requirements.md`) 和符号-伪代码层 (`.mcpc`) 之间。本层的核心目的是将高层的自然语言需求进行结构化的拆解，具象化软件的框架、运行流程、模块定义以及核心业务逻辑的处理方式。它侧重于描述“如何通过一系列步骤和行为来实现”特定功能，并在此层级初步勾勒出关键符号（函数、流程块等）的框架，同时也描述软件中将要存在的变量和类等概念，为后续 `.mcpc` 层和目标代码层的生成奠定基础。

一个 `.mcbc` 文件通常代表一个模块或一个独立的功能单元。文件所在的目录结构对应于项目的模块结构，与 `.mcpc` 和 `src_target` 目录下的结构应当始终保持一致。

`.mcbc` 文件允许使用中文/英文作为描述性文本。理论上来说，对其它语言的支持程度仅取决于大模型的训练结果。

## 1. 行为/功能描述 (Behavior/Function Description)

在`.mcbc` 层，我们使用 `FUNC` 关键字声明一个新的功能或行为块。通常与FUNC相伴随出现的内容还有：`INPUT`, `OUTPUT`, `BEHAVIOR`。

语法:
`FUNC <功能名称>:`

`<功能名称>` 是一个标识符，应清晰地表达该功能的目的。命名推荐使用驼峰命名法 (*camelCase*) 或下划线命名法 (*snake_case*)。也可以使用描述性命名（如下例），mccp-toolchain会结合描述内容与符号表进行推断

语法:
`INPUT: <参数列表>` 

语法:
`OUTPUT: <参数列表>`

描述输入参数，输出参数（返回参数），参数列表用逗号`,` 分隔

语法:
`BEHAVIOR:`
    `  <描述步骤 1>`
    `  <描述步骤 2>`
    `  ...`

`BEHAVIOR:` 关键字开始一个功能或行为的具体描述块。该关键字之后的内容需要缩进。

示例：

```mcbc
FUNC 计算总价:
INPUT: 商品列表, 优惠码
OUTPUT: (总金额, 应用的折扣)
BEHAVIOR:
    初始化一个变量来存储当前的总金额，初始值为零。 (Initialize a variable to store the current total amount, starting at zero.)
    遍历商品列表中的每一个商品。
    对于每个商品，获取其价格，并累加到总金额变量中。
    检查是否提供了优惠码。
    如果提供了优惠码，计算应用的折扣并更新总金额。 (If discount code is provided, calculate applied discount and update the total amount variable.)
    返回最终的总金额和应用的折扣变量的值。 (Return the values of the final total amount and applied discount variables.)
```

## 2. 变量和类概念描述 (Variable and Class Concept Description)

在 `.mcbc` 层，我们通过语言文本配合结构化缩进语法对变量 (`VAR`) 和类 (`CLASS`) 的功能职责进行描述。

准确来说，在行为描述层允许使用隐含过程变量的描述来对过程中出现的变量进行说明，VAR 关键字的主要使用目的是强制让大模型识别：此处有一个开发者强制要求的变量

示例 (过程变量的描述):

```mcbc
FUNC 计算总价:
INPUT: 商品列表, 优惠码
OUTPUT: (总金额, 应用的折扣)
BEHAVIOR:
    VAR 当前总金额: 初始化为0。
    (Initialize a VAR currTotalAmount to store the current total amount, starting at zero.)
    遍历商品列表中的每一个商品。
    对于每个商品，获取其价格，并累加到总金额变量中。
    检查是否提供了优惠码。
    如果提供了优惠码，计算应用的折扣并更新 VAR 当前总金额。 
    (If discount code is provided, calculate applied discount and update the VAR currTotalAmount)
    返回最终的 VAR 当前总金额 和应用的折扣变量的值。 
    (Return the VAR currTotalAmount and Return the applied discount variables.)
```

示例 (类的描述):

```mcbc
CLASS ConfigurationManager:
    VAR configPath: 字符串  // 配置文件路径
    
    FUNC 加载配置(): 布尔值
        BEHAVIOR:
            尝试读取 this.configPath 指向的配置文件
            若成功则返回 true
            否则返回 false
    
    FUNC 获取参数(参数名: 字符串): 字符串
        BEHAVIOR:
            从已加载配置中查找指定参数名
            返回对应的参数值
```

## 3. 逻辑控制流 (High-level Logic & Control Flow)

`.mcbc` 层支持描述控制流，但不强制要求使用精确的`IF-ELSE` 语法。开发者可以使用隐含分支结构或隐含循环结构的自然语言说明，但是应当注意合理缩进，便于大模型的识别

### 3.1 条件判断 (Conditional Statements)

使用 `IF <条件>  ...` 和 `ELSE:` 描述条件分支。

语法:
`IF <条件描述> :`
    `<结果或步骤描述>`
`ELSE:`
    `<结果或步骤描述>`

示例:

```mcbc
BEHAVIOR:
    检查用户权限。 (Check user permissions.)
    IF 权限足够执行此操作  执行操作并记录日志。 (IF permissions are sufficient for this operation  perform the operation and log the event.)
    ELSE:
        返回权限不足错误。 (Return insufficient permissions error.)
```

### 3.2 循环与迭代 (Loops and Iteration)

`.mcbc` 层通过描述性语句结合缩进说明循环或迭代行为。可以提供特定的循环关键字（如 `FOR`, `WHILE`），也可以描述性地表达“对集合中的每一个元素执行...”。

语法:
`<描述性语句，暗示迭代，如：> 对列表中的每一个项:`
    `  <对当前项执行的操作>`

说明:
使用如“遍历”、“对每个”、“循环处理”、“FOR each”等词语结合缩进表达迭代逻辑。

示例:

```mcbc
BEHAVIOR:
    读取文件所有行到列表中。 (Read all lines from the file into a list.)
    对列表中的每一行: (FOR each line in the list:)
        移除行首尾空格。 (Remove leading and trailing whitespace from the line.)
        如果行不为空且不是注释行: (IF the line is not empty and not a comment line:)
            处理该行数据。 (Process the data in the line.)
```

### 3.3 错误处理与尝试 (Error Handling and Attempts)

使用 `TRY...` 结构描述可能失败的操作，并结合 `IF ... fails  ...` 描述失败时的处理。

对于不支持类似`try-catch` 语法的目标语言而言，此类操作应当被转化为基本的分支语句

语法:
`TRY <操作描述>.`
`IF <操作描述> fails  <失败处理描述>.`

说明:
这是一种常见模式，用于描述需要检查结果并进行错误处理的操作流程。

示例:

```mcbc
BEHAVIOR:
    TRY 连接到数据库。 (TRY connect to the database.)
    IF 连接到数据库 fails  记录错误日志并终止操作。 (IF connect to the database fails  log error and terminate operation.)
    ELSE:
        执行数据库查询。 (Execute database query.)
        处理查询结果。 (Process query results.)
```

## 4. 注释 (Commenting)

`.mcbc` 文件支持两种类型的注释，用于不同的目的：

- 人员注释 (`//`): 常规的注释内容，主要面向代码阅读人员。mccp-toolchain 会直接忽略此注释
- 意图注释 (`@`): 用于提供额外的、非行为流程本身的元信息，例如设计意图、对模型的额外约束、性能要求、安全考虑、或者关联到符号表/配置文件的额外提示。这些注释旨在引导模型的理解和生成过程。当用户有一些不便于或不希望被包含在行为描述流程中的内容时，可以使用此类注释。mccp-toolchain会对此类意图注释进行特定处理。

示例:

```mcbc
// 这是整个文件的目的描述 (This describes the overall purpose of the file)
@ 这个模块是高性能关键路径的一部分，模型生成代码时需要考虑效率。优先考虑运行时间短的算法，无需考虑空间占用。
FUNC 初始化系统:
INPUT: 配置文件路径 @ 确保路径是绝对路径且文件存在
OUTPUT: (成功状态, 错误信息)
BEHAVIOR:
    // 检查配置文件是否存在 (Check if the config file exists)
    TRY 读取配置文件。 // 使用标准库的读取函数 (Use standard library read function)
    IF 读取配置文件 fails  返回错误状态和信息。
    ELSE:
        @ 配置格式是 YAML，需要使用特定的解析库。
        解析配置内容。
        根据配置内容 初始化各个模块。
        返回成功状态。
```

## 5. 缩进约定 (Indentation Convention)

缩进在 `.mcbc` 文件中具有结构性意义，用于表示行为块的范围以及逻辑控制流的嵌套层级。建议使用一致的缩进单位（例如，4个空格）。

示例:

```mcbc
FUNC 处理订单:
INPUT: 订单数据
OUTPUT: (处理结果, 附加信息)
BEHAVIOR:
    验证订单数据的完整性。 (Validate the integrity of the order data.)
    IF 验证失败:
        记录验证失败日志。 (Log validation failure.)
        返回失败结果和原因。 (Return failure result and reason.)
    ELSE: // ELSE下的块体需缩进 (Block body under ELSE needs indentation)
        检查库存。 (Check inventory.)
        IF 库存充足:
            扣减库存。 (Decrease inventory.)
            生成支付请求。 (Generate payment request.)
            返回支付请求信息。 (Return payment request information.)
        ELSE: // ELSE下的块体需缩进 (Block body under ELSE needs indentation)
            标记订单为缺货。 (Mark order as out of stock.)
            通知用户。 (Notify the user.)
            返回缺货信息。 (Return out of stock information.)
```

## 6. 完整示例 (Full Example)

以下是一个完整的 `.mcbc` 文件示例，演示了上述语法的综合使用。

```mcbc
// mccp_mcbc_syntax_convention_revised.md
// MCCP Behavior Description for a simple file processor module - Revised

// 文件用途: 定义文件处理相关的行为，例如读取、写入、反转行等。
// File Purpose: Defines behaviors related to file processing, such as reading, writing, reversing lines, etc.

@ 这个模块主要负责IO操作，注意异常处理。

FUNC reverseFileLines:
INPUT: input_filepath, output_filepath // 输入：输入文件路径，输出文件路径 (Input: input file path, output file path)
OUTPUT: (success_status, error_message) // 输出：成功状态 (布尔), 错误信息 (字符串, 可选) (Output: success status (boolean), error message (string, optional))
BEHAVIOR:
    // 需要一个变量来存储读取到的所有行。
    // A variable is needed to store all read lines.
    @ 变量名应为 `linesList`，类型为字符串列表。
    TRY open the file at input_filepath for reading. // 尝试打开输入文件进行读取 (TRY open the input file for reading.)
    
    IF open the file at input_filepath fails : // 检查文件打开是否成功 (Check if file opening was successful.)
        // 如果失败，记录错误并返回。 (If fails, log error and return.)
        @ 使用日志系统记录错误，级别为 ERROR。
        Log an error indicating failure to open input file: input_filepath.
        Return (False, "Failed to open input file").
    ELSE:
        // 如果成功，读取文件所有行到列表linesList中。
        // If successful, read all lines from the file into the linesList variable.
        Read all lines from the input file into the linesList variable.
        
        Close the input file. // 关闭输入文件 (Close the input file.)
        
        // 对行列表linesList进行反转。
        // Reverse the order of lines in the linesList variable.
        Reverse the order of elements in the linesList.
        
        TRY open the file at output_filepath for writing. // 尝试打开输出文件进行写入 (TRY open the output file for writing.)
        
        IF open the file at output_filepath fails : // 检查输出文件打开是否成功 (Check if output file opening was successful.)
            // 如果失败，记录错误并返回。 (If fails, log error and return.)
            Log an error indicating failure to open output file: output_filepath.
            Return (False, "Failed to open output file").
        ELSE:
            // 如果成功，将反转后的行写入输出文件。 (If successful, write the reversed lines to the output file.)
            // 遍历反转后的列表linesList中的每一行。
            // Iterate through each line in the reversed linesList.
            FOR each line in the linesList:
                Write the current line to the output file, preserving original line endings. // 将当前行写入输出文件 (Write the current line to the output file)
            
            Close the output file. // 关闭输出文件 (Close the output file.)
            
            // 操作成功，返回成功状态。 (Operation successful, return success status.)
            Return (True, NULL). // NULL表示没有错误信息 (NULL indicates no error message)

// End of file_operations.mcbc
```
