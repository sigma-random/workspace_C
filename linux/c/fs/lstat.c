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
    return 0;
}
