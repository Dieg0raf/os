#include <stdio.h>

int main(int argc, char* argv[]) {
    // char* c = "somethin";
    //
    // printf("char c: %c\n", *c);
    // printf("char c: %p\n\n", (void*)c);
    // printf("char c: %c\n", *(c + 1));
    // printf("char c: %p\n\n", (void*)c + 1);
    // printf("char c: %c\n", *(c + 2));
    // printf("char c: %p\n\n", (void*)c + 2);
    // printf("char c: %c\n", *(c + 3));
    // printf("char c: %p\n\n", (void*)c + 3);
    // printf("char c: %c\n", *(c + 4));
    // printf("char c: %p\n\n", (void*)c + 4);
    //
    // printf("\n");
    // printf("char c: %p\n\n", (void*)c + 9);
    // printf("char c: %c\n", *(c + 9));
    int x = 5;
    int* i = &x;
    printf("int i dereferenced: %d\n", *i);
    printf("int i value address: %p\n", i);
    i++;
    printf("int i value address: %p\n", i);
    i++;
    printf("int i value address: %p\n", i);
    i++;
    printf("int i value address: %p\n", i);
    i += 4;
    printf("int i value address: %p\n", i);
    // char myString[] = "Hello, World!";
    // printf("mystring address: %p\n", (void*)myString);
    // printf("mystring address: %c\n", *myString);
    //
    // printf("\n");
    // printf("mystring address: %p\n", (void*)(myString + 1));
    // printf("mystring address: %c\n", *(myString + 1));
    //
    // printf("\n");
    // printf("mystring address: %p\n", (void*)(myString + 2));
    // printf("mystring address: %c\n", *(myString + 2));
    //
    // printf("\n");
    // printf("mystring address: %p\n", (void*)(myString + 12));
    // printf("mystring address: %c\n", *(myString + 12));

    return 0;
}
