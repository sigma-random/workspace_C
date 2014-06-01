/*#####################################################
#       SecretChannel - -  file access time
#
#       Copyright (C) 2014 random <random@pku.edu.cn>
#
######################################################*/
#ifndef _SECRET_CHANNEL_
#define _SECRET_CHANNEL_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <error.h>
#include <fcntl.h>
#include <time.h>

#define TRUE        1
#define FALSE       0

#define WAIT_TIME   1


#define BASE_DIR	   "/home/user_low/"	/* endding by */


#define DATA_FILE_NUM   8					/* data file nums */

#define DATA_FILE0		BASE_DIR"0"
#define DATA_FILE1		BASE_DIR"1"
#define DATA_FILE2		BASE_DIR"2"
#define DATA_FILE3		BASE_DIR"3"
#define DATA_FILE4		BASE_DIR"4"
#define DATA_FILE5		BASE_DIR"5"
#define DATA_FILE6		BASE_DIR"6"
#define DATA_FILE7		BASE_DIR"7"
#define DATA_FILE_ARRAY_INIT(data_files)\
const char *data_files[DATA_FILE_NUM] = {\
	DATA_FILE0,\
	DATA_FILE1,\
	DATA_FILE2,\
	DATA_FILE3,\
	DATA_FILE4,\
	DATA_FILE5,\
	DATA_FILE6,\
	DATA_FILE7,\
};


#define FLAG_FILE_NUM   3					  /* flag file nums */

#define FLAG_FILE1		BASE_DIR"flag1"    
#define FLAG_FILE2		BASE_DIR"flag2"    
#define FLAG_FILE3      BASE_DIR"flag3"  
#define FLAG_FILE_ARRAY_INIT(flag_files)\
const char *flag_files[FLAG_FILE_NUM] = {\
	FLAG_FILE1,\
	FLAG_FILE2,\
    FLAG_FILE3\
};


#define ASC2BIN(asc,bin) \
{\
	int i;\
	for(i=0;i<DATA_FILE_NUM; \
		bin[i]=((asc&(1<<i))>>(i)),i++);\
}

#define BIN2ASC(bin,asc)\
{\
	int i;\
	for(asc=0,i=0;i<DATA_FILE_NUM;\
		asc+=(bin[i] << i),i++);\
}

#define GET_ATIME(filepath,st)\
    if(-1 == stat(filepath, &st)) {\
        perror("stat");\
        printf("file: %s\n\n",filepath);\
        exit(-1);\
    }


int get_files_atime(const char* files[],int filenum, time_t atime[]){
    int i = 0;
    struct stat st;
    for(i = 0; i < filenum; i++){
        GET_ATIME(files[i],st);
        atime[i] = st.st_atime;
        //printf("%s : st_atime = %d\n",files[i],atime[i]);
    }
    return 0;
}


inline int OpenReadFile(const char *filepath, int flag) {
    int fd ;
    char buf[10];
    if(0 > (fd = open(filepath,flag))){
        perror("open");
        printf("file: %s\n",filepath);
        return(-1);
    }
    read(fd,buf,10);
    close(fd);
    return 0;
}


void signal_wait(const char* file, time_t *orig_atime ) {
    struct stat st;
    while(TRUE){
    	GET_ATIME(file,st);
		if(st.st_atime > *orig_atime){
			*orig_atime = st.st_atime;
			break;
		}
		sleep(WAIT_TIME);
		printf("waitting...\n");
	}

}


void signal_post(const char* file) {
	OpenReadFile(file,O_RDONLY);
}




#endif
