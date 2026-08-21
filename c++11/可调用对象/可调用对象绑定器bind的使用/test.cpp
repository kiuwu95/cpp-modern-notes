#include<iostream>
#include<functional>
using namespace std;

int Minus(int a, int b) {
    return a - b;
}

class test {
public:
    int num;
    test(int num) {
        this->num = num;
    }
    void print(int a, int b) {
        cout << "先" << a << "后" << b << endl;
    }
};

int main() {
    //仿函数
    auto m1 = bind(Minus, placeholders::_1, placeholders::_2)(33, 22);
    cout << m1 << endl;

    auto m2 = bind(Minus, 33, 22);
    cout << m2() << endl;

    auto m3 = bind(Minus, placeholders::_2, placeholders::_1);
    cout << m3(3, 2) << endl;

    auto m4 = bind(Minus, placeholders::_1, 4);
    cout << m4(6) << endl;
    //包装
    function<int(int, int)>f1 = bind(Minus, placeholders::_1, placeholders::_2);
    cout << f1(3, 2) << endl;;

    test t1(114514);
    auto p1 = bind(&test::print, &t1, placeholders::_1, placeholders::_2);
    p1(3, 4);
    function<void(int, int)>f2 = bind(&test::print, &t1, placeholders::_1, placeholders::_2);
    f2(5, 6);

    auto p2 = bind(&test::num, &t1);
    cout << p2() << endl;
    function<int& ()>f3 = bind(&test::num, &t1);
    cout << f3() << endl;
    f3() = 67;
    cout << f3() << endl;
}