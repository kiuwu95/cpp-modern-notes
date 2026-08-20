//using与typedef功能相同，起别名
#include<iostream>
#include<map>
#include<string>
using namespace std;
//模板的别名
template<typename T>
using MyMap = map<int, T>;

int main() {
    //给int起别名MyType
    using MyType = int;
    MyType a = 1;

    MyMap<string> mm1;
    mm1.insert({ 114514,"hhhaaaaaaaa" });

    MyMap<double> mm2;
    mm2.insert({ 314,3.1415926535 });
}