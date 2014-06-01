#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct List* pList;

typedef struct List {

    pList pre;
    pList next;

}LIST;

typedef struct Info {
    
  char* name;
  int   count;
  pList list_head;
}INFO;


int main(int argc, char **argv) { 
    
    void    *result;
    INFO    *info;
    LIST    list = {
            .pre = NULL,
            .next = NULL
    };

    info = malloc(sizeof(*info));
    info->name = argv[0];
    info->count = argc;
    info->list_head = &list;
    
    result = info->list_head;
    printf("0x%08x\n",result);
    
    result = &info->list_head;
    printf("0x%08x\n",result);
    
    result = &(info->list_head);
    printf("0x%08x\n",result);

    result = ((INFO*)NULL);
    printf("0x%08x\n",result);

    result = &( ((INFO*)NULL)->list_head );
    printf("0x%08x\n",result);
    
    if(info) {
        free(info);
    }
    return 0;
}
