#include<iostream>
using namespace std;

template<class T>
T get_value = static_cast<T>(3.1415926535L);
int v1 = get_value<int>;
float v2 = get_value<float>;
double v3 = get_value<double>;
int main() {
    cout << v1 << endl << v2 << endl << v3 << endl;
}