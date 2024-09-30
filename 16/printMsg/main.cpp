#include <iostream>
#include <sstream>
#include <string>

// 处理基础类型的 debug_rep
template <typename T>
std::string debug_rep(const T& t) {
    std::ostringstream ret;
    ret << t;  // 输出到字符串流
    return ret.str();
}

// 专门化处理指针类型
template <typename T>
std::string debug_rep(T* p) {
    std::ostringstream ret;
    ret << "pointer: " << p;  // 输出指针地址
    if (p)
        ret << " " << debug_rep(*p);  // 输出指向的值
    else
        ret << " null pointer";  // 如果是空指针
    return ret.str();
}

// 专门化处理 const char*
std::string debug_rep(const char* p) {
    return debug_rep(std::string(p));  // 转换为 std::string 处理
}

// 专门化处理 std::string
std::string debug_rep(const std::string& s) {
    return '"' + s + '"';  // 输出字符串加上引号
}

// print 函数：递归出口，用于结束递归
std::ostream& print(std::ostream& os) {
    return os;  // 什么都不做，返回 os
}

// print 函数：可变参数版本
template <typename T, typename... Args>
std::ostream& print(std::ostream& os, const T& firstArg, const Args&... rest) {
    os << firstArg;  // 输出第一个参数
    if (sizeof...(rest) != 0)  // 如果还有其他参数
        os << ", ";  // 加逗号分隔
    return print(os, rest...);  // 递归处理剩余参数
}

// errorMsg 函数：接收可变参数并调用 print
template<typename... Args>
std::ostream& errorMsg(std::ostream& os, const Args&... rest) {
    return print(os, debug_rep(rest)...);  // 使用 debug_rep 处理每个参数
}

// 测试代码
int main() {
    int i = 42;
    std::string s = "Hello, world!";
    double d = 3.14;

    errorMsg(std::cout, i, s, d) << std::endl;
    errorMsg(std::cout, "Error in file", "main.cpp", "on line", 42) << std::endl;
    errorMsg(std::cout, &i, &s) << std::endl;

    return 0;
}
