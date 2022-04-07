# agps

a parser to parse arguments

一个平时作业用的参数解析器。

目前支持的类型：整形、标志、字符串

## 使用方式

### 主要类名

- Type 枚举类。标识参数类型，目前包含 FLAG、INT、STR
- value 联合体，记录以上的一种信息
- Parser 分析器。

### 主要方法

- Parser::add 设定参数规则
	- Type type 参数类型
	- char short_name 短名字
	- const char *long_name 长名字
	- const char *infomation 提示信息
	- bool is_necessary = true 必须参数
	- const Value &default_value = VALUE_NONE 默认值
	- bool (*check_func)(Value) = nullptr 检查合法性。返回true 则合法
- Parser::parse 分析参数
	- int argc 参数数
	- const char **argv 参数数组
- Parser::success() 解析成功并参数值全合法
- Parser::get(char short_name) 用短名获取值
- Parser::get(const char *long_name) 用长名获取值
- Parser::isExist(char short_name) 参数存在于命令行
- Parser::isExist(const char *long_name) 参数存在于命令行
- Parser::printUsage(const char *name, FILE *out_stream = stdout) 输出提示
- Parser::reset() 重置参数为默认值
- Parser::clean() 清空解析器

详情可看 test.cpp

## 代办

1. 将解析过的参数保存以免原字符串改变
2. 获取剩余参数
3. 带参宏定义，用于提供基本的字符串规则判断例如yes/no/y/n之类
4. 维修整形参数解析比如 11a 时不报错而解析为 11 的问题
5. 重载 get 使能够直接通过引用获得值