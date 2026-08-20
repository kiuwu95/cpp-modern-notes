#include<iostream>
#include<string>
using namespace std;

class Base {
public:
    string m_string;
    int m_A;
    double m_B;

    Base(string str) {
        m_string = str;
    }
    Base(string str, int A) :Base(str) {
        m_A = A;
    }
    Base(string str, int A, int B) :Base(str, A) {
        m_B = B;
    }

    void func(int num) {
        cout << "The number is " << num << endl;
    }

    void func(int num, string str) {
        cout << "The number is " << num << endl;
        cout << "The string is " << str << endl;
    }
};

class Son :public Base {
public:
    //继承了父类的构造函数
    using Base::Base;
    //继承了父类的func函数，这样子类拥有重载的函数时，所继承的父类func函数也不会被隐藏
    using Base::func;
    void func() {
        cout << "Son func的调用" << endl;
    }
};

int main() {
    Son s1("");
    s1.func();
}