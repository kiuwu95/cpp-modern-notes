#include<iostream>
using namespace std;
class Base {
public:
    int m_A, m_B;
    //利用初始化列表直接赋值效率更高
    Base(int A, int B) :m_A(A), m_B(B) {};
};
