// 继承的作用：
// 1）在已有的类基础上添加新功能；
// 2）可以给类添加新数据；
// 3）可以修改类方法的行为；

// 继承之后的效果
// 1）派生类对象存储了基类的数据成员
// 2）派生类对象可以使用基类的方法

// 派生类不能直接访问基类的私有成员，而是必须通过基类的方法访问；

// 创建派生类对象时，程序首先创建基类对象，这意味着基类对象应当在程序进入派生类的构造函数之前被创建，c++ 通过初始化列表实现；
// 必须首先在初始化列表中调用基类的构造函数，如果不调用，则程序将调用默认构造函数；
// 除非调用默认构造函数，否则必须在初始化列表中显示调用正确的基类构造函数；

// 继承之后：
// 1）派生类对象可以直接使用父类的所有 public 成员；
// 2）在派生类对象内部可以使用除私有成员外所有成员；
// 3）基类指针可以直接指向子类对象，基类引用可以直接引用子类对象-->主要应用在使用基类指针或者引用做函数参数既可以接受基类也可以接受派生类对象；
// 4）基类指针和引用只能调用基类方法（基类中有的方法），而不能调用派生类中特有的方法；
// 5）可以直接使用派生类对象初始化基类对象，调用的是基类的拷贝构造函数或者赋值运算符；


