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
}
void * mymalloc(size_t size, char *file, int line){    
    initializeMallocArray();
    //Read the first chunk header which starts at memory[0] (Should always be there because we called initialize)
    //If the chunk header indicates that the chunk is allocated OR too small move to the next chunk header.
    //      We can calculate the location of the next chunk header using the size of the next chunk (Which is stored in our current chunk header)
    // Not sure what is supposed to happen if there is no chunks with enough space
    //Once we find a suitable chunk indicate that it is now allocated its chunk header and return a pointer to the chunk

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