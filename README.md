Mychal Ortega netID: mlo77<br>
Sebastian Hanna netID: sah324


Test plan:<br><br>

Description of Test Programs:<br>
We did a total of 5 tests. <br>
testA<br>
    - uses malloc() and immediately free() a 1-byte object 120 times. It takes in an integer named number_of_tests to determine how many times to run the test.<br>
testB<br>
    - uses malloc()to get 120 1-byte objects, storing the pointers in an array, then uses free() to deallocate the chunks. It takes in an integer named number_of_tests to determine how many times to run the test.<br>
testC<br>
    - creates an array of 120 pointers. It repeatedly makes a random choice between allocating a 1-byte object and adding the pointer to the array and deallocating a previously allocated object(if any),k until it has allocated 120 times. It then deallocates any remaining objects. It takes in an integer named number_of_tests to determine how many times to run the test.<br>
testD<br>
    - this test is like testC where decided whether to free() and malloc() but instead of randomizing a 1-byte object it is now randomizing the size of the object. The test will go until it has malloc() 50 times. It then will deallocate any remaining objects. It takes in an integer named number_of_tests to determine how many times to run the test.<br>
testE<br>
    - this test will malloc() 50 1-byte pointers then free() all objects backwards. <br><br>

Project Design<br>
When mymalloc() is called, an initializing function will always be called. This function will detect whether or not the array has been initialized by reading the data of the first 24 bytes. The first 24 bytes will be 3 doubles 0.0 0.0 0.0 if unitialized. If initialized, the first 24 bytes will ALWAYS correspond to the very first ChunkHeader, which cannot hold data equal to 0.0 0.0 0.0. Because the first 24 bytes will never be accessible to clients (unless they intentionally use pointer arithmetic to break the program) we can read them safely.<br>
After this sequence, mymalloc() will round the requested bytes up to an 8 aligned number, check if the size is a negative number, find a free chunk, divide the chunk if necessary, then indicate it is allocated and then return a pointer to the chunk<br><br>

When calling myfree() the initialize function is again called. Myfree() will produce an error message, but initialize is still called to avoid a a runtime error. Several checks are then performed. If the pointer is null, if the pointer points somewhere outside the memory array, if the pointer does not point to the start of a chunk, or if the pointer points to a chunk that is not allocated, an error message will be produced. After executing a valid freeing of a chunk, free chunks are coalesced by iterating through all the chunkheaders and checking to see if there are any unallocated chunks next to each other.
