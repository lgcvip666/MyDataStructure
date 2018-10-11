/* 指针也可以指向一个结构体，定义的形式一般为：
struct 结构体名 *变量名;

获取结构体成员:
通过结构体指针可以获取结构体成员，一般形式为：
(*pointer).memberName
或者：
pointer->memberName
第一种写法中，.的优先级高于*，(*pointer)两边的括号不能少。如果去掉括号写作*pointer.memberName，那么就等效于*(pointer.numberName)，这样意义就完全不对了。

第二种写法中，->是一个新的运算符，习惯称它为“箭头”，有了它，可以通过结构体指针直接取得结构体成员；这也是->在C语言中的唯一用途。

上面的两种写法是等效的，我们通常采用后面的写法，这样更加直观。 */

//下面是一个定义结构体指针的实例：
struct stu{
    char *name; //姓名
    int num; //学号
    int age; //年龄
    char group; //所在小组
    float score; //成绩
} stu1 = { "Tom", 12, 18, 'A', 136.5 };

//也可以在定义结构体的同时定义结构体指针：
struct stu{
    char *name;                //姓名
    int num;                   //学号
    int age;                   //年龄
    char group;                //所在小组
    float score;               //成绩
} stu1 = { "Tom", 12, 18, 'A', 136.5 }, *pstu = &stu1;

/* 注意，结构体变量名和数组名不同，数组名在表达式中会被转换为数组指针，
而结构体变量名不会，无论在任何表达式中它表示的都是整个集合本身，要想取得结构体变量的地址，
必须在前面加&，所以给 pstu 赋值只能写作：
struct stu *pstu = &stu1;
而不能写作：
struct stu *pstu = stu1; */
