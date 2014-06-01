#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


__attribute__((constructor)) void before_main() {

    printf("before main\n");
}

int main() {
    printf("in main\n");
}
