Mychal Ortega netID: mlo77
Sebastian Hanna netID: sah324
hello

Test plan:

Description of Test Programs:
We did a total of 5 tests. 
testA
    - uses malloc() and immediately free() a 1-byte object 120 times.
testB
    - uses malloc()to get 120 1-byte objects, storing the pointers in an array, then uses free() to deallocate the chunks.
testC
    - creates an array of 120 pointers. It repeatedly makes a random choice between allocating a 1-byte object and adding the pointer to the array and deallocating a previously allocated object(if any),k until it has allocated 120 times. It then deallocates any remaining objects.
testD
    - this test is like testC where decided whether to free() and malloc() but instead of randomizing a 1-byte object it is now randomizing the size of the object. The test will go until it has malloc() 50 times. It then will deallocate any remaining objects.
testE
    - this test will malloc() 50 1-byte pointers then free() all objects backwards. 
