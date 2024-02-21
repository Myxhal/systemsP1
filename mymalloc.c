#include "stdlib.h"
#include "stdio.h"
#include "mymalloc.h"
#define MEMLENGTH 512
static double memory[MEMLENGTH];

typedef struct ChunkHeader{
    size_t size;
    int allocated;
    struct ChunkHeader* nextChunkHeader;
    
}ChunkHeader;
void initializeMallocArray(){
    //This chunk of code creates the first chunk header IF the test value is not correctly set.
    // I think we are allowed to do this because 
    if (memory[0] ==0.0 && memory[1] ==0.0){
        ChunkHeader firstChunkHeader;
        firstChunkHeader.size = 509*8; //512  - 3 (For the first Chunk Header)
        firstChunkHeader.allocated = 0;
        firstChunkHeader.nextChunkHeader = NULL;
        *((ChunkHeader *)&memory[0]) = firstChunkHeader;
}


    //actually create an array
    //Create the first chunk header
//struct ChunkHeader mArr[MEMLENGTH]; // I don't think we are allowed to do this since the metadata for the storage array has to also be in the storage array
  //  struct ChunkHeader header = {0,0};
    //mArr[0] = header;

}

size_t round_up(size_t size) {
    return (size + 7) & ~7;
}


ChunkHeader* find_free_chunk(size_t size){
    ChunkHeader* current = (ChunkHeader*)((char*) &memory[0]);
    // current can't be null
    // the size has to be more than the requested size
    // has to be unallocated
    while(current != NULL && (current->allocated == 1 || current->size < size)){
        current = current->nextChunkHeader;
    }
    //while(current != NULL && !(current->allocated && current->size >= size)){
      //  current = current->nextChunkHeader;
    //}
    return current;
}
ChunkHeader* correctChunkSize(ChunkHeader* chunkHeader,size_t requestedSize){
    if(chunkHeader->size > requestedSize){
        size_t leftoverSize = chunkHeader->size - requestedSize - sizeof(ChunkHeader);
        chunkHeader->size = requestedSize;
        //Creates a new chunkheader to head the leftover size and sets its size, pointer, and allocated status accordingly.
        ChunkHeader newChunkHeader;
        newChunkHeader.size = leftoverSize;
        newChunkHeader.nextChunkHeader = chunkHeader->nextChunkHeader;
        newChunkHeader.allocated = 0;
        
        //Puts this chunkheader in the correct place in memory
        ChunkHeader* addressForNewHeader = (ChunkHeader* )(((char*)chunkHeader) + (chunkHeader->size)+sizeof(ChunkHeader));
        *addressForNewHeader = newChunkHeader;

        chunkHeader->nextChunkHeader = addressForNewHeader;
    }
    else{
        return chunkHeader;
    }
}
void* mymalloc(size_t size, char *file, int line){    //I changed the function definition so that it aligns with the way they are defined in mymalloc.h the file and line are used for error messages
    double* memorylocation = &memory[0]; 
    initializeMallocArray();
    size = round_up(size);
    if(size <= 0){
        fprintf(stderr,"Error at %s%d: Cannot allocate memory of size less than or equal to 0\n", file, line);
            return NULL;
    }

    ChunkHeader* chunkHeader = find_free_chunk(size);//Finds a free chunk that is big enough
    if(chunkHeader == NULL){
        return NULL;
    }
    chunkHeader = correctChunkSize(chunkHeader,size);//If a chunk is too big this will shrink it to the correct size
    chunkHeader -> allocated = 1;
    size_t sizeOfChunkHeader  = sizeof(ChunkHeader);
    void* locationOfChunk = ((char*) chunkHeader + sizeOfChunkHeader);
    return locationOfChunk;
}
void coalesce(){
    ChunkHeader *currentChunkHeader = &memory[0];
    ChunkHeader *nextChunkHeader = currentChunkHeader->nextChunkHeader;
    while(nextChunkHeader!=NULL){
        if ((nextChunkHeader->allocated==0) && (currentChunkHeader->allocated==0)){
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
    ChunkHeader* iteratedChunkHeader = &memory[0];
    while(iteratedChunkHeader->nextChunkHeader!=NULL){
        //char* locationofChunk = (char*)(iteratedChunkHeader)+sizeof(ChunkHeader);
        if(iteratedChunkHeader==currentChunkHeader){
            return 1;
        }
        else{
            iteratedChunkHeader = iteratedChunkHeader->nextChunkHeader;
        }
    }
    return 0; 
}
void myfree(void *ptr, char *file, int line){
    initializeMallocArray();
    //If the pointer is null 
    if (!ptr){
        printf("free: null pointer (%s:%d)", file, line);
        return;
    } 
    //If the pointer doesn't point to somewhere in the array. 
    if ((double*)ptr < &memory[1]||(double*)ptr > &memory[499]){
        printf("free: invalid pointer (%s:%d)", file, line);
        return;
    }

    ChunkHeader *currentChunkHeader =  ptr - sizeof(ChunkHeader);//Finds the location of the chunk header of the given chunk
    int aligned = checkIfAligned(currentChunkHeader);
    if(!aligned){
        printf("free: invalid pointer (%s :%d)",file,line);
    }
    //If the chunk isn't allocated
    if (currentChunkHeader->allocated==0){
        printf("free: double free (%s :%d)", file, line);
        return;
    }

    currentChunkHeader->allocated=0;
    coalesce(currentChunkHeader);
//I'm not sure how to check whether or not a pointer is in the middle of a chunk without directly accessing the memory which isn't allowed.
}

int main(int argc, char **argv)
{
    double* ptr = malloc(16);
    double* ptr2 = malloc(16);
    ptr[0] = 1.0;
    ptr[1] = 2.0;
    ptr2[0] = 3.0;
    ptr2[1] = 3.0;
    free(ptr);
    double* newptr1 = malloc(16);
    newptr1[0] = 5.0;
    newptr1[1] = 6.0;
    for(int i = 0; i < 500; i++){
        printf("%f  ",memory[i]);
    }
    
    //malloc(-5);
    //printf("%d", sizeof(ChunkHeader));
}