#include<iostream>
#include<utility>
using namespace std;

void test(int& a) {
    cout << "左值的引用" << endl;
}
void test(int&& a) {
    cout << "右值的引用" << endl;
}
//forward须搭配万能模板引用，左值可保留左值特性，右值可保留右值特性。
template<typename T>
void l_or_r(T&& num) {
    test(forward<T>(num));
}

int main() {
    int a = 10;
    int& b = a;
    l_or_r(a);
    l_or_r(b);
    int&& c = move(a);
    l_or_r(c);
    //move会将左值转换为右值，右值也会保留右值特性。本质上是数据仍在内存的那个位置上，只不过宿主被架空罢了。
    l_or_r(move(a));
    test(move(a));
}