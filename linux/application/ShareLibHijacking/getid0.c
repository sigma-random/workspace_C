//#include <dlfcn.h> 
#include <unistd.h> 
#include <sys/types.h> 

/*

	gcc -fPIC -shared getid0.c -o getid0.so

*/

uid_t geteuid( void ) 
{ 
        return 0; 
} 

uid_t getuid( void ) 
{ 
        return 0; 
} 

uid_t getgid( void ) 
{ 
        return 0; 
} 
