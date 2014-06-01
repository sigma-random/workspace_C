#ifndef _FILE_H_
#define _FILE_H_
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<dirent.h>

#define MODE(s,u,g,o)   ((s<<9)|(u<<6)|(g<<3)|(0))
#define MODE_644 MODE(0,6,4,4)


#endif
