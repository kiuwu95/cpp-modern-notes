#include<iostream>
#include<functional>
using namespace std;
//引用捕获
void ReferenceCapture() {
    int num = 123;
    //c++11捕获
    auto func1 = [&num]() {};
    //c++14新增捕获：
    //cap是num的引用
    auto func2 = [&cap = num]() {
        cap = 321;
        cout << cap << endl;
        };
    //ref将cap包装成一个引用包装器
    auto func3 = [cap = ref(num)]() {
        cap.get() = 123;//需通过get的方式获得cap的值
        cout << cap.get() << endl;
        };
    //常量引用初始化
    auto func4 = [&cap = static_cast<const int&>(num)]() {
        cout << cap << endl;//只读
        };
    //cref与ref的区别是cref是const属性的
    auto func5 = [&cap = cref(num)]() {
        cout << cap << endl;//只读
        };
}