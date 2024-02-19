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
void * mymalloc(){    
    initializeMallocArray();
    //Read the first chunk header which starts at memory[0] (Should always be there because we called initialize)
    //If the chunk header indicates that the chunk is allocated OR too small move to the next chunk header.
    //      We can calculate the location of the next chunk header using the size of the next chunk (Which is stored in our current chunk header)
    // Not sure what is supposed to happen if there is no chunks with enough space
    //Once we find a suitable chunk indicate that it is now allocated its chunk header and return a pointer to the chunk

}
void myfree(void *chunkPointer){
    if (!chunkPointer){return;} //If the pointer is null just return

    struct chunkHeader *currentChunkHeader =  chunkPointer - sizeof(struct chunkHeader);//Finds the location of the chunk header of the given chunk
    currentChunkHeader->allocated=0; //If there isn't a chunkheader there because we were given a bad pointer I'm not really sure what will happen

    //We should be able to subtract 16 bytes from the pointer and find a chunk header.
    //      If we don't find a chunk header there I think we can return a header
    //If we do find a chunk header then indicate that it is now unallocated.
    //      I'm not sure if we have to do anything to the data like delete it or set it to zeros or something
}