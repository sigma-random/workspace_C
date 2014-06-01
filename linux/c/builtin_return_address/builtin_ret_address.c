#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
void bar(void);
void foo()
{
   // printf("in foo()\n");
    printf("foo: __builtin_return_address(0) = 0x%08X\n",__builtin_return_address(0));
    printf("foo: __builtin_return_address(1) = 0x%08X\n",__builtin_return_address(1));
    bar();
}

void bar()
{

    printf("bar: __builtin_return_address(0) = 0x%08X\n",__builtin_return_address(0));
    printf("bar: __builtin_return_address(1) = 0x%08X\n",__builtin_return_address(1));


}
int main()
{
    printf("main: __builtin_return_address(0) = 0x%08X\n",__builtin_return_address(0));
    foo();
    return 0;
}
