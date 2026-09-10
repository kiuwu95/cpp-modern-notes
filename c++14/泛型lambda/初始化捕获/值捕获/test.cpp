#include<iostream>
using namespace std;
//值捕获
void ValueCapture() {
    int num = 211;
    float num2 = 3.14;
    auto func1 = [data = num, data2 = num2](const auto& t) {
        //data通过拷贝num存于lambda函数的类中，并且它在lambda函数中是只读的，不能修改
        //如果需要修改则在函数后面加上mutable
        return data + t + data2;
        };
    func1(3);
}
int main() {

}