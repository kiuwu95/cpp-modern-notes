#include<iostream>
using namespace std;
class A;
class B {
    //在类中声明另一个类为友元时不再需要class关键字，还可使用别名
    friend B;
};
//在类中还可通过模板声明友元,这样在那个友元类里面就可以调用这个类里面的私有属性的数据
template<class T>
class test {
    friend T;
private:
    int m_data;
};