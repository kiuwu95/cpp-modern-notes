#include<iostream>
using namespace std;

//强枚举类型默认的底层类型为 int,但也可以显示地指定其他类型，比如：
enum class Colors :char { Red, Blue, Green };

enum class Fruits :int { Apple, Banana, Lemon };
//强枚举类型可以避免因两个不同的枚举出现同一个名字相同的对象而导致的枚举混淆。
//强枚举类型可以通过声明枚举域来判断该同名对象是属于哪个枚举
enum class China { Shanghai, Dongjing, Beijing, Nanjing, };
enum class Japan :char { Dongjing, Daban, Hengbin, Fudao };

int main() {
    //使用时必须作强制类型转换，强枚举类型不会自动作隐式类型转换
    int num = (int)Fruits::Banana;//1
    if (num == 1)cout << "It's a banana!" << endl;

    char c = (char)Colors::Blue;
    c += 50;
    cout << c << endl;//'3'

    Colors c1 = Colors::Blue;
    Fruits f1 = Fruits::Apple;
}