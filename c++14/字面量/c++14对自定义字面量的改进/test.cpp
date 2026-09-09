#include<iostream>
#include<string>
#include<chrono>
#include<complex>
using namespace std;
//若要调用系统库自带的字面量则必须使用下列命名空间，或者直接using namespace std;
using namespace std::complex_literals;
using namespace std::chrono_literals;
using namespace std::string_literals;

int main() {
    //chrono系统库自带的时间字面量
    auto t1 = 1s;
    auto t2 = 1ms;
    auto t3 = 1us;
    auto t4 = 1h;
    auto t5 = 1min;

    //string系统库自带的字符串字面量
    auto s1 = "world";//s1为const char*类型
    auto s2 = "world"s;//s2为string类型，等价于string(s1)
    auto s3 = u"world"s;//u16string类型，编码为UTF-16
    auto s4 = U"world"s;//u32string类型，编码为UTF-32
    auto s5 = L"world"s;//wstring类型
    //complex系统库自带的复数字面量
    auto n1 = 1.0 + 2i;//double
    auto n2 = 4.5f + 1.4if;//float
    auto n3 = 5.1l + 3.2il;//long doublea
}