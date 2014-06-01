#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


__attribute__((destructor)) void after_main() {

    printf("before main\n");
}

int main() {
    printf("in main\n");
}
