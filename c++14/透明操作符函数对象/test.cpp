#include<iostream>
using namespace std;

template<class T>
struct Plus {
    T operator()(const T& a, const T& b) {
        return a + b;
    }
};
template<>
struct Plus<void> {
    template<class T1, class T2>
    decltype(auto) operator()(T1&& a, T2&& b) {
        return forward<T1>(a) + forward<T2>(b);
    }
};

int main() {
    Plus<void>p1;
    cout << p1(3.14, 2) << endl;
}