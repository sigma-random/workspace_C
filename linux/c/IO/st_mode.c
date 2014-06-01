#include "io.h"


int main(int argc, char ** argv)
{

    struct stat st;
    if(argc != 2)
    {
        printf("usage: %s filename\n",argv[0]);
        exit(-1);
    }
    if(-1==lstat(argv[1], &st))
    {
        perror("stat error!\n");
        exit(0);
    }
    printf("stat.st_dev = %d\n", st.st_dev );
    printf("stat.st_ino = %d\n", st.st_ino );
    printf("stat.st_mode = %d\n", st.st_mode );
    printf("stat.st_nlink = %d\n", st.st_nlink );
    printf("stat.st_uid = %d\n", st.st_uid);
    printf("stat.st_gid = %d\n", st.st_gid );
    printf("stat.st_rdev = %d\n", st.st_rdev );
    printf("stat.st_size = %d\n", st.st_size );
    printf("stat.st_blksize = %d\n", st.st_blksize );
    printf("stat.st_blocks = %d\n", st.st_blocks );
    printf("stat.st_atime = %d\n", st.st_atime );
    printf("stat.st_mtime = %d\n", st.st_mtime );
    printf("stat.st_ctime = %d\n", st.st_ctime );
    printf("===============st_mode==============\n");
    if(S_ISREG(st.st_mode))
    {
        printf("%s is regular file\n",argv[1]);
    }
    if(S_ISCHR(st.st_mode))
    {
        printf("%s is char file\n",argv[1]);
    }
    if(S_ISDIR(st.st_mode))
    {
        printf("%s is dir\n",argv[1]);
    }
    if(S_ISFIFO(st.st_mode))
    {
        printf("%s is pipe\n",argv[1]);
    }
    if(S_ISBLK(st.st_mode))
    {
        printf("%s is block file\n",argv[1]);
    }
    if(S_ISLNK(st.st_mode))
    {
        printf("%s is software link file\n",argv[1]);
    }
    if(S_ISSOCK(st.st_mode))
    {
        printf("%s is unix sock file\n",argv[1]);
    }
    


    return 0;
}
