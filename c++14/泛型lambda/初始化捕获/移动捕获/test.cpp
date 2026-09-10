#include<iostream>
#include<functional>
#include<memory>
#include<vector>
using namespace std;

void MoveCapture() {
    //以vector举例
    vector<int>vec = { 1,2,3,4,5 };
    //v=move(vec)同样是值捕获，如果不加mutable则无法在函数体中修改v的值
    auto func1 = [v = move(vec)/*移动构造的等号右边是右值*/]() mutable {
        v.push_back(6);
        return v;
        };
    auto vec2 = func1();
    cout << vec.size() << endl << vec2.size() << endl;//vec已被架空
    //unique_ptr独占指针
    unique_ptr<int>ptr(new int(21));
    auto func2 = [ptr = move(ptr)] {
        cout << *ptr << endl;
        };
    if (ptr) {
        cout << "not null" << endl;
    }
    else {
        cout << "null" << endl;
    }
    // 在func2没执行之前就显示ptr的指针为空，说明ptr变化为nullptr发生在func2函数构造的时候
    func2();
}

int main() {
    MoveCapture();
}