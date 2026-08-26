#include<iostream>
#include<assert.h>
using namespace std;
//assert的作用：当参数发生异常的时候程序退出，从而避免程序陷入逻辑的混乱，多在调试的时候使用。
int main() {
    assert(false);
    cout << "hello,world" << endl;
}