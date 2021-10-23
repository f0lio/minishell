#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>

/**
** This function limits the memory (MB) the program can use (abuse)
** It must be called before anything else.
**
** NOTE: You can allocate N bytes of memory,
** though it's not considered as used until you write in it.
**/
void setmemlimit(int mb)
{
        struct rlimit memlimit;
        long bytes;

        printf("WARNING!\nMEMORY LIMITED AT %d MB\n", mb);
        bytes = mb * (1024*1024);
        memlimit.rlim_cur = bytes;
        memlimit.rlim_max = bytes;
        setrlimit(RLIMIT_AS, &memlimit); 
}
