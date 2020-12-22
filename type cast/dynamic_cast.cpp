// dynamic_cast in c++

// 运行时类型识别
// 运行时类型信息是由操作符：dynamic_cast 指定。
// dynamic_cast 用于向下转型，即将基类的指针或引用动态转型为派生类指针或引用。
//  （1）static_cast：静态转型（向下转型）。不管父类指针是否真的指向子类对象，一律把指针转型后返回。转型不保证安全。
//  （2）dynamic_cast：动态转型操作符。把父类指针转型成子类指针，如果转型成功（即父类指针的确指向子类对象），返回子类对象地址；如果转型失败，返回NULL。即转型是安全的。

// 面试问题：如何判断一个父类指针是否指向子类对象？
// 回答：使用 dynamic_cast 进行转换，然后对结果进行判断，如果结果为 null，则说明不是指向子类的指针；如果非 null，则说明是指向子类的指针。

// 使用格式：dynamic_cast<子类指针/引用>（父类指针/引用），用来检测父类指针/引用是否可以转换成子类指针/引用。

// 注意：dynamic_cast转换的时候必须有virtual函数支持。

// 面试提问：为何使用dynamic_cast转换类指针时，需要虚函数呢?
// 回答：    Dynamic_cast 转换是在运行时进行转换，运行时转换就需要知道类对象的信息（继承关系等）。那么如何在运行时获取到这个信息——虚函数表。C++ 对象
// 模型中，对象实例最前面的就是虚函数表指针，通过这个指针可以获取到该类对象的所有虚函数，包括父类的。因为派生类会继承基类的虚函数表，所以通过这个虚函数
// 表，我们就可以知道该类对象的父类，在转换的时候就可以用来判断对象有无继承关系。所以虚函数对于正确的基类指针转换为子类指针是非常重要的。

// 面试提问：对于 ABC 结构，即 B 类 继承 A 类，C 类继承 B 类，此时当将一个指向 C 类对象的 A 指针转化为 B 指针，可以成功么？
// 回答：这种转化是可以完成的，虽然最后转化的不是 C 类指针，但是也可以转化为 B 类指针，和 A 类指针相比，B 类指针更接近与 C 类对象。这可能和虚函数表
// 有关，在检查的时候发现相对于 B 类，A 类就是父类对象。

// 面试提问：对于 A(B)C 结构，即 C 类同时继承 A 类和 B 类，A 类指针指向了 C 类对象，那么如何转换为 B 类指针指向 C 类对象？
// 回答：使用 dynamic_cast 可以直接实现转换，如果 A 类指针指向的真的是 C 类对象的时候，因为在运行过程中，根据虚函数表，可以看到继承关系，便会进行转
// 换，但是如果直接使用 static_cast 进行转换，由于 B 类和 A 类类型不同，因此编译通不过，可以先使用 static_cast 进行下行转换，然后再进行向上转换。

#include <iostream>
using namespace std;

class Base
{
public:
    virtual void print() const { cout << "Base.\n"; }

    void outB() const { cout << "Out Base.\n"; }
};
class D1 : public Base
{
public:
    void print() const { cout << "D1.\n"; }

    void outD1() const { cout << "Out D1.\n"; }
};
class D2 : public Base
{
public:
    void print() const { cout << "D2.\n"; }

    void outD2() const { cout << "Out D2.\n"; }
};
void test01()
{
    D1 d1; 
    D2 d2;
    const D1* p1;
    const D2* p2;
    // 基类指针数组
    Base* p[2] = {&d1, &d2};
    for (int count = 0; count < 2; ++count)
    {
        if ((p1 = dynamic_cast<D1*>(p[count])))
        {
            p1->print();
            p1->outD1();
        }
        else if ((p2 = dynamic_cast<D2*>(p[count])))
        {
            p2->print();
            p2->outD2();
        }
    }
}

// 一个实际应用: 学生和教师都是人，使用一个 Person 保存所有 Student 和 Teacher 的信息，对于这个 Person 数组
// 我们如何选取所有的 Student 或者 Teacher 进行处理。
class Person
{
public:
    virtual void print() const { cout << "Person\n"; }
};
class Student : public Person
{
public:
    void print() const { cout << "Student\n"; }
};
class Teacher : public Person
{
public:
    void print() const { cout << "Teacher\n"; }
};
void test02()
{
    Student std1;
    Teacher tec1;
    Student std2;
    Teacher tec2;
    Student std3;

    const Student* pStd = nullptr;

    Person* p[5] = {&std1, &tec1, &std2, &tec2, &std3};
    for (int i = 0; i < 5; ++i)
    {
        if ((pStd = dynamic_cast<Student*>(p[i])))
        {
            pStd->print();
        }
    }
}

// 测试 A->B->C 结构
class A
{
public:
    virtual void show() { cout << "A" << endl; }
};
class B : public A
{
public:
    void show() { cout << "B" << endl; }
};
class C : public B
{
public:
    void show() { cout << "C" << endl; }
};
void test03()
{
    A *pA = new C();
    B *pB = nullptr;
    C *pC = nullptr;

    if ((pB = dynamic_cast<B*>(pA))) 
        cout << "B" << endl;

    if ((pC = dynamic_cast<C*>(pA)))
        cout << "A" << endl;
}


// 多继承的向下转型
class Base1{
	virtual void f1(){}
};
class Base2{
	virtual void f2(){}
};
class Derived: public Base1, public Base2{
	void f1(){}
	void f2(){}
};
void test04()
{
    Base1 *pD = new Derived;
    Derived *pD1  = dynamic_cast<Derived*>(pD);  //正确，原因和前面类似
    Derived *pD2  = static_cast<Derived*>(pD);  //正确，原因和前面类似
    Base2 *pB1  = dynamic_cast<Base2*>(pD);    //语句1  right
    // Base2 *pB2  = static_cast<Base2*>(pD);    语句2 wrong
    Base2 *pB2 = static_cast<Base2*>(static_cast<Derived*>(pD));

    /*
        此时的语句 1,将 pD 的类型转化为 Base2*，即：使得 pB1 指向 Drived 对象的 Base2 子对象，为什么能达到这种转化？因为 dynamic_cast 是运行时才决
        定真正的类型，在运行时发现虽然此时 pD 的类型是 Base1*，但是实际指向的是Derived类型的对象，那么就可以通过调整指针，来达到 pB1 指向 Derived 
        对象的 Base2 子对象的目的；
        但是语句 2 就不行了，其使用的是 static_cast，它不涉及运行时的类型检查，对于它来讲，pD 的类型是 Base1*，Base1 和 Base2 没有任何关系，那就会
        出现编译错误了。error: invalid static_cast from type ‘Base1*’ to type ‘Base2*’
        总结：对于多种继承，如果 pD 真的是指向 Derived，使用 static_cast 和 dynamic_cast 都可以转化为 Derived，但是如果要转化为 Base1 的兄弟类
        Base2，必须使用 dynamic_cast，使用 static_cast 不能通过编译。
    */
}

int main()
{
    // test01();
    // test02();
    // test03();
    test04();

    cin.get();
    return 0;
}


