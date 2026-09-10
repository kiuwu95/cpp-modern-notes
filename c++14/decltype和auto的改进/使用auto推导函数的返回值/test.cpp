#include<iostream>
using namespace std;
//1.若有多个返回值，则这多个返回值的类型必须相同
auto func1(int x, double y) {
    if (x / 2) {
        return x + y;
    }
    return static_cast<double>(1);
}
//2.若是递归函数，则必须在该函数中确定边界以确定返回值类型
auto func2(int x) {
    if (x == 1)return x;
    return x * func2(x - 1);
}
//3.在auto推导中，引用会被去除，const和volatile会被省略，const指针除外
auto func3() {
    const int num = 1;
    return num;
}

int& func4() {
    static int x = 1;//静态变量，不静态则会在栈区释放掉
    return x;
}
auto func5() {
    return func4();
}//int类型函数
auto& func6() {
    return func4();
}//int&类型函数

auto func7() {
    const int* ptr = new int(2);//在堆区上被开辟，不会再栈区被释放
    return ptr;
}//const int*类型函数