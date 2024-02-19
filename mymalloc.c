#include "stdlib.h"

#include "mymalloc.h"
#define MEMLENGTH 512
static double memory[MEMLENGTH];
struct chunkHeader{
    int size;
    int allocated;
};
void initializeMallocArray(){
    //actually create an array
    //Create the first chunk header
    struct chunkHeader mArr[MEMLENGTH];
    struct chunkHeader header = {0,0};
    mArr[0] = header;

}
void * mymalloc(size_t size, char *file, int line){    
    initializeMallocArray();
    //Read the first chunk header which starts at memory[0] (Should always be there because we called initialize)
    //If the chunk header indicates that the chunk is allocated OR too small move to the next chunk header.
    //      We can calculate the location of the next chunk header using the size of the next chunk (Which is stored in our current chunk header)
    // Not sure what is supposed to happen if there is no chunks with enough space
    //Once we find a suitable chunk indicate that it is now allocated its chunk header and return a pointer to the chunk

    //loop intilaize 
    int i = 0;
    //pointer to array
    char* ptr = &mArr[i]; 
    //traverse
   for(i; i < MEMLENGTH; i++){
    //check to see if chunk is allocated and if it has enough size
    if(mArr[i].allocated == 1 || mArr[i].size < size) {
        continue;
    }
    // checks if there is enough size in the unallocated chunk
    else if (size <= mArr[i]size){
        myArr[i].allocated = 1;
        //not sure if this is right
        //subtract if there is more memory left?
        mArr[i].size = size;
        //ptr to chunk 
        ptr = &mArr[i];
        
        return ptr;
        
    }
    else{
        return printf("There is not enough memory for size %d", size);

    }

   }



}
void myfree(void *ptr, char *file, int line){
    initializeMallocArray();
    if (!ptr){
        printf("free: null pointer (%c:%d)", file, line);
        return;
    } //If the pointer is null 
        
    if (ptr<&memory[1]||ptr >&memory[499]){
        printf("free: invalid pointer (%c:%d)", file, line);
        return;
    }//If the pointer doesn't point to somewhere in the array.
    struct chunkHeader *currentChunkHeader =  ptr - sizeof(struct chunkHeader);//Finds the location of the chunk header of the given chunk
    if (currentChunkHeader->allocated==0){
        printf("free: double free (%c :%d)", file, line);
        return;
    }//If the chunk isn't allocated

    currentChunkHeader->allocated=0;

//I'm not sure how to check whether or not a pointer is in the middle of a chunk without directly accessing the memory which isn't allowed.


}