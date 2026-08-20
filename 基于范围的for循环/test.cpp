#include<iostream>
#include<vector>
using namespace std;
int main() {
    vector<int> v1 = { 1,2,3,4,5 };
    //基于范围的for循环效率更加高点
    for (auto it : v1) {
        cout << it << endl;
    }
}