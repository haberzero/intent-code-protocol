# ICP 符号-伪代码层语法约定文档

！！！未完善！！！

此文档暂时经由我的概念描述，借助flowith直接生成，极大概率不会是真正的最终方案

现阶段，出于开发周期和我个人时间精力成本的考虑，我将直接实现从icb代码到实际目标代码的转化，跳过mcpc的生成过程

然而，mcpc层仍然具备其必要性，这一抽象层不会被弃用。在未来将会实现的反向构建功能中，符号-伪代码层将会至关重要

## 目录

- [前言](#前言)
- [1.伪代码文件结构](#1-伪代码文件结构)
- [2.核心语法约定](#2-核心语法约定)
    - [2.1 语法语言约定](#21-语法语言约定)
    - [2.2 数据类型系统](#22-数据类型系统)
    - [2.3 变量声明与赋值](#23-变量声明与赋值)
    - [2.4 类结构定义](#24-类结构定义)
    - [2.5 函数/方法定义](#25-函数方法定义)
    - [2.6 控制流](#26-控制流)
        - [2.6.1 条件判断 (IF/ELSE IF/ELSE)](#261-条件判断-ifelse-ifelse)
        - [2.6.2 循环 (FOR, WHILE)](#262-循环-for-while)
    - [2.7 函数/方法调用](#27-函数方法调用)
    - [2.8 字面量](#28-字面量)
    - [2.9 操作符与优先级](#29-操作符与优先级)
    - [2.10 内置关键字与指令](#210-内置关键字与指令)
    - [2.11 注释](#211-注释)
- [3.缩进与块结束约定](#3-缩进与块结束约定)
    - [3.1 缩进约定](#31-缩进约定)
    - [3.2 块结束约定 (`END CLASS` vs.缩进)](#32-块结束约定-end-class-vs-缩进)
- [4.符号解析与作用域](#4-符号解析与作用域)
- [5.命名约定与最佳实践](#5-命名约定与最佳实践)
    - [5.1 命名约定](#51-命名约定)
    - [5.2 最佳实践](#52-最佳实践)
- [6.完整示例](#6-完整示例)

---

## 前言

`.mcpc` 文件是 模型上下文代码协议 (ICP) 中介表示层 (Intermediate Representation Layer) 的核心组成，位于符号-伪代码层 (Symbol-Pseudocode Layer)。它在行为描述层 (`.icb`) 和目标代码生成层 (`src_target`) 之间扮演关键桥梁角色。

其核心作用包括：

1. 精确符号关联: 使用外部符号表文件（如 `icp_symbols.json`）中定义的符号（`VAR`, `FUNC`, `CLASS`, 内置指令等），将高层行为具象化为可执行逻辑单元。
2. 结构化逻辑表达: 提供结构化、接近编程语言但保持平台和语言抽象的伪代码语法，用于清晰、无歧义地描述计算逻辑、数据流程、控制流及对象交互。
3. 目标代码生成依据: 作为 ICP 工具链将抽象行为转换为特定目标编程语言源代码的主要输入依据。工具链解析 `.mcpc` 文件，结合符号定义和目标语言规则，生成最终可编译代码。

ICP 协议栈的简化视图概念图：

```text

+-------------------+      +-----------------------+      +--------------------+
| Behavior Layer    | <--> | Symbol-Pseudocode     | <--> | Target Code Layer  |
| (`.icb` files)   |      | (`src_target` files)  |      |                    |
+-------------------+      | (`.mcpc` files)       |      +--------------------+
                           +-----------------------+
                                     ^
                                     |
                             +-------------------+
                             | Symbol Table      |
                             | (`icp_symbols.json`)|
                             +-------------------+

```

*此图示为概念说明，不属于`.mcpc`语法。*

`.mcpc` 文件采用结构化伪代码风格，强调可读性和解析性。允许包含中文和英文的描述性注释 (`//`) 和模型指令 (`@`)，但核心语法元素（关键字、操作符、内置指令名称）必须使用标准英文标识符，确保工具链解析一致性。

通常，一个 `.mcpc` 文件对应于 `src_icb` 和 `src_target` 目录下具有相同基础名称的文件。文件和目录结构应与 `src_icb` 和 `src_target` 目录同步，反映项目模块划分和文件对应关系。

## 1.伪代码文件结构

`.mcpc` 文件包含结构化伪代码实现，核心是顶级结构定义，如函数 (`FUNC`) 和类 (`CLASS`)。这些顶级结构直接位于文件的根层，不进行缩进。

语法:

```mcpc

// 文件顶层伪代码实现
<顶级结构定义1> // e.g., FUNC definition, CLASS definition
<顶级结构定义2>
...
```

说明:

- `<顶级结构定义>`: 可以是独立函数 (`FUNC`) 或类 (`CLASS`) 定义。它们应从文件第一列 (0缩进) 开始。
- 任何非顶级结构（如函数体内语句、类体内成员、控制流块内语句）必须相对于其父结构缩进，表达层级和块范围。

示例:

```mcpc
// 示例文件结构
FUNC processData(data): // 顶级函数，0缩进
    // 函数体，缩进一次
    VAR:[] processed = processInternal(data)
    IF processed: // 控制流语句，缩进一次
        // IF块体，缩进两次
        PRINT("Data processing successful.")
    // IF块结束，回到缩进一次
    // 函数体结束，回到0缩进

CLASS DataStore: // 顶级类，0缩进
    // 类体内成员，缩进一次
    VAR:[List<Byte>] storageList // 成员变量

    FUNC addData(newData): // 方法定义，缩进一次
        // 方法体，缩进两次
        storageList.APPEND(newData) // 调用列表方法 (假设 APPEND 内置或通过符号表定义)
    // addData 方法结束

END CLASS // DataStore类结束，0缩进
```

---

## 2.核心语法约定

### 2.1 语法语言约定

为确保 ICP 工具链解析一致性，`.mcpc` 文件核心语法元素必须使用标准英文标识符。

包括：

- 所有 关键字 (Keywords): `VAR`, `FUNC`, `CLASS`, `IF`, `ELSE IF`, `ELSE`, `WHILE`, `FOR`, `IN`, `RETURN`, `BREAK`, `CONTINUE`, `NEW`, `THIS`, `NULL`, `TRUE`, `FALSE`, `PASS`, `END CLASS`, `TYPE`.
- 所有 内置函数或指令名称 (Built-in Function/Instruction Names): 例如 `PRINT`, `EXIT`, `LOG_ERROR`, `WAIT`, `TYPE`, `OPEN_FILE`, `READ_ALL_LINES_FROM_HANDLE`, `CLOSE_FILE_HANDLE`, `REVERSE_LIST_IN_PLACE`, `WRITE_LINE_TO_HANDLE`, `APPEND`, `LENGTH` 等。这些名称是语言内置或通过标准库符号定义。
- 所有 操作符 (Operators): 例如 `==`, `!=`, `<`, `>`, `<=`, `>=`, `AND`, `OR`, `NOT`, `IS NULL`, `IS NOT NULL`, `IS TRUE`, `IS FALSE`, `+`, `-`, `*`, `/`, `%`, `.` (成员访问), `[]` (索引/切片访问), `()` (函数调用/分组).

用户自定义符号名称（如变量名、函数名、类名、方法名）可在外部符号表 (`icp_symbols.json`) 中定义为包含中文或其他语言的混合名称，并在 `.mcpc` 文件中使用。字符串字面量及注释 (`//` 和 `@`) 也允许包含中文或其他语言字符。

### 2.2 数据类型系统

`.mcpc` 支持基本数据类型和结构化类型。变量类型可通过 `[TYPE: <类型>]` 方式可选（但推荐）指定，增强清晰度，辅助代码生成阶段的类型检查和目标语言映射。

语法:
`[TYPE: <类型>]`

主要类型类别:

- 基本类型 (Primitive Types): `Int`, `String`, `Boolean`, `Byte`, `Float`.
- 集合类型 (Collection Types): `List<elementType>`, `Map<keyType, valueType>`.
- 自定义类型 (Custom Types): `<自定义类名>` (通过 `CLASS` 定义).
- 特殊类型: `NULL`, `Any`, 特定内置资源类型（如文件句柄）。

示例:

```mcpc
VAR:[Int] itemCount = 0
VAR:[String] userName = "Alice"
VAR:[Boolean] isProcessed = FALSE
VAR:[List<Byte>] rawBytes
VAR:[Map<String, String>] configMap
VAR:[MyClass] myObject // 假设 MyClass 自定义
VAR:[FileHandle] fileHandle // 假设 FileHandle 内置资源类型
```

### 2.3 变量声明与赋值

使用 `VAR` 关键字声明变量。类型可选指定。使用 `=` 赋值。

语法:
`VAR:[<类型>] <变量名> [= <初始值>]` // 声明并可选指定类型和初始化
`<变量名> = <表达式>` // 赋值
`VAR:[] (<变量1>, <变量2>, ...) = <多值表达式>` // 多变量同时赋值 (用于接收多返回值函数)

说明:

- `VAR`: 关键字，显式声明变量。
- `:[<类型>]`: 可选，使用 `:[<类型>]` 语法指定变量类型。遵循 2.2 数据类型系统约定。若不指定类型，写为 `VAR:[]` 或直接省略 `:[<类型>]` 部分（取决于具体工具链实现，推荐 `VAR:[]` 保持结构一致性，但示例兼容两种）。本规范示例中，对于无类型且无初始值的声明，简化为 `VAR <变量名>`；对于无类型但有初始值的，使用 `VAR:[] <变量名> = <初始值>`。为严格统一，本修订采用 `VAR:[<类型>] <变量名> [= <初始值>]` 作为标准格式，无类型时 `<类型>` 留空，无初始值时 `= <初始值>` 省略。
- `<变量名>`: 变量名称。遵循命名约定（章节 5.1），可在符号表中定义为混合语言。
- `<初始值>`: 可选，声明变量时的初始值。
- `<表达式>`: 字面值、变量、函数调用、类实例创建、操作符组合等。
- 多变量赋值用于同时接收函数返回的多个值。

示例:

```mcpc
FUNC setupData(): // 0缩进
    // 函数体，缩进一层
    VAR:[Int] defaultLimit = 100 // 声明Int变量，指定类型并初始化
    VAR:[String] currentStatus // 声明String变量，指定类型，未初始化
    currentStatus = "Active" // 赋值

    VAR:[List<String>] dataList = ["item1", "item2"] // 声明并初始化列表

    VAR:[] isConfigured = checkConfiguration() // 声明并根据函数返回值初始化，类型推断

    VAR:[] (resultCode, resultMessage) = performAction() // 同时接收函数返回的两个值

    resultCode = 0 // 重新赋值单个变量
```

### 2.4 类结构定义

使用 `CLASS` 关键字定义类。类体内包含成员变量 (`VAR`) 和方法 (`FUNC`) 定义。类定义是顶级结构，0缩进。

语法:

```mcpc
CLASS <类名>: // 0缩进
    // 类成员定义，相对于 CLASS 行缩进一个层级
    VAR:[<类型>] <成员变量名> [= <初始值>]
    FUNC <方法名>([<参数列表>]):
    ...
END CLASS // 结束类定义，与对应的 CLASS 行同缩进 (0缩进)
```

说明:

- `CLASS`: 关键字，定义类。
- `<类名>`: 类名称。遵循命名约定（章节 5.1），可在符号表中定义为混合语言。
- `END CLASS`: 关键字，标记类定义结束。必须与对应的 `CLASS` 关键字同缩进。
- `<成员定义>`: 成员变量 (`VAR`) 和成员函数/方法 (`FUNC`) 定义。在 `CLASS` 块内需相对于 `CLASS` 行增加一个缩进层级。
- `__init__` 通常用作构造函数。

示例:

```mcpc
CLASS UserProfile: // 定义用户 प्रोफाइल 类, 0缩进
    VAR:[Int] userId // 成员变量，缩进一层
    VAR:[String] userName // 成员变量，缩进一层
    VAR:[Boolean] isActive = TRUE // 成员变量并初始化，缩进一层

    FUNC __init__(id [TYPE: Int], name [TYPE: String]): // 构造函数，缩进一层
        // 构造函数体，缩进两层
        THIS.userId = id // 使用 THIS 引用当前实例成员
        THIS.userName = name

    FUNC deactivate(): // 方法，缩进一层
        // 方法体，缩进两层
        THIS.isActive = FALSE
        LOG_INFO("User " + THIS.userName + " deactivated.")

END CLASS // UserProfile 类结束，0缩进
```

### 2.5 函数/方法定义

使用 `FUNC` 关键字在文件顶层定义函数，或在 `CLASS` 块内定义方法。函数是顶级结构，0缩进。方法在类体内，相对于 `CLASS` 行缩进一层。

语法:
`FUNC <函数名>([<参数列表>]):` // 定义函数 (0缩进) 或方法 (类体内，缩进一层)
    `<函数/方法体伪代码>` // 相对于 FUNC 行增加一个缩进层级

说明:

- `FUNC`: 关键字，定义函数或方法。
- `<函数名>`: 函数/方法名称。应在外部符号定义文件中定义。遵循命名约定（章节 5.1），可在符号表中定义为混合语言。
- `[<参数列表>]`: 可选，逗号分隔的参数列表。每个参数可选使用 `[TYPE: <类型>]` 指定类型，例如 `paramName [TYPE: ParamType]`.
- 函数/方法体相对于 `FUNC ...:` 行需增加一个缩进层级。结束由缩进层级减少标识（章节 3.2）。
- `RETURN [<表达式> or (<表达式1>, <表达式2>, ...)]`: 返回一个或多个值。

示例:

```mcpc
FUNC calculateSum(num1 [TYPE: Int], num2 [TYPE: Int]): // 顶级函数，带参数和返回值
    // 函数体，缩进一层
    VAR:[] sumResult = num1 + num2
    RETURN sumResult
    // 函数 calculateSum 结束

CLASS Calculator: // 顶级类
    // 类体，缩进一层
    FUNC add(a [TYPE: Int], b [TYPE: Int]): // 方法定义，带参数和返回值
        // 方法体，缩进两层
        RETURN a + b
    // add 方法结束
// Calculator 类结束
```

### 2.6 控制流

`.mcpc` 支持结构化的条件判断和循环。关键字必须为英文。块体必须相对于控制流语句缩进。

#### 2.6.1 条件判断 (IF/ELSE IF/ELSE)

使用 `IF`, `ELSE IF`, `ELSE` 关键字构建条件分支。

语法:

```mcpc
IF <条件表达式>: // IF语句本身位于某个缩进层级
    <条件为真时执行的伪代码> // 相对于 IF 行增加一个缩进层级
ELSE IF <另一个条件表达式>: // 可选，与 IF 同一缩进层级
    <另一个条件为真时执行的伪代码> // 相对于 ELSE IF 行增加一个缩进层级
ELSE: // 可选，与 IF/ELSE IF 同一缩进层级
    <所有条件都为假时执行的伪代码> // 相对于 ELSE 行增加一个缩进层级
// 条件判断块结束，回到 IF/ELSE IF/ELSE 所在的缩进层级
```

说明:

- `<条件表达式>`: 求值为布尔值的表达式。使用比较 (`==`, `!=`, `<`, `>`, `<=`, `>=`) 和逻辑 (`AND`, `OR`, `NOT`) 操作符，及特殊检查 (`IS NULL`, `IS NOT NULL`, `IS TRUE`, `IS FALSE`)。操作符必须是英文。
- `IF`, `ELSE IF`, `ELSE`: 关键字。
- `:` 标记条件表达式结束和条件块开始。块体必须相对于控制流语句行增加一个缩进层级。
- `ELSE IF` 和 `ELSE` 必须与其对应的 `IF` (或 `ELSE IF`) 同一缩进层级。
- 块结束由缩进层级减少标识。

示例:

```mcpc
FUNC processStatus(status): // 0缩进
    // 函数体，缩进一层
    IF status == "Error": // 缩进一层
        // IF块体，缩进两层
        LOG_ERROR("Processing failed.")
        handleError()
    ELSE IF status == "Warning": // 缩进一层
        // ELSE IF块体，缩进两层
        LOG_WARN("Processing encountered a warning.")
    ELSE: // 缩进一层
        // ELSE块体，缩进两层
        LOG_INFO("Processing successful.")
    // IF/ELSE IF/ELSE 块结束，回到缩进一层
    // 函数体结束，回到0缩进
```

#### 2.6.2 循环 (FOR, WHILE)

`.mcpc` 支持基于集合的迭代 (`FOR`) 和条件循环 (`WHILE`)。

语法:
`FOR <元素变量> IN <集合表达式>:` // FOR语句本身位于某个缩进层级
    `<循环体伪代码>` // 相对于 FOR 行增加一个缩进层级
// FOR 循环结束，回到 FOR 所在的缩进层级

`WHILE <条件表达式>:` // WHILE语句本身位于某个缩进层级
    `<循环体伪代码>` // 相对于 WHILE 行增加一个缩进层级
// WHILE 循环结束，回到 WHILE 所在的缩进层级

说明:

- `FOR`: 遍历 `<集合表达式>` 求值得到的集合。每次迭代将当前元素赋给 `<元素变量>`。`IN` 是必需关键字。
- `WHILE`: 只要 `<条件表达式>` 求值为 `TRUE`，重复执行循环体。
- `FOR`, `IN`, `WHILE`: 关键字。
- 循环体伪代码必须相对于循环语句增加一个缩进层级。
- 块结束由缩进层级减少标识。
- `BREAK`: 关键字，立即退出最内层循环。
- `CONTINUE`: 关键字，跳过当前循环迭代剩余代码，开始下一次迭代。

示例:

```mcpc
FUNC processItems(itemsList): // 0缩进
    // 函数体，缩进一层
    VAR:[] isCompleted = FALSE // 缩进一层
    WHILE NOT isCompleted: // 缩进一层
        // WHILE 循环体，缩进两层
        isCompleted = checkProcessStatus(processHandle) // 检查状态
        IF NOT isCompleted: // 缩进两层
            // IF块体，缩进三层
            WAIT(1000) // 等待1秒 (假设 WAIT 内置)
        // IF块结束，回到缩进两层
    // WHILE 循环结束，回到缩进一层
    PRINT("Process completed.") // 缩进一层

    FOR item IN itemsList: // 遍历列表
        // FOR 循环体，缩进两层
        IF item.isValid(): // 缩进两层
            // IF块体，缩进三层
            processSingleItem(item)
        ELSE: // 缩进两层
            // ELSE块体，缩进三层
            LOG_WARN("Skipping invalid item.")
            CONTINUE // 跳到下一个 item
        // IF/ELSE块结束，回到缩进两层
        IF item.isCritical(): // 缩进两层
             BREAK // 如果遇到关键项目则退出整个循环
        // IF块结束，回到缩进两层
    // FOR 循环结束，回到缩进一层
    // 函数体结束，回到0缩进
```

### 2.7 函数/方法调用

直接使用函数或方法符号名称及参数列表进行调用。

语法:
`<函数或方法名>([<参数列表>])` // 作为语句执行，忽略返回值
`VAR:[] <结果变量> = <函数或方法名>([<参数列表>])` // 调用并获取单个返回值 (示例使用 VAR:[] 假定类型未指定)
`VAR:[] (<变量1>, <变量2>, ...) = <函数或方法名>([<参数列表>])` // 调用并获取多个返回值
`<对象变量>.<方法名>([<参数列表>])` // 调用对象方法
`VAR:[] <结果变量> = <对象变量>.<方法名>([<参数列表>])` // 调用对象方法并获取返回值

说明:

- `<函数或方法名>`: 要调用的符号名称。应在外部符号定义文件中定义。可以是混合语言。
- `<参数列表>`: 逗号分隔的传递给函数/方法的参数列表。可以是字面量、变量、表达式等。
- 类实例方法调用使用 `.` 操作符。
- 函数/方法调用表达式可在赋值语句右侧使用。
- 使用 `VAR:[] (<var1>, <var2>, ...)` 语法接收多个返回值。

示例:

```mcpc
FUNC performTask(): // 0缩进
    // 函数体，缩进一层
    initializeService() // 调用独立函数，无参数无返回值

    VAR:[] userId = 123 // 缩进一层
    VAR:[] userRecord = getUserRecord(userId) // 调用独立函数，有参数，获取返回值

    VAR:[] (status, message) = processRecord(userRecord) // 调用独立函数，有参数，获取多个返回值

    IF status == "Success": // 缩进一层
        VAR:[MyClass] myObject = NEW MyClass() // 创建类实例，NEW 关键字
        myObject.updateStatus("Processed") // 调用对象方法，有参数，无返回值
        VAR:[] currentStatus = myObject.getStatus() // 调用对象方法，无参数，获取返回值
        PRINT("Object status: " + currentStatus)
    // IF块结束
    // 函数体结束
```

### 2.8 字面量

`.mcpc` 支持以下字面量：

- 字符串: 用双引号 (`"`) 包围。示例: `"你好，世界"`, `"Error message: \"Invalid input\""`.
- 整数: 数字序列。示例: `123`, `0`, `-45`.
- 浮点数: 包含小数点或科学计数法。示例: `3.14`, `-0.001`, `1e6`, `1.5e-2`.
- 布尔: 关键字 `TRUE` 和 `FALSE`。示例: `TRUE`, `FALSE`.
- 空值: 关键字 `NULL`。示例: `NULL`.
- 列表: 用方括号 (`[]`) 包围，逗号分隔元素。示例: `[]`, `[1, 2, 3]`, `["apple", "banana"]`, `[1, "mix", TRUE]`.
- 映射: 用花括号 (`{}`) 包围，逗号分隔键值对 (`key: value`)。键通常是字符串或整数。示例: `{}`, `{"name": "Alice", "age": 30}`, `{1: "first", 2: "second"}`.

示例:

```mcpc
VAR:[String] greeting = "Hello"
VAR:[Int] count = 10
VAR:[Float] piValue = 3.14159
VAR:[Boolean] isDone = FALSE
VAR:[List<Any>] emptyList = []
VAR:[Map<String, String>] settings = {"theme": "dark", "language": "zh-CN"}
```

### 2.9 操作符与优先级

`.mcpc` 支持常见操作符，必须为英文。理解优先级和结合性对正确解析表达式至关重要。

操作符列表 (按大致优先级从高到低):

| 类型               | 操作符                       | 描述                         | 结合性   | 示例                                     |
| :----------------- | :--------------------------- | :--------------------------- | :------- | :--------------------------------------- |
| 成员/索引访问      | `.`                          | 成员访问                     | 左       | `obj.member`, `obj.method()`             |
|                    | `[]`                         | 索引或切片访问               | 左       | `list[0]`, `map["key"]`                  |
| 函数调用           | `()`                         | 函数/方法调用                | 左       | `func()`, `method(arg)`                  |
| 一元操作符         | `-`, `NOT`                   | 负号, 逻辑非                 | 右       | `-5`, `NOT TRUE`                         |
| 乘法/除法/取模     | `*`, `/`, `%`                | 乘法, 除法, 取模             | 左       | `a * b`, `x / y`, `p % q`                |
| 加法/减法/连接     | `+`, `-`                     | 加法, 减法, 字符串连接       | 左       | `a + b`, `x - y`, `"Hello" + " World"` |
| 比较操作符         | `==`, `!=`, `<`, `>`, `<=`, `>=`| 等于, 不等于, 小于, 大于等   | 左       | `a == b`, `x >= y`                       |
| 特殊比较           | `IS NULL`, `IS NOT NULL`, `IS TRUE`, `IS FALSE`| 是否为 NULL/非NULL, 是否为 TRUE/FALSE | 无       | `var IS NULL`, `boolVar IS TRUE`         |
| 逻辑与             | `AND`                        | 逻辑与                       | 左       | `cond1 AND cond2`                        |
| 逻辑或             | `OR`                         | 逻辑或                       | 左       | `cond1 OR cond2`                         |
| 赋值               | `=`                          | 赋值                         | 右       | `var = value`                            |
| 分组               | `()`                         | 强制优先级/多值分组          | N/A      | `(a + b) * c`, `VAR:[] (x, y) = func()`  |

说明:

- 优先级决定计算顺序 (`a + b * c` 先算 `b * c`).
- 结合性决定同一优先级操作符连续出现时的计算顺序。左结合 (e.g., `+`, `.`) 从左向右；右结合 (e.g., `=`, `NOT`) 从右向左。
- 括号 `()` 改变默认优先级。
- `+` 用于数字加法，字符串连接。
- `IS NULL`, `IS NOT NULL`, `IS TRUE`, `IS FALSE` 是特殊布尔检查。

示例:

```mcpc
VAR:[] result = 5 + 3 * 2 // result is 11 (multiplication before addition)
VAR:[] anotherResult = (5 + 3) * 2 // anotherResult is 16 (parentheses force addition first)
VAR:[] isEligible = age >= 18 AND hasPermission IS TRUE // 组合逻辑和比较操作
VAR:[] itemStatus = dataMap["status"] // 映射访问
```

### 2.10 内置关键字与指令

除语法结构关键字外，`.mcpc` 通过关键字或内置符号提供基本内置功能。它们是语言规范一部分，无需在外部符号表中重复定义（实现可能通过符号表映射）。

常用内置关键字/指令:

- `NEW`: 关键字，创建类实例。语法: `NEW <类名>([<构造函数参数>])`.示例: `VAR:[] myObject = NEW MyClass(arg1, arg2)`
- `THIS`: 关键字，在类方法内引用当前实例。示例: `THIS.memberVariable = value`, `THIS.methodName()`.
- `NULL`: 关键字，表示空值。示例: `VAR:[] myVar = NULL`, `IF result IS NULL: ...`.
- `TRUE`, `FALSE`: 关键字，布尔字面量。示例: `VAR:[] isDone = TRUE`, `WHILE condition IS FALSE: ...`.
- `PASS`: 关键字，空块占位符。示例: `IF someCondition: PASS ELSE: ...`.
- `BREAK`: 关键字，立即退出最内层 `FOR` 或 `WHILE` 循环。
- `CONTINUE`: 关键字，跳过当前最内层 `FOR` 或 `WHILE` 循环剩余部分，进入下一次迭代。
- `RETURN [<表达式>]`: 关键字，退出当前函数/方法，返回指定值（可选）。
- `TYPE`: 关键字，用于 `[TYPE: <类型>]` 语法中。

常用内置函数/操作 (通过内置符号提供): `PRINT()`, `LOG_INFO()`, `LOG_WARN()`, `LOG_ERROR()`, `EXIT()`, `WAIT()`, 文件操作 (e.g., `OPEN_FILE()`), 列表/集合操作 (e.g., `APPEND()`, `LENGTH()`).

注意: 内置功能集可能由工具链实现或标准符号表定义。

示例:

```mcpc
FUNC processItemsSafely(items): // 0缩进
    // 函数体，缩进一层
    IF items IS NULL: // 检查是否为 NULL
        LOG_ERROR("Input items list is NULL.")
        RETURN FALSE // 使用 RETURN 退出函数并返回值

    IF LENGTH(items) == 0: // 使用 LENGTH 内置函数
        LOG_INFO("Items list is empty.")
        RETURN TRUE

    FOR item IN items: // 循环
        IF NOT item.isValid(): // 调用对象方法，使用 NOT 操作符
            LOG_WARN("Invalid item found, skipping.")
            CONTINUE // 跳过当前迭代
        processItem(item)
        // 检查是否需要中断循环
        IF item.isTerminator:
            BREAK // 中断循环
    // 循环结束

    RETURN TRUE
    // 函数结束
```

### 2.11 注释

`.mcpc` 支持两种单行注释：

语法:
`// <注释内容>` // 代码级注释
`@ <元数据内容>` // 元数据/意图注释

说明:

- `//`: 用于解释伪代码行、详细逻辑、代码意图。面向阅读者、模型理解，帮助理解实现细节。不直接转化为可执行代码，生成目标代码时可能保留为注释。
- `@`: 用于提供更高层上下文、约束、指令或非执行信息给工具链或模型。不属可执行伪代码逻辑，指导代码生成。例如，标记算法选择、优化提示、资源约束、需求关联 (`@see`, `@ref`)，或特定工具链指令。通常不简单复制到目标代码注释，可能影响生成代码结构。工具链可能解析特定 `@` 指令。

示例:

```mcpc
FUNC processData(inputData): // 0缩进
    // 函数体，缩进一层
    // 初始化处理计数器
    VAR:[Int] processedCount = 0 // 缩进一层

    @ Consider optimizing this loop for large datasets.(考虑对大型数据集优化此循环)
    FOR dataItem IN inputData: // 遍历输入数据，缩进一层
        // 对每个数据项执行处理逻辑
        VAR:[] status = processItem(dataItem) // 调用处理函数，缩进两层

        IF status == "SUCCESS": // 检查处理结果，缩进两层
            processedCount = processedCount + 1 // 增加计数
            // TODO: Add logging for successful processing (待办：添加成功处理的日志)
        ELSE: // 处理失败，缩进两层
            @ Error handling strategy: log and continue.(错误处理策略：记录并继续)
            LOG_ERROR("Failed to process item: " + dataItem.id) // 记录错误
            // No BREAK or EXIT here, continue to next item
        // IF/ELSE 块结束
    // FOR 循环结束

    @ Ensure cleanup resources are released.(确保释放清理资源)
    cleanupResources() // 调用资源清理函数，缩进一层

    RETURN processedCount // 返回处理成功的计数，缩进一层
    // 函数结束
```

---

## 3.缩进与块结束约定

### 3.1 缩进约定

缩进在 `.mcpc` 文件中强制且具结构意义，表示代码块范围及逻辑控制流嵌套层级。取代多数编程语言的花括号或其他显式块定界符。

约定:

1.顶级结构: 函数 (`FUNC`) 和类 (`CLASS`) 定义必须在文件最外层，不缩进 (0缩进)。
2.块内容:
    - 函数体（紧跟 `FUNC ...:` 后）所有语句、变量定义 (`VAR`)、控制流语句等必须相对于包含结构起始行向内缩进一层。
    - 类体（紧跟 `CLASS ...:` 后）所有成员变量 (`VAR`) 和方法 (`FUNC`) 定义必须相对于 `CLASS` 行向内缩进一层。
3.控制流块: `IF`, `ELSE IF`, `ELSE`, `FOR`, `WHILE` 语句本身在某个缩进层级。其下块体伪代码（即 `:` 后代码）必须相对于该控制流语句行向内再缩进一层。
4.嵌套: 结构或控制流嵌套叠加缩进层级。新块应在前一级基础上再增加一个缩进单位。
5.缩进单位: 必须使用一致单位，建议 4个空格 或 2个空格。整个文件必须使用相同单位和风格（禁止混合空格和制表符）。本规范示例使用4个空格。

### 3.2 块结束约定 (`END CLASS` vs.缩进)

`.mcpc` 语法主要依赖缩进标识块的开始和结束。缩进减少表示当前块结束，回到了上一级范围。类定义是唯一例外。

约定:

1.基于缩进的块结束: 大多数块（函数/方法体、`IF/ELSE IF/ELSE` 块、`FOR` 块、`WHILE` 块）无显式结束关键字。范围由缩进层级定义。后续行缩进小于当前块起始行时，当前块结束。
2.显式 `END CLASS`: 类定义 (`CLASS`) 是唯一使用显式结束关键字的块。`END CLASS` 关键字必须与对应 `CLASS` 关键字同缩进层级（顶级类 `CLASS` 和 `END CLASS` 皆为 0缩进）。

设计理由:

- 缩进标识块: 依赖缩进是 `.mcpc` 伪代码风格核心，借鉴Python易读性。对函数体和控制流，此方式简洁清晰，避免重复 `END FUNC`, `END IF` 等关键字。
- 显式 `END CLASS`: 类结构复杂，含多种成员，嵌套深。显式 `END CLASS` 为类定义提供明确文件级结束标记，提高大型类定义清晰度和可维护性。作为重要锚点，尤其在快速浏览文档时。

示例 (使用4个空格作为缩进单位):

```mcpc
// 文件根层，0缩进

FUNC processList(items): // 函数开始，0缩进
    // 函数体开始，缩进一层 (4 spaces)
    VAR:[] count = LENGTH(items) // 缩进一层
    IF count > 0: // IF块开始，缩进一层
        // IF块体开始，缩进两层 (8 spaces)
        FOR item IN items: // FOR块开始，缩进两层
            // FOR块体开始，缩进三层 (12 spaces)
            processItem(item) // 缩进三层
            // processItem 调用结束，仍是缩进三层
        // FOR块体结束，回到缩进两层
        PRINT("Processed all items.") // 缩进两层
    // IF块体结束，回到缩进一层
    // PRINT 调用结束，仍是缩进一层
// 函数体结束，回到0缩进
// processList 函数结束

CLASS DataManager: // 类开始，0缩进
    VAR:[List<Byte>] data // 成员变量，缩进一层

    FUNC initialize(): // 方法开始，缩进一层
        // 方法体开始，缩进两层
        THIS.data = [] // 缩进两层
        // THIS.data 赋值结束，仍是缩进两层
    // 方法体结束，回到缩进一层
    // initialize 方法结束

    FUNC load(source): // 方法开始，缩进一层
        // 方法体开始，缩进两层
        VAR:[] handle = OPEN_FILE(source, "read") // 缩进两层
        IF handle IS NOT NULL: // IF块开始，缩进两层
            // IF块体开始，缩进三层
            THIS.data = READ_ALL_LINES_FROM_HANDLE(handle) // 缩进三层
            CLOSE_FILE_HANDLE(handle) // 缩进三层
            // CLOSE_FILE_HANDLE 调用结束，仍是缩进三层
        // IF块体结束，回到缩进两层
        // handle 变量使用结束，仍是缩进两层
    // 方法体结束，回到缩进一层
    // load 方法结束

END CLASS // 类体结束，显式 END CLASS，0缩进
// DataManager 类定义结束
```

---

## 4.符号解析与作用域

`.mcpc` 语言中符号（变量、函数、类、方法）可见性和生命周期由定义位置决定。解析遵循作用域规则。外部符号表 (`icp_symbols.json`) 定义全局可见符号。

规则:

1.外部/全局作用域: 外部符号表中定义的符号全局可见。`.mcpc` 文件任何位置可引用。
2.文件局部作用域: `.mcpc` 文件顶层定义的函数 (`FUNC`) 和类 (`CLASS`) 具文件局部作用域。该文件内可见可引用。默认不对其他 `.mcpc` 文件可见，除非符号表声明为导出或全局。
3.类作用域: `CLASS` 定义体内成员变量 (`VAR`) 和方法 (`FUNC`) 具类作用域。只能通过类实例 (`THIS.memberName`, `instance.methodName()`) 或方法内部 `THIS` 引用。
4.函数/方法局部作用域: 函数或方法体内部 `VAR` 声明变量具函数/方法局部作用域。仅在该函数/方法体及其嵌套块内可见。生命周期与执行周期一致。
5.控制流块作用域: `IF`, `ELSE IF`, `ELSE`, `FOR`, `WHILE` 等块内部声明变量具该块局部作用域。仅在该块及其嵌套块内可见。作用域从声明处开始，到缩进减少表示块结束时结束。
6.参数作用域: 函数或方法参数在其整个函数/方法体内具局部作用域。
7.变量遮蔽 (Shadowing): 嵌套作用域变量与外部同名变量同名时会遮蔽外部变量。不推荐使用遮蔽。

示例:

```mcpc
// 假设 icp_symbols.json 中定义了全局函数 globalFunc() 和全局类 GlobalClass

FUNC fileLocalFunc(): // 文件局部函数 (文件作用域)
    VAR:[] localFileVar = 10 // 函数局部变量
    globalFunc() // 引用全局函数

    IF localFileVar > 5:
        VAR:[] localBlockVar = 20 // 控制流块局部变量
        PRINT(localFileVar + localBlockVar) // 可以访问外层变量
        // globalFunc() // 可以访问全局函数
    // localBlockVar 的作用域在此结束

// localFileVar 的作用域在此结束
// localBlockVar 在此不可见

CLASS FileLocalClass: // 文件局部类 (文件作用域)
    VAR:[Int] classMemberVar // 类成员变量 (类作用域)

    FUNC classMethod(): // 类方法 (类作用域)
        VAR:[] methodLocalVar = 30 // 方法局部变量
        THIS.classMemberVar = methodLocalVar // 访问类成员变量
        fileLocalFunc() // 访问同一文件内的其他函数
        // globalFunc() // 访问全局函数
    // methodLocalVar 的作用域在此结束
// FileLocalClass 类作用域在此结束
```

## 5.命名约定与最佳实践

清晰一致的命名约定和良好实践对 `.mcpc` 文件可读性、可维护性和工具链准确解析至关重要。

### 5.1 命名约定

建议遵循以下命名约定（应在外部符号表中强制）：

- 变量名: 驼峰命名法 (camelCase)，首字母小写。描述性强。示例: `userCount`, `inputFilePath`.
- 函数/方法名: 驼峰命名法 (camelCase)，首字母小写。动词/动宾短语，表明行为。构造函数 `__init__`。示例: `calculateAverage`, `getData`, `deactivateUser`.
- 类名: 帕斯卡命名法 (PascalCase)，首字母大写。名词/名词短语，表明概念。示例: `DataProcessor`, `ConfigurationManager`.
- 常量: (符号表定义) 全大写，下划线分隔 (SCREAMING_SNAKE_CASE)。示例: `MAX_RETRIES`.
- 布尔变量/函数: 变量名 `is`, `has`, `can` 等前缀。函数名 `is`, `has`, `can`, `check` 等前缀。示例: `isActive`, `canProcess`, `isEmpty()`, `checkStatus()`.
- 混合语言名称: 符号表允许且项目需要时可谨慎使用。建议外部符号表明确定义其英文/内部标识符。示例：`VAR:[Int] 用户计数`.

### 5.2 最佳实践

- 保持简洁: 伪代码描述核心逻辑，避免特定目标语言细节。
- 清晰缩进: 严格遵守约定，确保代码块结构清晰。
- 善用注释: `//` 解释逻辑，`@` 提供元数据/指令。注释应简洁准确。
- 明确类型: 尽可能使用 `VAR:[<类型>]` 指定类型，增强可读性安全性。
- 单一职责: 函数方法应只负责一个明确任务。
- 避免魔术数字/字符串: 使用变量或符号表常量。
- 合理命名: 选择自解释名称，避免单字母或不明确缩写。
- 控制流嵌套: 避免过深嵌套，考虑重构小函数。
- 错误处理: 使用 `IF/ELSE` 或内置日志/退出指令清晰描述错误检查处理。

## 6.完整示例

以下为完整 `.mcpc` 文件示例，综合使用上述语法，包括结构、核心元素、缩进和注释。改编自文件行反转逻辑，含类定义和使用。

```mcpc
// icp_file_processor.mcpc
// ICP Symbol-Pseudocode for a simple file line reversal module - Final Optimized Version

@ This module implements file line reversal logic.
@ It reads lines from an input file, reverses them, and writes to an output file.
@ All referenced external symbols (e.g., OPEN_FILE, LOG_ERROR) are assumed to be defined in icp_symbols.json.

// -----------------------------------------------------------------------------------
// Helper Class: LineBuffer (辅助类：行缓冲区)
// Manages a list of lines in memory.
CLASS LineBuffer: // 顶级类定义，0缩进
    // 类成员变量，缩进一层
    VAR:[List<String>] lines // 存储行的列表

    // Constructor (构造函数)
    FUNC __init__(): // 缩进一层
        // 方法体，缩进两层
        THIS.lines = [] // 初始化空列表
        // 方法体结束

    // Method to add a line (添加一行的方法)
    FUNC addLine(line [TYPE: String]): // 缩进一层
        // 方法体，缩进两层
        THIS.lines.APPEND(line) // 调用列表内置操作 APPEND
        // 方法体结束

    // Method to get all lines (获取所有行的方法)
    FUNC getLines(): // 缩进一层
        // 方法体，缩进两层
        RETURN THIS.lines // 返回内部列表
        // 方法体结束

    // Method to reverse lines in place (原地反转行的方法)
    FUNC reverseLinesInPlace(): // 缩进一层
        // 方法体，缩进两层
        @ Using a built-in efficient list reversal function.
        REVERSE_LIST_IN_PLACE(THIS.lines) // 调用内置操作 REVERSE_LIST_IN_PLACE
        // 方法体结束

END CLASS // LineBuffer 类结束，0缩进

// -----------------------------------------------------------------------------------
// Main Function: Reverse lines in a file (主函数：反转文件中的行)
// Takes input and output file paths, returns success status and optional error message.
FUNC reverseFileLines(input_filepath [TYPE: String], output_filepath [TYPE: String]): // 顶级函数，0缩进
    // 函数体开始，缩进一层 (4 spaces)
    VAR:[] inputFileHandle // 输入文件句柄，类型通常由 OPEN_FILE 返回值决定
    VAR:[] outputFileHandle // 输出文件句柄，类型通常由 OPEN_FILE 返回值决定
    VAR:[LineBuffer] buffer = NEW LineBuffer() // 创建 LineBuffer 实例
    VAR:[Boolean] successStatus = FALSE // 初始化成功状态
    VAR:[String] errorMessage = NULL // 初始化错误信息

    // Attempt to open the input file for reading.(尝试打开输入文件进行读取)
    @ Critical step: Handle potential file access errors.
    inputFileHandle = OPEN_FILE(input_filepath, "read") // 调用外部符号 OPEN_FILE

    // Check if file opening was successful (OPEN_FILE returns NULL on failure).
    IF inputFileHandle IS NULL: // 缩进一层
        // IF块体，处理失败情况，缩进两层
        errorMessage = "Failed to open input file for reading: " + input_filepath
        LOG_ERROR(errorMessage) // 调用外部符号 LOG_ERROR
        RETURN (FALSE, errorMessage) // 返回失败状态和错误信息
        // IF块结束，此处 RETURN 退出函数

    // If successful, read all lines from the file into the buffer.
    // (如果成功，读取文件所有行到缓冲区)
    VAR:[List<String>] linesRead = READ_ALL_LINES_FROM_HANDLE(inputFileHandle) // 调用外部符号
    FOR line IN linesRead: // 遍历读取到的行
        buffer.addLine(line) // 调用 LineBuffer 实例的方法
    // FOR 循环结束

    // Close the input file handle.(关闭输入文件句柄)
    CLOSE_FILE_HANDLE(inputFileHandle) // 调用外部符号

    // Reverse the order of lines in the buffer.(反转缓冲区中的行顺序)
    buffer.reverseLinesInPlace() // 调用 LineBuffer 实例的方法

    // Attempt to open the output file for writing.(尝试打开输出文件进行写入)
    outputFileHandle = OPEN_FILE(output_filepath, "write") // 调用外部符号

    // Check if output file opening was successful.(检查输出文件打开是否成功)
    IF outputFileHandle IS NULL: // 缩进一层
        // IF块体，处理失败情况，缩进两层
        errorMessage = "Failed to open output file for writing: " + output_filepath
        LOG_ERROR(errorMessage) // 记录错误日志
        RETURN (FALSE, errorMessage) // 返回失败状态和错误信息
        // IF块结束，此处 RETURN 退出函数

    // Write the reversed lines from the buffer to the output file.
    // (将反转后的行从缓冲区写入文件)
    VAR:[List<String>] reversedLines = buffer.getLines() // 获取反转后的行列表
    FOR currentLine IN reversedLines: // 遍历反转后的列表中的每一行
        WRITE_LINE_TO_HANDLE(outputFileHandle, currentLine) // 调用外部符号
    // FOR 循环结束

    // Close the output file handle.(关闭输出文件句柄)
    CLOSE_FILE_HANDLE(outputFileHandle) // 调用外部符号

    // Operation successful.(操作成功)
    successStatus = TRUE // 设置成功状态
    errorMessage = NULL // 没有错误
    RETURN (successStatus, errorMessage) // 返回结果

// 函数 reverseFileLines 结束，回到0缩进
```
