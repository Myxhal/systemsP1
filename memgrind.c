#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
//#include<time.h> //Need to include time.h to record times for the workloads
#include "mymalloc.h"

/* testA will malloc() and immediately free() a 1-byte object, 120 times
*/

long testA (int number_of_tests){
    //create a timeval for time start and time end
    struct timeval tv_start, tv_end;
    int i = 0;
    //put current time in time start
    gettimeofday(&tv_start, NULL);
    while(i < number_of_tests){
        char* oneByte = malloc(1);
        free(oneByte);
        i++;

    }
    gettimeofday(&tv_end, NULL);

    //returns time in seconds
    return(tv_end.tv_usec - tv_start.tv_usec);


}


//TestB will use malloc() to get 120 1-byte objects and store the pointers in an array then
//use free() to deallocate the chunks

long testB(int number_of_tests){
struct timeval tv_start, tv_end;
char* storage[120];
int i = 0;
gettimeofday(&tv_start, NULL);
while(i < number_of_tests){
    int j;
    for(j = 0; j < 120; j++){
        storage[j] = malloc(1);
    }

    for (j = 0; j < 120; j++){
        free(storage[j]);
    }
i++;
}
gettimeofday(&tv_end, NULL);
return(tv_end.tv_usec - tv_start.tv_usec);


}

long testC (int number_of_tests){
    struct timeval tv_start, tv_end;
    char* storage[120];
    int allocatedNum = 0;
    gettimeofday(&tv_start, NULL);
    while(allocatedNum != 120){
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


long testD(int number_of_tests){
    struct timeval tv_start, tv_end;
    char* storage[50];
    int allocatedNum = 0;
    int mallocNum = 0;
    gettimeofday(&tv_start, NULL);          
     while (mallocNum != 50) { 
        int randNum = (rand() % 2); 
        if (randNum == 0) { 
            //Generate between 1 and 64.
            size_t randSize = (rand() % 64) + 1; 
            storage[allocatedNum] =  malloc(randSize);
            //Increment the number of times malloced
            mallocNum++; 
            allocatedNum++; //Increment number of allocated in array
        } else { 
            if (allocatedNum> 0) {
                free(storage[allocatedNum - 1]); 
                allocatedNum--;
            }
        }
            }
    int i = 0;
    for(i; i < allocatedNum; i++){
        free(storage[i]);
    }
    gettimeofday(&tv_end, NULL);
    return (tv_end.tv_usec - tv_start.tv_usec);
}

long testE(int number_of_tests){
    struct timeval tv_start, tv_end;
    int i = 0;
    //Create a storage array
    char* storage[50]; 
    gettimeofday(&tv_start, NULL); 
    while (i < number_of_tests) {
        //Create storage looping forwards
        int j;
        for (j = 0; j < 50; j++) {
            storage[j] = malloc(1);
        }
        //Remove storage looping backwards
        for (j = 49; j >= 0; j--) {
            free(storage[j]);
        }
        i++;
    }
    gettimeofday(&tv_end, NULL);
    return (tv_end.tv_usec - tv_start.tv_usec);
}


    long timeAVG(long* work, int workCOUNT){
        long total = 0;
        int i = 0;
        for (i; i < workCOUNT; i++) { //Loop through all workload times and all them all together
        total += work[i];
    }
     return(total / workCOUNT);
    }

    int main(int argc, char** argv){
        int iterations = 50;
        int count = 0;

        long testA_time[iterations];
        long testB_time[iterations];
        long testC_time[iterations];
        long testD_time[iterations];
        long testE_time[iterations];
        while(count < iterations){
            testA_time[count] = testA(120);
            testB_time[count] = testB(3);
            testC_time[count] = testC(1);
            testD_time[count] = testD(1);
            testE_time[count] = testE(50);
            count++;

        }

        printf("Test A time in microseconds: %ld\n", timeAVG(testA_time, iterations));
        printf("Test B time in microseconds: %ld\n", timeAVG(testA_time, iterations));
        printf("Test C time in microseconds: %ld\n", timeAVG(testA_time, iterations));
        printf("Test D time in microseconds: %ld\n", timeAVG(testA_time, iterations));
        printf("Test E time in microseconds: %ld\n", timeAVG(testA_time, iterations));

    }











