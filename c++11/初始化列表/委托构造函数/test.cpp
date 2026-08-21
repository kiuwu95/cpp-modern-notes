#include<iostream>
using namespace std;
class Num {
public:
    int m_num1, m_num2, m_num3;

    //链式结构，层层递进
    Num() {}

    Num(int num1) {
        m_num1 = num1;
    }

    Num(int num1, int num2) :Num(num1) {
        m_num2 = num2;
    }

    Num(int num1, int num2, int num3) :Num(num1, num2) {
        m_num3 = num3;
    }
};