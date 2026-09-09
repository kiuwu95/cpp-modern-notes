#include<iostream>
using namespace std;
//1.c++14可以在constexpr修饰的函数中使用if-else、switch、for等，而c++11只能存在return那一行代码
constexpr int func(int num, int times) {
    //计算num的times次方
    int res = 1;
    for (int i = 1;i <= times;i++, res *= num);
    return res;
}
//2.c++14中，constexpr可以修饰void类型的函数，而在c++11中不可以
constexpr void func2() {
    cout << "Hello,world!" << endl;
}
//3.c++11中，对类内函数施加constexpr进行修饰会默认在该函数后面添加const修饰，即该函数内无法修改该类中的成员变量。
//而在c++14中，则不会使用const默认修饰
class test {
public:
    constexpr void print() {
        cout << "Test,test." << endl;
    }
    //4.c++11中，被constexpr修饰的构造函数中只能存在初始化列表赋值内容，函数体内为空
    //c++14中则可以在函数体中写些内容
    constexpr test(int data) :m_data(data) {
        cout << "test has been created!" << endl;
    }
private:
    int m_data;
};