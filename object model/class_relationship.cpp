// 类与类之间的关系
// 1）继承（Inheritance） is-a
// 2）复合（Composition）  has-a
// 3）委托（Delegation/Composition by reference）   类的定义中包含其它类的引用或指针

// 复合关系中的构造和析构
// 1）构造必须由内而外，这样结构才稳定，比如 Container has-a Component，此时再构造 Container 时，必须先调用 Component 的构造函数。
// Container::Container(...) : Component(...) { ... }
// 注意调用默认 ctor 只是编译器的默认做法，大致顺序是：在构造本身前，必须先将其所包含的类进行构造，如果程序提供了默认 ctor，并且没有指定调用 ctor 的
// 其它版本，则编译器会自动帮我们调用其默认无参 ctor，不需要手动添加代码。当然我们也可以指定构造方法，所以我们需要在初始化列表添加构造代码。
// 2）析构必须由外向内，这样才不会发生“坍塌”，比如在析构 Container 时，会先调用 Container 析构函数，再调用 Component 析构函数。
// Container::~Container() { ... ~Component() }

// 委托关系
// 1）委托关系就是本类中含有其它类的引用或者指针，和复合不同的是，委托关系中两个类的周期并不同步（在复合中周期同步）；

// 继承关系中的构造与析构
// 1）构造必须由内向外，向调用父类的构造函数，在调用子类的构造函数；
// 2）析构必须由外向内，先调用子类的析构函数，在调用父类的析构函数；
// 析构的这种执行顺序必须由“父类的析构必须为虚函数”支撑才能实现，当你在设计一个类的时候如果是基类，那么请将析构函数设置为虚析构函数；

#include <iostream>
using namespace std;

class Base
{
public:
    Base() { cout << "Base()" << endl; }
    virtual ~Base() { cout << "~Base()" << endl; }
};

class Other
{
public:
    Other() { cout << "Other()" << endl; }
    ~Other() { cout << "~Other()" << endl; }
};

class Son1 : public Base
{
public:
    Son1() { cout << "Son1()" << endl; }
    ~Son1() { cout << "~Son1()" << endl; }
private:
    Other m_o;
};

void test01()
{
    {
        Base *pB = new Son1();
        delete pB;
    }
}

#include <iostream>
using namespace std;

int main()
{
    test01();
    /*
        Base()
        Other()
        Son1()
        ~Son1()
        ~Other()
        ~Base()
    */

    cin.get();
}