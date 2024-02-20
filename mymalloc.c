#include "stdlib.h"
#include "stdio.h"
#include "mymalloc.h"
#define MEMLENGTH 512
#define TESTVALUE 3.5
static double memory[MEMLENGTH];
typedef struct ChunkHeader{
    size_t size;
    int allocated;
    ChunkHeader* nextChunkHeader;
}ChunkHeader;
void initializeMallocArray(){
    //This chunk of code creates the first chunk header IF the test value is not correctly set.
    // I think we are allowed to do this because 
    if (memory[0] != TESTVALUE){
        memory[0] = TESTVALUE;
        ChunkHeader firstChunkHeader;
        firstChunkHeader.size = 509*8; //512 - 1 (For the TESTVALUE) - 2 (For the first Chunk Header)
        firstChunkHeader.allocated = 0;
        firstChunkHeader.next = NULL;
        *((ChunkHeader *)&memory[1]) = firstChunkHeader;
}


    //actually create an array
    //Create the first chunk header
struct ChunkHeader mArr[MEMLENGTH]; // I don't think we are allowed to do this since the metadata for the storage array has to also be in the storage array
    struct ChunkHeader header = {0,0};
    mArr[0] = header;

}

size_t round_up(size_t size) {
    return (size + 7) & ~7;
}


ChunkHeader* find_free_chunk(size_t size){
    ChunkHeader* current = memory[1];
    while(current != NULL && !(current->allocated && current->size >= size)){
        current = current->nextChunkHeader;
    }
    return current;
}
void * mymalloc(size_t size, char *file, int line){    //I changed the function definition so that it aligns with the way they are defined in mymalloc.h the file and line are used for error messages
    if(size <= 0){
        fprintf(stderr, "Error at %s%d: Cannot allocate memory of size 
    less than or equal to 0\n", file, line);
            return NULL;
    }

    ChunkHeader* chunk = find_free_chunk(size);
    if(block != NULL){
        block -> free = 0;
        return(void*)(block +1);
    }

    chunk = (ChunkHeader*)sbrk(size * sizeof(ChunkHeader));
    if(chunk == (void*) - 1){
        fprintf(stderr, "Error at %s:%d: sbrk failed\n", file, line);
        return NULL;

    }
    chunk->size = size;
    chunk->free = 0;
    chunk->nextChunkHeader = memory[0];


    return(void*)(block + 1);

   
    initializeMallocArray();
    size = round_up(size);
    //Read the first chunk header which starts at memory[0] (Should always be there because we called initialize)
    //If the chunk header indicates that the chunk is allocated OR too small move to the next chunk header.
    //      We can calculate the location of the next chunk header using the size of the next chunk (Which is stored in our current chunk header)
    // Not sure what is supposed to happen if there is no chunks with enough space
    //Once we find a suitable chunk indicate that it is now allocated its chunk header and return a pointer to the chunk
/**
 * 
 * 
 * I was getting errors while compiling because I wanted to test something real quick so I just commented it out for now
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
**/


}
void coalesce(){
    ChunkHeader *currentChunkHeader = &memory[1];
    ChunkHeader *nextChunkHeader = currentChunkHeader->nextChunkHeader;
    while(nextChunkHeader!=NULL){
        if ((nextChunkHeader->allocated==0) && (currentChunkHeader->allocated==00)){
            currentChunkHeader->size = currentChunkHeader->size + sizeof(ChunkHeader)+nextChunkHeader->size;
            currentChunkHeader->nextChunkHeader = nextChunkHeader->nextChunkHeader;
            nextChunkHeader = currentChunkHeader->nextChunkHeader;
        }else{
            currentChunkHeader = nextChunkHeader;
            nextChunkHeader = nextChunkHeader->nextChunkHeader;
        }
    }

    
}
int checkIfAligned(ChunkHeader* currentChunkHeader){
    int count = 512*8;
    ChunkHeader* iteratedChunkHeader = &memory[0];
    return 1; //temporary
   // while (count > 0){
   //     if
    //} 
}
void myfree(void *ptr, char *file, int line){
    initializeMallocArray();
    if (!ptr){
        printf("free: null pointer (%s:%d)", file, line);
        return;
    } //If the pointer is null 
        
    if ((double*)ptr < &memory[1]||(double*)ptr > &memory[499]){
        printf("free: invalid pointer (%s:%d)", file, line);
        return;
    }//If the pointer doesn't point to somewhere in the array.
    ChunkHeader *currentChunkHeader =  ptr - sizeof(ChunkHeader);//Finds the location of the chunk header of the given chunk
    bool alignedBool = checkIfAligned(currentChunkHeader);
    if (currentChunkHeader->allocated==0){
        printf("free: double free (%s :%d)", file, line);
        return;
    }//If the chunk isn't allocated

    currentChunkHeader->allocated=0;
    coalesce(currentChunkHeader);
//I'm not sure how to check whether or not a pointer is in the middle of a chunk without directly accessing the memory which isn't allowed.


}

int main(int argc, char **argv)
{
    printf("%d", round_up(17));
}