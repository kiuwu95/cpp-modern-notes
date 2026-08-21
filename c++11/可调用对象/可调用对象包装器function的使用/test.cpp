#include<iostream>
#include<functional>
using namespace std;

void print(int a, double b) {
    cout << a << " " << b << endl;
}
using MyPrint_ptr1 = void(*)(int, double);

class MyPrint1 {
public:
    void print(int a, double b) {
        cout << a << " " << b << endl;
    }

    void operator()(int a, double b) {
        cout << a << " " << b << endl;
    }
};

class MyPrint2 {
public:
    static void print(int a, double b) {
        cout << a << " " << b << endl;
    }

    operator MyPrint_ptr1() {
        return print;
    }
};

class bb {
private:
    function<void(int, double)> func;
public:
    // 构造函数参数是一个包装器对象
    bb(const function<void(int, double)>& f) :func(f) {}

    void print(int a, double b) {
        func(a, b);// 调用通过构造函数得到的函数指针
    }
};
int main() {
    //1.包装普通函数
    function<void(int, double)> f = print;
    bb b1(print);
    b1.print(1, 1.1);
    //2.包装类的静态函数
    function<void(int, double)> f1 = MyPrint2::print;
    bb b2(MyPrint2::print);
    b2.print(1, 1.1);
    //3.包装类的仿函数
    MyPrint1 p1;
    function<void(int, double)> f2 = p1;
    bb b3(p1);
    b3.print(1, 1.1);
    //4.包装转换为函数指针的对象
    MyPrint2 p2;
    function<void(int, double)> f3 = p2;
    bb b4(p2);
    b1.print(1, 1.1);
}