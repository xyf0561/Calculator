# Calculator
一个桌面计算器，实现解析用户输入的表达式，计算并显示结果的功能。

1 系统描述
一个桌面计算器，实现解析用户输入的表达式，计算并显示结果的功能。

2 系统功能
（1）以命令行方式解析用户输入的表达式，计算并显示结果；
（2）支持基本的整型和浮点类型数值计算；
（3）支持用变量和存储计算结果、变量引用，变量类型无需声明，可根据保存的数据变化。

3 实现语言和平台
使用C++语言，IDE为Visual Studio 2017，在Windows 10操作系统上测试通过。


4 系统实现
源代码清单：Calculator.cpp
	共6个函数：
				1、main
				2、toPostfix
				3、postfixValue
				4、dealWithInput
				5、dealWithExpree
				6、appearAssignmentExpression

可执行的系统程序：Calculator.exe
