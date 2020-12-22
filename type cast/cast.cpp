/*
    1）类型转换（cast）是将一种数据类型转换成另一种数据类型。例如，将一个整型赋值给一个浮点类型的变量，编译器会暗地里将其转换成浮点类型。
    2）转换是非常有用的，但是它也会带来一些问题，比如在转换指针时，我们很可能将其转换成一个比它更大的类型，但这可能会破坏其它的数据。
    3）应该小心类型转换，因为转换相当于对编译器说：忘记类型检查，把它看做其他类型。
    4）一般情况下，尽量少的去使用类据转换，除非用来解决非常特殊的间题。
    5）任何一个程序，如果出现了大量的类型转换都是值得怀疑的。
    6）隐式类型转换是安全的，显式类型转换是有风险的，C 语言之所以增加强制类型转换的语法，就是为了强调风险，让程序员意识到自己在做什么。但是，这种强调
风险的方式还是比较粗放，粒度比较大，它并没有表明存在什么风险，风险程度如何。再者，C 风格的强制类型转换统一使用 ()，而()在代码中随处可见，所以也不利于
使用文本检索工具定位关键代码。为了使潜在风险更加细化，使问题追溯更加方便，使书写格式更加规范，C++ 对类型转换进行了分类，并新增了四个关键字来予以支持，
它们分别是：
    static_cast     用于良性转换，一般不会导致意外发生，风险很低。
    const_cast	    用于 const 与非 const、volatile 与非 volatile 之间的转换。
    reinterpret_cast	高度危险的转换，这种转换仅仅是对二进制位的重新解释，不会借助已有的转换规则对数据进行调整，但是可以实现最灵活的 C++ 类型转换。
    dynamic_cast	借助 RTTI，用于类型安全的向下转型（Downcasting）。

*/