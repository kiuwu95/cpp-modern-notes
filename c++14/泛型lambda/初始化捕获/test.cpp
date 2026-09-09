#include<iostream>
using namespace std;

void ValueCapture() {
    int num = 211;
    float num2 = 3.14;
    auto func1 = [data = num, data2 = num2](const auto& t) {
        //data通过拷贝num存于lambda函数的类中，并且它是只读的，不能修改
        return data + t + data2;
        };
}
int main() {

}