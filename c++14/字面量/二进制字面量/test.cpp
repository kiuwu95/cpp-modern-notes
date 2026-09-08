#include<iostream>
using namespace std;
//权限等级
enum right {
    right1 = 0b100,
    right2 = 0b010,
    right3 = 0b001,
};

int main() {
    //二进制字面量，在“0b”后面加上二进制数即可获得一个二进制数字
    int binary1 = 0b10001;
    cout << binary1 << endl;
    //在二进制字面量后面加上类型缩写可指定这个二进制数的类型
    auto binary2 = 0b10001ul;//unsigned long类型
    auto binary3 = 0b11001l;//long类型
    //分隔符,具有分隔数字便于读数的功能
    int num1 = 114'514;
    auto binary4 = 0b111'000'111ull;//unsigned long long类型
    cout << num1 << endl << binary4 << endl;

    int person1 = 0b111, person2 = 0b100;
    if (person1 & right3) {//与运算
        cout << "person1有权" << endl;
    }
    else {
        cout << "person1无权" << endl;
    }

    if (person2 & right2) {
        cout << "person2有权" << endl;
    }
    else {
        cout << "person2无权" << endl;
    }
}