#include<iostream>
#include<string>
using namespace std;

class base {
public:
    string str;
    int m_num;

    void print() {
        cout << str << endl << m_num << endl;
    }
    void set_Str(const string& s) {
        str = s;
    }
    void set_num(const int& n) {
        m_num = n;
    }
};
//只要联合体里面有一个成员拥有非平凡构造/析构，联合体本身默认构造函数、析构函数会被编译器删除，你必须手动管理生命周期，要用 placement new 构造，手动调用析构函数！
union test {
    string s;
    int num;
    base obj;
    //定位放置 new的方式将构造出的对象地址定位到了联合体的成员string s的地址上
    test() {
        new(&s) string;
    }
    ~test() {};
};

int main() {
    test t;
    t.s = "kskbl";
    t.num = 1;

    t.obj.set_Str("zdjd");//"kskbl"->"zdjd"
    t.obj.set_num(2);//1->2
    t.obj.print();
}