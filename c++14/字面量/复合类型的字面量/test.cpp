#include<iostream>
using namespace std;

class MyColor {
private:
    uint8_t r, g, b;
public:
    MyColor(uint8_t R, uint8_t G, uint8_t B) :r(R), g(G), b(B) {};

    void print() {
        cout << "R : " << (int)r << " G : " << (int)g << " B : " << (int)b << endl;
    }
};
//整形读取颜色
MyColor operator"" _read1(unsigned long long data) {
    return MyColor{
        data >> 16 & 0xff,data >> 8 & 0xff,data & 0xff
    };
}
//字符串读取颜色
MyColor operator"" _read2(const char* str, size_t len) {
    int r, g, b;
    sscanf(str, "%d,%d,%d", &r, &g, &b);//格式化扫描赋值
    return MyColor{ (uint8_t)r,(uint8_t)g,(uint8_t)b };
}

int main() {
    MyColor get_from_string = "255,100,100"_read2;
    get_from_string.print();

    MyColor get_from_num = 0x677891_read1;
    get_from_num.print();
}