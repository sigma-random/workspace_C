#include "io.h"



int selectdir(const struct dirent* );
void getfiletype(struct stat* , char* );


int main(int argc, char **argv)
{
    DIR *dp;
    struct dirent **pDirEntList;
    struct stat st;
    char filetype[10] = {0};
    int i = 0;
    int total =0;
    char *filename;
    if(argc != 2)
    {
        printf("usage: %s dirname\n",argv[0]);
        exit(-1);
    }
    if(NULL == (dp = opendir(argv[1])))
    {
        printf("can't open dir %s\n",argv[1]);
        exit(-1);
    }
    if(-1 == chdir(argv[1]))
    {
        printf("error: chdir %s\n",argv[1]);
        exit(-1);
    }
    total = scandir(argv[1],&pDirEntList,selectdir,alphasort);
    if(total == 0)
    {
        printf("can't scan dir %s\n",argv[1]);
        exit(-1);
    }
    for(i = 0; i < total; i++)
    {
        bzero(&st,sizeof(struct stat));
        filename = (*pDirEntList)->d_name;
        lstat(filename,&st);
        getfiletype(&st,filetype);
        printf("%-08s%s\n",filetype,filename);
        pDirEntList++;
    } 
    closedir(dp);
    return 0;
}




int selectdir( const struct dirent* pDirEnt)
{
    if(pDirEnt->d_name[0] == '.')
    {
        return 0;
    }
    return 1;
}

void getfiletype(struct stat* st, char* filetype)
{
    bzero(filetype,strlen(filetype));
    if(S_ISREG(st->st_mode))
    {
        memcpy(filetype,"file", 4);
    }
    else if(S_ISDIR(st->st_mode))
    {
        memcpy(filetype,"dir", 3);
    }
    else if(S_ISFIFO(st->st_mode))
    {
        memcpy(filetype,"pipe", 4);
    }
    else if(S_ISLNK(st->st_mode))
    {
        memcpy(filetype,"link", 4);
    }
    else if(S_ISSOCK(st->st_mode))
    {
        memcpy(filetype,"sock", 4);
    }
    else if(S_ISCHR(st->st_mode))
    {
        memcpy(filetype,"char", 4);
    }
    else if(S_ISBLK(st->st_mode))
    {
        memcpy(filetype,"block", 5);
    }
    else
    {
        memcpy(filetype,"unknown", 7); 
    }

}


void getfiletime(struct stat* st, char* time)
{
    bzero(time,strlen(time));

}

void getfilemode(struct stat* st, char* mode)
{
    bzero(mode,strlen(mode));

}

