//能在编译期算 → 能用 constexpr 就用；
//数值运行时才确定 → 老老实实只用const；
#include<iostream>
using namespace std;
int main() {
    constexpr double Pi = 3.14159;
    cout << Pi << endl;
}