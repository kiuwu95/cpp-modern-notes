#include<iostream>
#include<string>
#include<memory>
using namespace std;
class person {
private:
    int m_id;
    string m_name;
public:
    person() = default;
    person(int id, string name) :m_id(id), m_name(name) {};
};
//掌握make_unique的初始化方法即可
int main() {
    unique_ptr<int>ptr1 = make_unique<int>(1);
    unique_ptr<person>ptr2 = make_unique<person>(1, "Alice"s);
    //unique_ptr初始化数组，一定要加[]，变量填的是数组的大小，数组内的所有元素都默认初始化为int()或int{}
    unique_ptr<int[]>ptr3 = make_unique<int[]>(5);
    unique_ptr<person[]>ptr4 = make_unique<person[]>(3);
}