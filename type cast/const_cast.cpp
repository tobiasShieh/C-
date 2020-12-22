// const_cast in C++

// NOTE:
// The expression const_cast<T>(v) can be used to change the const or volatile qualifiers of pointers or references.
// Where T must be a pointer, reference, or pointer-to-number type.
#include <iostream>
using namespace std;

// 1. When the actual referred object/variable is not const.
// 当可能发生修改时，被指的对象或者变量本身必须是非 const
void test01()
{
    const int a1 = 10;
    const int *b1 = &a1;
    // int temp = a1;
    //const int *b1 = &temp;
    int *d1 = const_cast<int*>(b1);
    *d1 = 15;   // Invalid and Undefined Behavior!

    cout << "a1 = " << a1 << endl;  // 10
    // cout << "a1 = " << 10 << endl;
    cout << "*d1" << *d1 << endl;   // 15

    int a2 = 20;
    const int *b2 = &a2;
    int *d2 = const_cast<int*>(b2);
    *d2 = 30;   // Valid Code!

    cout << "a2 = " << a2 << endl;  // 30
}

// 2. When we need to call some 3'rd party library where it is taking variable/object as non-const but not changing that.
// 当我们想使用第三方库只读时（不修改数据），库函数提供非 const 形参列表，如果此时实参为 const，则不能直接传递，会产生 error，这时就
// 需要使用 const_cast 进行转换

void thirdPartyLibrary(int *x)
{
    int k = 10;
    cout << k + *(x);   // 30
}
void test02()
{
    const int x = 20;
    const int *px = &x;
    // thirdParityLibriry(px);  invalid conversion from "const int*" to "int*"
    thirdPartyLibrary(const_cast<int*>(px));
}


int main()
{
    // test01();
    test02();

    cin.get();
    return 0;
}

/*
总结：
1）const_cast的用途：
    用于除去类型中的 const
2）const_cast的使用场景：
    修改。必须要求原始对象或变量为非 const；
    访问。调用第三方库，必须保证不发生修改操作；
*/