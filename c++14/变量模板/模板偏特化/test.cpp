//变量模板特化优先级：全特化 > 偏特化 > 主模板
#include<iostream>
using namespace std;
//1.判断两个类型是否相同
//主模板
template<class T1, class T2>
constexpr bool type_is_same = false;
//偏特化
template<class T>
constexpr bool type_is_same < T, T > = true;
//解决const T和T比较的问题
template<class T>
constexpr bool type_is_same<const T, T> = type_is_same<T, T>;

template<class T>
constexpr bool type_is_same < T, const T > = type_is_same<T, T>;
//全特化
template<>
constexpr bool type_is_same<const double, const double> = true;

template<>
constexpr bool type_is_same<const int, const int> = true;
//2.判断类型是否为数组类型
//主模板
template<typename T>
constexpr bool is_Array = false;
//偏特化
template<typename T>
constexpr bool is_Array<T[]> = true;      // 未知大小数组：T[]

template<typename T, size_t N>//N不是变量，只是用来识别数组的大小
constexpr bool is_Array<T[N]> = true;     // 已知大小数组：T[N]

int main() {
    cout << type_is_same<int, int> << endl
        << type_is_same<const int, int> << endl
        << type_is_same<double, int> << endl;

    int arr1[] = { 1,2,3 }, arr2[2] = { 1,2 };
    cout << is_Array<decltype(arr1)> << endl << is_Array<decltype(arr2)> << endl;
}