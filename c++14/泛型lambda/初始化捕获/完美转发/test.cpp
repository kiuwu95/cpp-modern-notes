#include<iostream>
#include<functional>
using namespace std;

template<class T>
void forward_and_capture(T&& data) {
    auto func = [cap = forward<T>(data)]() {
        if (is_same<T, int>::value) {
            cout << "int";
        }
        else if (is_same<T, int&>::value) {
            cout << "int&";
        }
        else cout << "int&&";
        cout << endl;
        };

    func();
}

int main() {
    int test = 1;
    int& test2 = test;
    forward_and_capture(test);
    forward_and_capture(test2);
    forward_and_capture(1);
    forward_and_capture(move(test));
}