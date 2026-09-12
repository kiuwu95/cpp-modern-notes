#include<iostream>
#include<map>
#include<string>
#include<functional>
using namespace std;

template<class T>
struct Plus {
    T operator()(const T& a, const T& b) {
        return a + b;
    }
};
template<>
struct Plus<void> {
    using is_transparent = void;//标签，表示支持异构处理。若以后自己设计透明函数对象则必须打上这个标签
    template<class T1, class T2>
    decltype(auto) operator()(T1&& a, T2&& b) {
        return forward<T1>(a) + forward<T2>(b);
    }
};

void example1() {
    //注意：显式指定比较器必须为less<>才能使用透明，这样在find时对于"hello"这一const char*类型的值不需要隐式转换为string类型再进行比较，节省了堆空间，提高效率
    map<string, int, less<>>m = { { "hello",1 } };
    map<string, int>::iterator it = m.find("hello");
    //若显示指定比较器不为less<>则会默认为less<std::string>，则无法采用透明，find"hello"时就会隐式转换为string类型再进行find
    map<string, int>m1 = { { "hello",1 } };
    auto ite = m1.find("hello");
}

//对此，我将写一个近似于less的底层代码 
struct Myless {
    using is_transparent = void;
    template<class T1, class T2>
    auto operator()(T1&& num1, T2&& num2) ->decltype(forward<T1>(num1) < forward<T2>(num2)) {
        return forward<T1>(num1) < forward<T2>(num2);
    }
};
int main() {
    Plus<void>p1;
    cout << p1(3.14, 2) << endl;//不需要再加<类型1,类型2>，因为operator()是函数模板，会自动推导参数类型

    Myless ml;
    cout << ml(1, 2) << endl << ml(3.14, 2) << endl;
}