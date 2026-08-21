#include<iostream>
using namespace std;
void func(initializer_list<int> ls) {
    for (auto it = ls.begin();it != ls.end();it++) {
        cout << *it << " ";
    }
}

int main() {
    func({ 1,2,3,4,5 });
}