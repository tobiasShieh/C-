// 静态转换（static_cast）
// static_cast 只能用于良性转换，这样的转换风险较低，一般不会发生什么意外，例如：
//      1）原有的自动类型转换，例如 short 转 int、int 转 double、double 转 int（安全需要程序员维护）、向上转型、向下转换（不安全）等；
//      2）void 指针和具体类型指针之间的转换，例如 void * 转 int *、char * 转 void *等，这个安全需要程序员维护；
//      3）有转换构造函数或者类型转换函数的类与其它类型之间的转换，例如 double 转 Complex（调用转换构造函数）、Complex 转 double（调用类型转换函数）。

// 需要注意的是，static_cast 不能用于无关类型之间的转换，因为这些转换都是有风险的，例如：
//      1）两个具体类型指针之间的转换，例如 int * 转 double *、Student * 转 int *等。不同类型的数据存储格式不一样，长度也不一样，用 A 类型的指针指
//      向 B 类型的数据后，会按照 A 类型的方式来处理数据：如果是读取操作，可能会得到一堆没有意义的值；如果是写入操作，可能会使 B 类型的数据遭到破坏，
//      当再次以 B 类型的方式读取数据时会得到一堆没有意义的值。
//      2）int 和指针之间的转换。将一个具体的地址赋值给指针变量是常非危险的，因为该地址上的内存可能没有分配，也可能没有读写权限，恰好是可用内存反而是
//      小概率事件。
//      3）static_cast 也不能用来去掉表达式的 const 修饰和 volatile 修饰。换句话说，不能将 const/volatile 类型转换为非 const/volatile 类型。这一
//      点可以通过 const_cast 来实现。
//      4）c++ 中可以实现隐式的向上转型，同样可以使用 static_cast 实现向上转换，但有一个例外就是 static_cast 也可以实现向下转换，但不能使用隐式转换
//      来完成，需要注意的是，这种转换方法没有办法判断当前指针到底是指向父类还是指向子类，比如一个父类指针可以转化为派生类指针，但是这个父类指针指向的
//      是父类对象，像这样的问题 static_cast 是检查不出来的，只有借助 dynamic_cast 才能判断出指针到底指向父类还是子类对象。

// static_cast 是“静态转换”的意思，也就是在编译期间转换，转换失败的话会抛出一个编译错误。

#include <iostream>
#include <cstdlib>
using namespace std;

class Complex{
public:
    Complex(double real = 0.0, double imag = 0.0): m_real(real), m_imag(imag){ }
public:
    // 类型转换函数
    operator double() const { return m_real; }  
private:
    double m_real;
    double m_imag;
};
void test01()
{
    //下面是正确的用法
    int m = 100;
    Complex c(12.5, 23.8);
    // 宽转换，没有信息丢失
    long n = static_cast<long>(m);  
    // 窄转换，可能会丢失信息
    char ch = static_cast<char>(m);  
    // 将 void 指针转换为具体类型指针
    int *p1 = static_cast<int*>( malloc(10 * sizeof(int)) );  
    // 将具体类型指针，转换为void指针
    void *p2 = static_cast<void*>(p1);  
    // 调用类型转换函数
    double real = static_cast<double>(c);  
   
    //下面的用法是错误的
    // 不能在两个具体类型的指针之间进行转换
    // float *p3 = static_cast<float*>(p1);  
    // 不能将整数转换为指针类型
    // p3 = static_cast<float*>(0X2DF9);  
}

class Base{};
class Child : public Base {};
class Other {};
void test02()
{
    Base* pB = nullptr;
    Child* pC = nullptr;
    Other* pO = nullptr;
    // 向上转型，也可以通过隐式转换完成
    pB = static_cast<Base*>(pC);
    // 例外之处，可以完成向下转换，但是不确定正确
    pC = static_cast<Child*>(pB);
    // 两个不相关的类型不能转换
    // pO = static_cast<Base*>(pB);
}

int main(){
    test01();

    return 0;
}