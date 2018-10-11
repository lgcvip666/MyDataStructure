#include	<stdio.h>
#include	<stdlib.h>
#include    <stdarg.h>
#include    <string.h>

int demo(char*, ...);                           //声明变参函数；

int main (int argc, char **argv)
{
    demo("Demo","This","is","a","demo!","");    //调用变参函数；
    return EXIT_SUCCESS;
}



int demo (char* msg, ...)                       //定义变参函数；
{
    va_list argp;                               //参数指针；
    int num = 0;
    char* para;

    va_start(argp,msg);                         //指针指向 msg 的下一个参数；
    while(1)
    {
        para = va_arg(argp, char*);             //获取变参列表里 char* 类型的参数值；
        if(strcmp(para, "")==0)
            break;
        printf("parameter %d is : %s\n", num, para);
        num++;
    }
    va_end(argp);
    return 0;
}

/* 
函数参数的传递原理：
函数参数是以数据结构:栈的形式存取,从右至左入栈。
首先是参数的内存存放格式：参数存放在内存的堆栈段中，
在执行函数的时候，从最后一个开始入栈。
因此栈底高地址，栈顶低地址，举个例子如下：
void func(int x, float y, char z);
那么，调用函数的时候，实参 char z 先进栈，
然后是 float y，最后是 int x，
因此在内存中变量的存放次序是 x->y->z，因此，
从理论上说，我们只要探测到任意一个变量的地址，
并且知道其他变量的类型，通过指针移位运算，则总可以顺藤摸瓜找到其他的输入变量。
 */

/* 
下面是 <stdarg.h> 里面重要的几个宏定义如下：

typedef char* va_list;  
va_list 是一个字符指针，可以理解为指向当前参数的一个指针，取参必须通过这个指针进行。
<Step 1> 在调用参数表之前，定义一个 va_list 类型的变量，(假设va_list 类型变量被定义为ap)；

void va_start (va_list ap, prev_param); 
<Step 2> 然后应该对ap 进行初始化，让它指向可变参数表里面的第一个参数，
这是通过 va_start 来实现的，第一个参数是 ap 本身，
第二个参数是“...”之前的那个参数； 

type va_arg (va_list ap, type); 
<Step 3> 然后是获取参数，调用va_arg，它的第一个参数是ap，
第二个参数是要获取的参数的指定类型，然后返回这个指定类型的值，
并且把 ap 的位置指向变参表的下一个变量位置；

void va_end (va_list ap); 
<Step 4> 获取所有的参数之后，我们有必要将这个 ap 指针关掉，
以免发生危险，方法是调用 va_end，他是输入的参数 ap 置为 NULL，
应该养成获取完参数表之后关闭指针的习惯。说白了，就是让我们的程序具有健壮性。
通常va_start和va_end是成对出现。 

 */