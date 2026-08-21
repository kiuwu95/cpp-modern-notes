#include<iostream>
#include<memory>
#include<functional>
using namespace std;

int main() {
    //构造函数初始化
    unique_ptr<int>ptr1(new int(10));
    //unique_ptr<int>ptr2 = ptr1错误，因为独占指针不允许其他的智能指针共享其内部的指针
    //make_unique初始化
    unique_ptr<int>ptr2 = make_unique<int>(20);
    //使用reset()函数重新初始化
    ptr2.reset(new int(30));
    //移动构造初始化
    unique_ptr<int>ptr3 = move(ptr1);//ptr1此时指向空,相当于ptr3取代了ptr1的位置
    //使用get()函数获取原始指针
    int* ptr = ptr3.get();
    cout << ptr << endl << ptr3 << endl;//地址相同

    //unique_ptr的删除器
    //无捕获的lambda函数删除器
    using delete_func = void(*)(int* ptr);//声明函数指针
    unique_ptr<int, delete_func>ptr4(new int(10), [](int* ptr) {delete ptr;});
    //有捕获的lambda删除器
    unique_ptr<int, function<void(int* ptr)>>ptr5(new int(20), [&](int* ptr) {delete ptr;});
    //C++11对于管理数组的独占指针可以使其在析构时可以自动释放，共享指针不可以。
    //但共享指针在C++17后也可以自动释放
    unique_ptr<int[]>ptr6;
}