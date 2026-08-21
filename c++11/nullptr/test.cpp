#include<iostream>
using namespace std;
int main() {
    //nullptr会随着指针类型分配对应的空指针类型，例如p就被分配为了int*类型的空指针，p1就被分配为了char*类型的空指针，p2也是同样如此
    //而c++中对于NULL的声明为0
    cout << NULL << endl;
    int* p = nullptr;
    char* p1 = nullptr;
    double* p2 = nullptr;
}