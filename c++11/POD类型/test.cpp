//关于如何判断POD类型以及平凡类型和标准模板类型请详见https://subingwen.cn/cpp/POD/
#include<iostream>
using namespace std;

class test1 {
public:
    static int a;
};
class test2 :public test1 {
public:
    int b;
    test1 t;//基类变量不应放在第一个位置以便实现优化
};

class test3 {
public:
    int a;
protected:
    int b;
private:
    int c;
};

class test4 {
public:
    int a;
    test4() {}//只要写出了构造函数则为非平凡
};
class test5 :public test4 {
public:
    int b;
    test5() = default;
};//基类非平凡，则派生类也非平凡

int main() {
    //is_trivial用来判断类型是否为平凡类型，is_standard_layout用来判断类型是否为标准模板类型。
    cout << "test2:" << endl << "is_trivial:";
    cout << is_trivial<test2>::value << endl;
    cout << "test2:" << endl << "is_standard_layout:";
    cout << is_standard_layout<test2>::value << endl;
    cout << "test3:" << endl << "is_trivial:";
    cout << is_trivial<test3>::value << endl;
    cout << "test3:" << endl << "is_standard_layout:";
    cout << is_standard_layout<test3>::value << endl;
    cout << "test4:" << endl << "is_trivial:";
    cout << is_trivial<test4>::value << endl;
    cout << "test5:" << endl << "is_trivial:";
    cout << is_trivial<test5>::value << endl;
    cout << "test5:" << endl << "is_standard_layout:";
    cout << is_standard_layout<test5>::value << endl;
}