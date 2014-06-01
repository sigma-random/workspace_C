#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h>

using namespace std;


class Test{

    public:
             Test(){printf("test construct!\n");}
            ~Test(){printf("test destruct!\n");}

};



void before_main(void) __attribute((constructor));
void after_main(void) __attribute((destructor));



Test test;



int main() {


    printf("in main\n");
    return 0;
}


void before_main()
{
    printf("before main\n");
}

void after_main()
{
    printf("after main\n");
}
