/*#####################################################
#       SecretChannel - -  file access time
#
#       Copyright (C) 2014 random <random@pku.edu.cn>
#
######################################################*/

#include "common.h"

#define FILE_FLAG   (O_CREAT | O_EXCL)
#define FILE_MODE   (S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IROTH)

int createFiles();
int checkCompletion();
char recv_one_byte();


DATA_FILE_ARRAY_INIT(data_files);
FLAG_FILE_ARRAY_INIT(flag_files);
time_t data_file_atime[DATA_FILE_NUM] = {0};
time_t flag_file_atime[FLAG_FILE_NUM] = {0};

char buf[4096];


int main(int argc, char **argv)
{
   
    int i;
    char asc;

    createFiles();

    get_files_atime(data_files,DATA_FILE_NUM,data_file_atime);
    get_files_atime(flag_files,FLAG_FILE_NUM,flag_file_atime);

    signal_wait(flag_files[FLAG_FILE_NUM-1],&flag_file_atime[FLAG_FILE_NUM-1]);
    signal_post(flag_files[0]);

    printf("\n**** start to recieve msg! ****\n\n");
    i = 0;
    while(TRUE){
        
        signal_wait(flag_files[1],&flag_file_atime[1]);
        
        asc = recv_one_byte();
        printf("\n**** recv : %c ****\n",asc);
        buf[i++] = asc;

        signal_post(flag_files[0]);
        
        if(checkCompletion()){
            break;
        }

    }
    printf("recv finished..\n");
    printf("\n\nrecv msg :\n%s\n",buf);
    
    return 0;

}

int createFiles(){
    int i;
    int fd;

    for (i = 0; i < DATA_FILE_NUM; i++){
        if(0 > (fd=open(data_files[i],FILE_FLAG,FILE_MODE) /*&& errno != EEXIST*/)){
            //perror("creat");
            //printf("file: %s\n",data_files[i]);
        }        
        chmod(data_files[i],FILE_MODE);
        close(fd);

    }

    for (i = 0; i < FLAG_FILE_NUM; i++){
        if(0 > (fd=open(flag_files[i],FILE_FLAG,FILE_MODE))){
            //perror("creat");
            //printf("file: %s\n\n",flag_files[i]);
        }    
        chmod(flag_files[i],FILE_MODE);
        close(fd);
    }

    return 0;
}


int checkCompletion( ) {
    struct stat st;
    GET_ATIME(flag_files[FLAG_FILE_NUM-1],st);
    if(st.st_atime > flag_file_atime[FLAG_FILE_NUM-1]){
        return TRUE;
    }else{
        return FALSE;
    }
}

char recv_one_byte(){

    int i;
    struct stat st;
    char bin[DATA_FILE_NUM];
    char asc;

    for(i = 0; i < DATA_FILE_NUM; i++) {
        GET_ATIME(data_files[i],st);
        if(st.st_atime > data_file_atime[i]){
            data_file_atime[i] = st.st_atime;
            bin[i] = 1;
            continue;
        }
        bin[i] = 0;
    }
    BIN2ASC(bin,asc);
    return asc;
}


