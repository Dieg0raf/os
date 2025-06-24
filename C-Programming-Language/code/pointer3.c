#include <stdint.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    char myString[40];  // myString is char*
    printf("%p\n", myString);
    printf("%p\n", (myString + 1));

    // myArrayOfStrings (char*[]) = [ char* | char* | char* | char* | char* ]
    // //                               |      |      |      |      |
    // //                               v      v      v      v      v
    // //                            "one"  "two"  "three" NULL   NULL

    char* myArryOfStrings[5];  // myArrayOfStrings is char**
    char x = 'a';
    printf("%p\n", *myArryOfStrings);
    *myArryOfStrings = &x;  // myArrayOfStrings[0] = &x;
    printf("%p\n", *myArryOfStrings);
    printf("%c\n", **myArryOfStrings);
    // printf("%p\n", (myArryOfStrings + 1));
    // printf("%p\n", (myArryOfStrings + 2));

    printf("\n\n");
    int arr[4] = {5, 6, 7, 8};  // type of arr is int*
    printf("%p\n", arr);
    printf("%p\n", arr + 1);

    // output the same thing
    printf("%d\n", *(arr + 1));
    printf("%d\n", arr[1]);
    printf("%d\n", 1 [arr]);  // 1[arr] == *(1 + arr)
    printf("%d\n", *(1 + arr));

    // casting
    printf("\n\n");
    printf("%llu\n", (uint64_t)(2 + 5));

    return 0;
}
