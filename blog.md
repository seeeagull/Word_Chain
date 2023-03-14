| 项目                                     | 内容                                                         |
| :--------------------------------------- | :----------------------------------------------------------- |
| 这个作业属于哪个课程                     | [2022 年北航敏捷软件工程](https://bbs.csdn.net/forums/buaa-ase2023) |
| 这个作业的要求在哪里                     | [结对编程项目-最长英语单词链](https://bbs.csdn.net/topics/613883108) |
| 我在这个课程的目标是                     | 了解并体验软件工程，实现从「程序」到「软件」的进展。         |
| 这个作业在哪个**具体方面**帮助我实现目标 | 体验结对编程，初步实践工程化开发。                           |

### 教学班级及项目地址

> - 教学班级：周四班
> - 项目地址：https://github.com/seeeagull/Word_Chain

### PSP表格-预期

| **PSP2.1**                              | **Personal Software Process Stages**    | **预估耗时（分钟）** |
| :-------------------------------------- | :-------------------------------------- | :------------------- |
| Planning                                | 计划                                    | 60                   |
| · Estimate                              | · 估计这个任务需要多少时间              | 10                   |
| Development                             | 开发                                    | 2200                 |
| · Analysis                              | · 需求分析 (包括学习新技术)             | 120                  |
| · Design Spec                           | · 生成设计文档                          | 60                   |
| · Design Review                         | · 设计复审 (和同事审核设计文档)         | 250                  |
| · Coding Standard                       | · 代码规范 (为目前的开发制定合适的规范) | 60                   |
| · Design                                | · 具体设计                              | 140                  |
| · Coding                                | · 具体编码                              | 720                  |
| · Code Review                           | · 代码复审                              | 360                  |
| · Test                                  | · 测试 (自我测试，修改代码，提交修改)   | 490                  |
| Reporting                               | 报告                                    | 160                  |
| · Test Report                           | · 测试报告                              | 60                   |
| · Size Measurement                      | · 计算工作量                            | 20                   |
| · Postmortem & Process Improvement Plan | · 事后总结, 并提出过程改进计划          | 80                   |
|                                         | 合计                                    | 2420                 |

### 设计理念

> todo 看教科书和其它资料中关于 Information Hiding，Interface Design，Loose Coupling 的章节，说明你们在结对编程中是如何利用这些方法对接口进行设计的。

- **信息隐藏(Infromation Hiding)：**
- **接口设计(Interface Design)：**
- **松耦合(loose coupling)：**

### 计算模块接口的设计与实现过程

> todo 设计包括代码如何组织，比如会有几个类，几个函数，他们之间关系如何，关键函数是否需要画出流程图？说明你的算法的关键（不必列出源代码），以及独到之处。



### 开发环境下编译通过无警告

> todo 展示在所在开发环境下编译器编译通过无警告的截图

### UML图

> todo 阅读有关 UML 的内容，画出 UML 图显示计算模块部分各个实体之间的关系（画一个图即可）https://en.wikipedia.org/wiki/Unified_Modeling_Language

### 计算模块接口部分的性能改进

> todo 记录在改进计算模块性能上所花费的时间，并展示你程序中消耗最大的函数，陈述你的性能改进策略。

### 关于Design by Contract / Code Contract的思考

> todo 阅读 Design by Contract，Code Contract 的内容，并描述这些做法的优缺点，说明你是如何把它们融入结对作业中的。
>
> * http://en.wikipedia.org/wiki/Design_by_contract
> * http://msdn.microsoft.com/en-us/devlabs/dd491992.aspx

### 单元测试

> todo **计算模块部分单元测试展示。\**\*\*展示出项目部分单元测试代码，并说明测试的函数，构造测试数据的思路。并\*\**\*将单元测试得到的测试覆盖率截图**，发表在博客中。要求总体覆盖率到 90% 以上，否则单元测试部分视作无效。

测试使用了1.12.1版本的google gtest，分为正确性测试、鲁棒性测试、性能测试三部分。共构造有不同特征的12个testcase，分别针对合法参数、非法参数、有环场景来设计测试。

| testcase | 自环 | 环   | 长为1单词 | 重复单词 | 混淆字符 | 数据合法性 | 描述                         | 测试参数                            |
| -------- | ---- | ---- | --------- | -------- | -------- | ---------- | ---------------------------- | ----------------------------------- |
| 1        | 有   | 无   | 无        | 无       | 无       | 合法       | 图中只有自环                 | [-n]                                |
| 2        | 有   | 有   | 有        | 有       | 有       | 合法       | 测试中文字符、希腊字母       | \[-r -w -h c -j v][-c -r -j h -t j] |
| 3        | 有   | 无   | 有        | 有       | 有       | 合法       | 自环在最长链首               | \[-w]                               |
| 4        | 有   | 无   | 有        | 有       | 有       | 合法       | 自环在最长链尾               | [-c]                                |
| 5        | 无   | 有   | 无        | 有       | 无       | 合法       | 最长链有多个环               | [-c  -j h -r]                       |
| 6        | 无   | 有   | 无        | 有       | 无       | 合法       | 多个孤立环/链                | [-w -t t -r]\[-w -h n -r]           |
| 7        | 有   | 有   | 有        | 有       | 有       | 合法       | 有自环的完全图               | [-w -r]\[-w -t b -r]                |
| 8        | 有   | 有   | 无        | 有       | 有       | 合法       | 只有一个环，每个单词都有自环 | [-c -r]                             |
| 9        | 有   | 有   | 有        | 有       | 有       | 合法       | 平平无奇                     | [-c -h j -t z -r]                   |
| 10       | 无   | 无   | 无        | 无       | 无       | 合法？todo | 只有一个单词，长度很长       | [-w -j b]                           |
| 11       |      |      |           |          |          | 不合法     | 非txt文件                    |                                     |
| 12       |      |      |           |          |          | 合法       | 文件不含单词                 | [-n]                                |

#### 正确性测试

见上表测试参数，使用gcov进行测试覆盖率分析，覆盖率为todo。

todo 补充覆盖率截图

部分testcase代码如下。

```c++
TEST(correctness_test, testcase1) {
    const char *file_name = "../testcase/testcase1.txt";
    const char *argv[] = {"Wordlist.exe", "-n", file_name};
    WordChain word_chain((std::string(file_name)));
    word_chain.BuildGraph();
    int std_res = word_chain.GetChainCnt();
    word_chain.OutputFile("../output/output1_std.txt");
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../output/output1.txt");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(res, std_res);
}

TEST(correctness_test, testcase2_1) {
    const char *file_name = "../testcase/testcase2.txt";
    const char *argv[] = {"Wordlist.exe", "-r", "-h", "c", "-j", "v", "-w", file_name};
    WordChain word_chain((std::string(file_name)));
    word_chain.BuildGraph();
    int std_res = word_chain.GetMostWordChain('c', '0', 'v');
    word_chain.OutputFile("../output/output2_1_std.txt");
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res,
                             "../output/output2_1.txt");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(res, std_res);
}

TEST(correctness_test, testcase2_2) {
    const char *file_name = "../testcase/testcase2.txt";
    const char *argv[] = {"Wordlist.exe", "-r", "-j", "h", "-t", "j", "-c", file_name};
    WordChain word_chain((std::string(file_name)));
    word_chain.BuildGraph();
    int std_res = word_chain.GetMostCharChain('0', 'j', 'h');
    word_chain.OutputFile("../output/output2_2_std.txt");
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res,
                             "../output/output2_2.txt");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(res, std_res);
}
```

#### 鲁棒性测试

见下文异常处理部分。

#### 性能测试

todo

### 异常处理

> todo 在博客中详细介绍每种异常的设计目标。每种异常都要选择一个单元测试样例发布在博客中，并指明错误对应的场景。

我们共支持了以下13种异常，每一种异常都进行了单元测试。

todo 12 13未构造

| case | intsr                                       | 场景                              | expcode             |
| ---- | ------------------------------------------- | --------------------------------- | ------------------- |
| 1    | Wordlist.exe -n                             | 参数中没有文件                    | NO_FILE_PATH        |
| 2    | Wordlist.exe -n testcase1.txt testcase2.txt | 参数中多个文件                    | MULTI_FILE_PATH     |
| 3    | Wordlist.exe -n testcase0.txt               | 参数中文件不存在                  | FILE_NOT_EXISTS     |
| 4    | Wordlist.exe -n testcase11.c                | 参数中文件不是txt文件             | FILE_TYPE_ERROR     |
| 5    | Wordlist.exe -q testcase1.txt               | 非法参数                          | ILLEGAL_PARAM       |
| 6    | Wordlist.exe -h a -t s testcase1.txt        | 无功能性参数                      | NO_FUNCTIONAL_PARAM |
| 7    | Wordlist.exe -n -w testcase1.txt            | 参数冲突                          | PARAMS_CONFLICT     |
| 8    | Wordlist.exe -w -w  testcase1.txt           | 多次指定相同参数                  | DUPLICATE_PARAM     |
| 9    | Wordlist.exe -h                             | -h -t -j参数没有接字符串          | CHAR_NOT_ASSIGN     |
| 10   | Wordlist.exe -h AB                          | -h -t -j参数接的字符串不合法      | ILLEGAL_CHAR        |
| 11   | Wordlist.exe -w testcase5.txt               | 未指定-r但出现环                  | UNEXPECTED_LOOP     |
| 12   | todo                                        | 单词数超过20000                   | LENGTH_OVERFLOW     |
| 13   | 用户输入单词不合法                          | 仅可以是{\space}\*{\\w}\*{\space} | ILLEGAL_INPUT       |

对应的testcase代码如下。

```c++
TEST(robustness_test, testcase1) {
    const char *argv[] = {"Wordlist.exe", "-n"};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp1.txt");
    EXPECT_EQ(ret, kNoFilePath);
}

TEST(robustness_test, testcase2) {
    const char *argv[] = {"Wordlist.exe", "-n", "../testcase/testcase2.txt", "../testcase/testcase2.txt"};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp2.txt");
    EXPECT_EQ(ret, kMultiFilePath);
}

TEST(robustness_test, testcase3) {
    const char *argv[] = {"Wordlist.exe", "-n", "../testcase/testcase0.txt"};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp3.txt");
    EXPECT_EQ(ret, kFileNotExists);
}

TEST(robustness_test, testcase4) {
    const char *argv[] = {"Wordlist.exe", "-n", "../testcase/testcase11.c"};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp4.txt");
    EXPECT_EQ(ret, kFileTypeError);
}

TEST(robustness_test, testcase5) {
    const char *argv[] = {"Wordlist.exe", "-q", "../testcase/testcase1.txt"};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp5.txt");
    EXPECT_EQ(ret, kIllegalParam);
}

TEST(robustness_test, testcase6) {
    const char *argv[] = {"Wordlist.exe", "-h", "a", "-t", "s", "../testcase/testcase1.txt"};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp6.txt");
    EXPECT_EQ(ret, kNoFunctionalParam);
}

TEST(robustness_test, testcase7) {
    const char *argv[] = {"Wordlist.exe", "-n", "../testcase/testcase1.txt", "-w"};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp7.txt");
    EXPECT_EQ(ret, kParamsConflict);
}

TEST(robustness_test, testcase8) {
    const char *argv[] = {"Wordlist.exe", "-w", "../testcase/testcase1.txt", "-w"};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp8.txt");
    EXPECT_EQ(ret, kDuplicateParam);
}

TEST(robustness_test, testcase9) {
    const char *argv[] = {"Wordlist.exe", "-h", "../testcase/testcase1.txt"};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp9.txt");
    EXPECT_EQ(ret, kCharNotAssign);
}

TEST(robustness_test, testcase10) {
    const char *argv[] = {"Wordlist.exe", "-h", "AB", "../testcase/testcase1.txt"};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp10.txt");
    EXPECT_EQ(ret, kIllegalChar);
}

TEST(robustness_test, testcase11) {
    const char *argv[] = {"Wordlist.exe", "-w", "../testcase/testcase5.txt"};
    int res;
    int ret = controller.Cmd(sizeof(argv) / sizeof(argv[0]), const_cast<char **>(argv), &res, "../exp11.txt");
    EXPECT_EQ(ret, kUnexpectedLoop);
}

todo 12 13
```

### UI设计

> todo 在博客中详细介绍界面模块是如何设计的，并写一些必要的代码说明解释实现过程。

界面模块采用C++的Qt6实现，整体效果如下：

- macos

    todo 图片

- windows

    todo 图片

UI分成两个部分。上侧用于选择目标功能、进行限制、点击求解、导入待处理txt文件、保存求解结果；下侧分成两部分，左侧用于展示待处理文本，右侧用于展示求解结果。

### 界面模块与计算模块的对接

> todo 详细地描述 UI 模块的设计与两个模块的对接，并在博客中截图实现的功能。

### 结对过程

> todo 提供两人在讨论的结对图像资料（比如 Live Share 的截图）。关于如何远程进行结对参见作业最后的注意事项。

### 优缺点

> todo 看教科书和其它参考书，网站中关于结对编程的章节，例如：http://www.cnblogs.com/xinz/archive/2011/08/07/2130332.html ，说明结对编程的优点和缺点。同时描述结对的每一个人的优点和缺点在哪里（要列出至少三个优点和一个缺点）。

- 结对编程优缺点
- jyz优缺点
- ljc优缺点

### PSP表格-实际

| **PSP2.1**                              | **Personal Software Process Stages**    | **预估耗时（分钟）** | **实际耗时（分钟）** |
| :-------------------------------------- | :-------------------------------------- | :------------------- | :------------------- |
| Planning                                | 计划                                    | 60                   | 60                   |
| · Estimate                              | · 估计这个任务需要多少时间              | 10                   | 10                   |
| Development                             | 开发                                    | 2200                 | 3100                 |
| · Analysis                              | · 需求分析 (包括学习新技术)             | 120                  | 150                  |
| · Design Spec                           | · 生成设计文档                          | 60                   | 100                  |
| · Design Review                         | · 设计复审 (和同事审核设计文档)         | 250                  | 120                  |
| · Coding Standard                       | · 代码规范 (为目前的开发制定合适的规范) | 60                   | 40                   |
| · Design                                | · 具体设计                              | 140                  | 220                  |
| · Coding                                | · 具体编码                              | 720                  | 1460                 |
| · Code Review                           | · 代码复审                              | 360                  | 400                  |
| · Test                                  | · 测试 (自我测试，修改代码，提交修改)   | 490                  | 620                  |
| Reporting                               | 报告                                    | 160                  | 250                  |
| · Test Report                           | · 测试报告                              | 60                   | 140                  |
| · Size Measurement                      | · 计算工作量                            | 20                   | 20                   |
| · Postmortem & Process Improvement Plan | · 事后总结, 并提出过程改进计划          | 80                   | 90                   |
|                                         | 合计                                    | 2420                 | 3410                 |

### 附加-模块松耦合

> todo 在博客中指明合作小组两位同学的学号，分析两组不同的模块合并之后出现的问题，为何会出现这样的问题，以及是如何根据反馈改进自己模块的。







### todo

- dll
- 对接GUI
- 覆盖率 gcov
- robustness测试
- 性能测试
- 20000测试