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


//TestB will use malloc() to get 120 1-byte objects and store the pointers in an array then
//use free() to deallocate the chunks

long testB(int number_of_tests){
struct timeval, tv_start, tv_end;
char* storage[120];
int i = 0;
gettimeoftheday(&tv_start, NULL);
while(i < number_of_tests){
    int j;
    for(j = 0; j < 120; j++){
        storage[j] = malloc(1);
    }

    for (j = 0; j < 120; j++){
        free(storage[j]);
    }

    gettimeofday(&tv_end, NULL);

}
return(tv_end.tv_usec - tv_start.tv_usec);


}

long testC (int number_of_tests){
    struct timeval, tv_start, tv_end;
    char* storage[120];
    int allocatedNum = 0;
    gettimeofday(&tv_start, NULL)
    while(number_of_tests != 120){
        int randNum = (rand() % 2);
        if(randNum == 0){
            storage[allocatedNum] = malloc(1);
            allocatedNum++;
        }
        else{
            if(allocatedNum > 0){
                free(storage[allocatedNum-1]);
                allocatedNum--;
            }
        }
    }

    int i = 0;
    for(i; i<120;i++){
        free(storage[i]);
    }

    gettimeofday(&tv_end, NULL);
    return(tv_end.tv_usec - tv_start.tv_usec);
}
