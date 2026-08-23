#include<iostream>
using namespace std;

class test {
public:
    int* ptr;

    test(int num) :ptr(new int(num)) {};
    //拷贝构造函数
    test(const test& t) :ptr(new int(*t.ptr)) {};
    //移动构造函数，浅拷贝，针对于即将被析构的变量
    test(test&& t) :ptr(t.ptr) {
        t.ptr = nullptr;
    };

    ~test() {
        if (ptr != nullptr) {
            delete ptr;
        }
    }

};
//右值函数
test func() {
    test t(10);
    cout << t.ptr << endl;
    return t;
}
int main() {
    //浅拷贝
    test t1 = func();
    cout << t1.ptr << endl;
}
//&&在自动推导上的应用详见https://subingwen.cn/cpp/rvalue-reference/#3-%E7%9A%84%E7%89%B9%E6%80%A7