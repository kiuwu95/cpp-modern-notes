#include<iostream>
using namespace std;
//static_assert()的作用：与assert的作用相同，只不过static_assert在编译期间就开始发挥作用，且不需要引用头文件。

//判断是否为32位系统
int main() {
    //static_assert(参数1,参数2)中，参数1是判断条件，参数2为字符串类型，以显示报错后输出的信息。
    static_assert(sizeof(long long) == 4, "该系统不是Windows32位系统！");
    cout << "hello,world" << endl;
}