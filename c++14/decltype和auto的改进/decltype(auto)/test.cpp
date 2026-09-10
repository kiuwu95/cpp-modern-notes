//decltype(auto)会将引用、const、volatile等特性完全保留下来
#include<iostream>
#include<vector>
using namespace std;
//引用
int& func1() {
    static int x = 1;
    return x;
}
auto func2() {
    return func1();
}//int返回类型
decltype(auto) func3() {
    return func1();
}//int&返回类型

decltype(auto) func4(vector<int>& v, const int& index) {
    return v[index];
}//int&返回类型

const int num = 2;
decltype(auto) p = num;//p为const int类型

// decltype对()的敏感性：
// 如果 decltype 里的参数是一个不加括号的变量名（如 x），推导结果就是该变量的类型。
// 如果decltype里的参数是一个表达式（如x + y或vec[i]），推导结果取决于该表达式的值类别：
// 只要 decltype 的参数被括号(...) 包裹，该参数在语法上就被视为一个表达式，而不是一个变量名。既然是表达式，接下来就要看这个表达式是左值 还是 右值：
// 如果是左值（L - value，如变量），推导结果为 类型的引用(T&)。
// 如果是右值（R - value，如临时对象或字面量），推导结果为 类型本身(T)。
int x = 1;
decltype(auto) w = (x);//int&

decltype(auto) i = (1);//int

int y = 2;
decltype(auto) l = (x + y);//int,x+y总的来说表达的是一个确定值3，而3是右值