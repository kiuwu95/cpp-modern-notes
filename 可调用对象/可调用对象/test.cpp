#include<iostream>
using namespace std;
//1.函数指针
void print(int a, double b) {
    cout << a << " " << b << endl;
}
using MyPrint_ptr1 = void(*)(int, double);
//2.类中的仿函数
class MyPrint1 {
public:
    void print(int a, double b) {
        cout << a << " " << b << endl;
    }

    void operator()(int a, double b) {
        cout << a << " " << b << endl;
    }
};
//3.可被转换为函数指针的类对象
class MyPrint2 {
public:
    static void print(int a, double b) {
        cout << a << " " << b << endl;
    }

    operator MyPrint_ptr1() {
        return print;//必须为静态函数
    }
};

int main() {
    MyPrint_ptr1 p = print;
    p(1, 3.14);

    MyPrint1 p1;
    p1(2, 1.1);

    MyPrint2 p2;
    p2(3, 1.3);
    //4.类成员函数指针或者类成员指针
    using MyPrint_ptr2 = void (MyPrint1::*)(int, double);
    MyPrint_ptr2 p3 = &MyPrint1::print;
    (p1.*p3)(114, 514);
}