#ifndef __FILE_SHARE__
#define __FILE_SHARE__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/errno.h>

#define  MODE 		( S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define  FLAGS 		(O_CREAT  | O_RDWR)
#define  BUF_SIZE	1024
#define  MAX_PATH	256


int fileclient(int readfd, int writefd) {

	int fd = 0;
	int len = 0;
	ssize_t r_cnt = 0;
	ssize_t w_cnt = 0;
	char path[MAX_PATH];
	char newpath[MAX_PATH];
	char buf[BUF_SIZE];

	memset(path,0,MAX_PATH);

	printf("[Client] input the filepath: ");
	fgets(path, MAX_PATH, stdin);
	len = strlen(path);
	if( '\n' == path[len -1] ) {
		path[len -1] = '\0';
		len--;
	}

	//write filename
	write(writefd,path,len);

	sleep(1);

	/* open or create new file */
	memset(newpath,0,MAX_PATH);
	printf("[Client] input new filename: ");
	fgets(newpath, MAX_PATH, stdin);
	len = strlen(newpath);
	if( '\n' == newpath[len -1] ) {
		newpath[len -1] = '\0';
	}
	
	//snprintf(path,MAX_PATH,"./fifo_tmp",getpid());
	printf("[Client] save file: \"%s\" to \"%s\" \n",path,newpath);
	if( 0 > (fd = open(newpath,FLAGS , MODE)) ) {
		perror("[Client] open");
		return (-1);
	}

	/* recv file content */
	memset(buf,0,BUF_SIZE);

	while( 0 < (r_cnt = read(readfd,buf,BUF_SIZE))) {
		//write(STDOUT_FILENO,buf,r_cnt);
		/* write content to newfile */
		if(-1 == write(fd,buf,r_cnt)) {
			perror("[Client] write");
			break;
		}
		memset(buf,0,BUF_SIZE);
	}

	close(fd);
	return 0;
}

int fileserver(int readfd, int writefd) {
	
	int fd = 0;
	int len = 0;
	ssize_t r_cnt = 0;
	ssize_t w_cnt = 0;
	char path[MAX_PATH];
	char buf[BUF_SIZE];

	memset(path,0,MAX_PATH);

	/* recv filepath */
	if(0 >= (r_cnt = read(readfd,path,MAX_PATH))){
		printf("[Server] error: you never give the filepath!\n");
		return (-1);
	}
	printf("[Server] read file: %s\n",path);
	/* open file */
	if( 0 > (fd = open(path,O_RDONLY))) {
		perror("[Server] open");
		return (-1);
	}

	/* read file and sent file content */
	memset(buf,0,BUF_SIZE);
	while( 0 < (r_cnt = read(fd,buf,BUF_SIZE))) {
		write(writefd,buf,r_cnt);
		memset(buf,0,BUF_SIZE);
	}
	close(fd);
	return 0;
}

#endif