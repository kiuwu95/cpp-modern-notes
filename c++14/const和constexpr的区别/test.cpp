#include<iostream>
using namespace std;

int get_input() {
    int input;
    cin >> input;
    return input;
}

int main() {
    //const和constexpr初始化时机不同

    //const的初始化时机可能是在编译时，也可能是在运行时
    const int num1 = 100;//编译时
    const int* ptr = new int(num1);//运行时，只有运行时才能创建内存
    int* const ptr2 = new int(get_input());//运行时，只有运行时才能接受用户的输入
    //constexpr的初始化时机只在编译时
    constexpr int num2 = 22;//编译时
    constexpr int* ptr = new int(22);//报错，不能在运行时
    constexpr int* ptr = new int(get_input());//报错，只有在运行时才能接受用户输入
}