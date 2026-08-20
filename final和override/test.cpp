#include<iostream>
using namespace std;
class base {
public:
    virtual void func() = 0;
};
class son1 :public base {
public:
    //对于一类中的虚函数函数加上final则表示其子类无法重写该虚函数。final只能写在虚函数上
    virtual void func() override final {
        cout << "son1 func()" << endl;
    }
};
class son2 :public base {
public:
    //重写虚函数时加上override可以更好地展示这个函数是重写的虚函数，也可不加。写上override时，编译器也会自动检测是否重写合理。
    virtual void func() override {
        cout << "son2 func()" << endl;
    }
};
//用final修饰类则表示该类无法被任何类继承
class grandson final :public son1 {
public:

};