#include<iostream>
using namespace std;
struct test1 {
    // 位域宽度（指定一个整型成员使用多少个比特（bit）来存储数据）：unsigned int x : WIDTH
    unsigned int x : 4;//4比特，最大能储存15（1111）
};
struct alignas(8) test2 {//以8字节对齐
    int x;//4字节
    char str[13];//13字节
    double y;//8字节
    char z;//1字节
};
int main() {
    // 一些需要编译时常量的场景：
    // 数组大小：int array[N];
    // 模板非类型参数：template<int N>
    // case标签：case VALUE :
    // 位域宽度（指定一个整型成员使用多少个比特（bit）来存储数据）：unsigned int x : WIDTH
    test1 t1;
    t1.x = 15;
    // 枚举值初始化：enum E{ val = N };
    // 对齐说明符：alignas(N) 是C++11引入的对齐说明符，用于显式指定变量、类、结构体或数组在内存中的对齐方式
    test2 t2;
    //8的倍数对齐
    cout << sizeof(t2) << endl;//最终大小为40字节，x和str共占了17字节，比16多出来的那一个字节因为8字节对齐原则所以要空出7字节的空间，之后才到y
}