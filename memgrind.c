#include <stdlib.h>
#include <stdio.h>
#include<time.h> //Need to include time.h to record times for the workloads
#include "mymalloc.h"

/* testA will malloc() and immediately free() a 1-byte object, 120 times
*/

long testA (int number_of_tests){
    //create a timeval for time start and time end
    struct timeval, tv_start, tv_end;
    int i = 0;
    //put current time in time start
    gettimeofday(&tv_start, NULL);
    while(i < number_of_tests){
        char* oneByte = malloc(1);
        free(oneByte);
        i++;

    }
    gettimeofday(tv_end, NULL);

    //returns time in seconds
    return(tv_end.tv_usec - tv_start.tv_usec);


}




