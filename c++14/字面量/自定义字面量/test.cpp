#include<iostream>
#include<string>
using namespace std;

//整形自定义字面量的参数类型必须为unsigned long long，返回类型随意
constexpr unsigned long long operator"" _km(unsigned long long distance) {
    return distance * 1000;
}
//浮点型自定义字面量的参数类型必须为long double，返回类型随意
constexpr long double operator"" _ct(long double num) {
    return num / 10;
}
//字符型自定义字面量
constexpr char operator"" _upper(char ch) {
    if (ch >= 'a' && ch <= 'z')return ch - 'a' + 'A';
    return ch;
}
//字符串自定义字面量的参数类型必须为“const char* 变量名, size_t 变量名”，其中size_t所对应的为字符串长度
string operator"" _add(const char* str, size_t len) {
    return "(" + string(str, len) + ")";
}

int main() {
    cout << 5_km << endl;//转5千米

    cout << 10.0_ct << endl;//除以10

    cout << 'a'_upper << endl;//转大写

    cout << "hello"_add << endl;//字符串左右加括号
}