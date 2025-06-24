#include <stdint.h>
#include <stdio.h>

void randomFun() {
    printf("Something");
}

int main(int argc, char* argv[]) {
    int x = 5;
    int* x_add = &x;
    printf("x address: %p\n", x_add);
    printf("x value through pointer: %d\n", *x_add);

    *x_add = 6;
    printf("x value through pointer after changing it: %d\n", *x_add);

    int arr1[5];  // array of intergers
    // arr1[0] = 10;
    // arr1[1] = 5;
    // printf("arr1 pointer value: %d\n", *(arr1));
    // printf("arr1 + 1 pointer value: %d\n", *(arr1 + 1));
    // printf("arr1 + 2 pointer value: %d\n", *(arr1 + 2));

    int* arr2[10];  // array of (int) pointers
    printf("arr2 pointer address: %p\n", arr2);
    printf("arr2 pointer value: %p\n", *arr2);

    printf("arr2 + 1 pointer address: %p\n", (arr2 + 1));
    printf("arr2 + 1 pointer value: %p\n", *(arr2 + 1));

    arr2[1] = &x;
    *arr2[1] = *arr2[1] + 1;
    int y = 2;
    arr2[2] = &y;
    printf("random adress: %p\n", arr2[2]);
    // printf("arr2 + 1 pointer value after change: %p\n", (arr2 + 1));
    printf("x address: %p\n", x_add);
    printf("x value through pointer: %d\n", *x_add);

    void* myPtr;
    myPtr = randomFun;
    printf("void ptr: %p\n", myPtr);

    return 0;
}
