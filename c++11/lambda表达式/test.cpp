//详细知识请参见https://subingwen.cn/cpp/lambda/

// [capture](params) opt->ret{ body; };
// 其中capture是捕获列表，params是参数列表，opt是函数选项（不需要可以省略），ret是返回值类型，body是函数体。

#include<iostream>
#include<functional>
#include<vector>
#include<algorithm>
using namespace std;
int main() {
    //sort+lambda表达式的使用
    vector<int>v1 = { 2,3,6,1,98,0,-1 };
    sort(v1.begin(), v1.end(), [](const int& a, const int& b)->bool {return a > b;});
    for (auto it : v1) {
        cout << it << " ";
    }
}