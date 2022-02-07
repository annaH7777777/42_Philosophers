#include <sys/time.h>
#include <stdio.h>



int main()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    long long a  = t.tv_sec * 1000 + t.tv_usec  / 1000;
    printf("%ld, %d, %lld", t.tv_sec, t.tv_usec, a);
    
}