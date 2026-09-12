#include<iostream>
#include<functional>
using namespace std;

struct is_equal_six {
    int value;
    //explicitd的添加是为了防止隐式转换而导致的不必要的错误❌
    explicit operator bool() const { return value == 6; };//显示类型转换符 面向对象编程好像学过？
};
struct is_equal_five {
    int value;
    operator bool() const { return value == 5; };
};
int main() {
    is_equal_five ies2{ 5 };
    int a = ies2;//如果没有explicit，就会发生隐式转换，出现了a=1的意外
    cout << a << endl;

    is_equal_six ies{ 6 };
    //对于bool类型的显示类型转换符，如果加了explicit，则不会发生隐式转换，就不会出现上面a=1的情况，反而会报错。只有在逻辑上下文中才能使用，如下：
    if (ies) {
        cout << "ies的value为6" << endl;
    }
}