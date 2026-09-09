#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

class person {
public:
    string name;
    int age;
};

void FatoryFunc() {
    //lambda组成的工厂函数
    auto compare = [](const auto memberptr) {
        return [memberptr](const auto& p1, const auto& p2) {
            return p1.*memberptr > p2.*memberptr;
            };
        };
    vector<person>pp = {
        { "Alice",18 },{ "Bob",12 },{ "Mike",25 }
    };
    sort(pp.begin(), pp.end(), compare(&person::age));
    for (auto& it : pp) {
        cout << it.name << " " << it.age << endl;
    }
    //这里的&person::age指的是成员指针，是在person作用域下指向age成员的指针，其功能类似于下面这种：
    // 定义成员指针
    // int person::* memberPtr = &person::age;
    // 创建对象
    // person p1{ "Alice", 18 };
    // person p2{ "Bob", 12 };
    // 通过成员指针访问成员
    // cout << p1.*memberPtr << endl;  // 输出 18
    // cout << p2.*memberPtr << endl;  // 输出 12

    sort(pp.begin(), pp.end(), compare(&person::name));
    for (auto& it : pp) {
        cout << it.name << " " << it.age << endl;
    }
}

void FunctionCombinator() {
    auto func1 = [](const auto& x) {return x - 1;};
    auto func2 = [](const auto& x) {return x * 2;};
    auto func3 = [](const auto& x) {return to_string(x);};
    //lambda构成的组合器函数
    auto Combinator = [](const auto& f1, const auto& f2) {
        return[f1, f2](const auto x) {
            return f2(f1(x));
            };
        };

    //先减一后乘二
    auto c1 = Combinator(func1, func2);
    cout << c1(4) << endl;
    //先乘二后转字符串
    auto c2 = Combinator(func2, func3);
    cout << c2(8) << endl;
}

int main() {
    FatoryFunc();
    FunctionCombinator();
}