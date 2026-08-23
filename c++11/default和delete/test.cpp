#include <iostream>
using namespace std;
class test
{
public:
    //令构造函数或析构函数等于default可使该函数变为默认函数
    test();
    test(const test &t) = default;
    test(test &&t) = default;
    test &operator=(test &&t) = default;
    ~test() = default;
    //令类内函数等于delete可使该函数被禁止使用（同样可以类外声明）
    test &operator=(const test &t) = delete;
    void print(char c) = delete;
    void print(int a){
        cout << a << endl;
    }
};
//类外也可声明
test::test() = default;

int main()
{
    test t1, t2;
    //t1 = t2非法
    t1.print(1);
    //t2.print('a')非法
}