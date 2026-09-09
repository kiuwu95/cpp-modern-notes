#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void func() {
    auto plus = [](const auto& x, const auto& y) {
        return x + y;
        };
    cout << plus(1, 1) << endl;

    auto is_equal = [](const auto& x, const auto& y) {
        return x == y;
        };
    cout << is_equal(2, 3) << endl;

    auto find_func = [](const auto& t, const auto& data) {
        return find(t.begin(), t.end(), data) != t.end();
        };
    vector<int>vec = { 1,2,3,4,5 };
    cout << find_func(vec, 3) << endl;
}

int main() {
    func();
}