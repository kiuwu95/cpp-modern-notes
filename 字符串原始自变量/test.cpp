#include<iostream>
#include<string>
using namespace std;
int main() {
    //在 C++11 中添加了定义原始字符串的字面量，定义方式为：R “xxxx(原始字符串)xxxx” 其中 () 两边的字符串可以省略,如果不省略则两边字符串必须一样。原始字符串量 R 可以直接表示字符串的实际含义，而不需要额外对字符串做转译或连接等操作。
    //比如：编程过程中，使用的字符串中常带有一些特殊字符，对于这些字符往往要做专门的处理，使用了原始字符串量就可以轻松的解决这个问题了。
    string s1 = R"(D:\pxn\PXNSimRacing)";
    string s2 = "D:\\pxn\\PXNSimRacing";

    //string s3 = "D:\pxn\PXNSimRacing",'\'与'p'组成了同一个字符'\p'会导致出错
    cout << s1 << endl << s2 << endl;
}