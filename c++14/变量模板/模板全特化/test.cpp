#include<iostream>
#include<vector>
using namespace std;
//定义一个计算类型大小的模板为例：
//主模板
template<class T>
constexpr size_t Typesize = sizeof(T);
//特化模板：比较特别的可以单独写出来作特化
template<>
constexpr size_t Typesize < vector<int>> = 114514;//假设对于vector<int>类型其大小为114514

//返回依赖模板的参数类型
//以计算圆的周长为例：
template<class T, T r>
constexpr T calculateCircumference = 2 * 3.1415926535 * r;

int main() {
    cout << Typesize<int> << endl << Typesize<float> << endl << Typesize<vector<int>> << endl;

    cout << calculateCircumference<int, 4> << endl//非类型参数不能为float和double，直到c++20为止
        << calculateCircumference<int, 5> << endl
        << calculateCircumference<int, 1> << endl;
}