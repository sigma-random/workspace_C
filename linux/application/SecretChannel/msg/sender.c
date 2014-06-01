
/*#####################################################
#       SecretChannel - -  file access time
#
#       Copyright (C) 2014 random <random@pku.edu.cn>
#
######################################################*/

#include "common.h"

int completion();
int send_one_byte(char asc);


DATA_FILE_ARRAY_INIT(data_files);
FLAG_FILE_ARRAY_INIT(flag_files);

time_t data_file_atime[DATA_FILE_NUM] = {0};

time_t flag_file_atime[FLAG_FILE_NUM] = {0};




int main(int argc, char **argv) {

    int i;
    int len;
    char * msg;

    printf("\n!!!! make sure run reciever firstly before running sender !!!!\n\n");

    if(argc != 2) {
        printf("[*] usage: %s msg\n",argv[0]);
        return -1;
    }

    msg = argv[1];
    len = strlen(msg);

    get_files_atime(data_files,DATA_FILE_NUM,data_file_atime);
    get_files_atime(flag_files,FLAG_FILE_NUM,flag_file_atime);

    signal_post(flag_files[FLAG_FILE_NUM-1]);

    printf("send msg: %s\n",msg);

    for(i = 0; i < len; i++){

        signal_wait(flag_files[0],&flag_file_atime[0]);

        printf("\n**** send: %c ****\n",msg[i]);
        send_one_byte(msg[i]);

        signal_post(flag_files[1]);
    }

    completion();

    printf("send finished..\n");
    
    return 0;
}


int completion() {
    signal_post(flag_files[FLAG_FILE_NUM-1]);
}


int send_one_byte(char asc){

    int i;
    char bin[DATA_FILE_NUM];
    char ret;

    ASC2BIN(asc,bin);
    for(i = 0; i < DATA_FILE_NUM; i++) {
        if(bin[i] == 1){
            OpenReadFile(data_files[i], O_RDONLY);
        }
    }
    BIN2ASC(bin,ret);
    return 0;
}



