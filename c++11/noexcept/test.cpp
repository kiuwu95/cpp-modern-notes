#include<iostream>
using namespace std;
//noexcept表示函数不会抛出异常。如果内部抛出异常则编译器直接调用terminate()终止程序。
//使用noexcept可以换取标准库高性能行为
int calculate(int& a, int& b) noexcept {
    if (b == 0) {
        cout << "b can't be zero!" << endl;
        return;
    }
    return a / b;
}

// ## 四、工程什么时候写 noexcept？✅推荐 / ❌不推荐

// ✅ 建议加上 noexcept：

// 1. 析构函数（默认就是）
// 2. 移动构造函数、移动赋值运算符
// 3. swap 交换函数
// 4. 简单计算、不会失败的工具函数

// ❌ 不要随便加 noexcept：

// 1. 函数内部有可能抛出异常的业务逻辑；一旦加了，抛异常直接程序终止。
// 2. 接口函数，未来版本可能会抛出异常，不要过早锁死 noexcept 契约。