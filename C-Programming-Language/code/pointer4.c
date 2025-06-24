#include <stdio.h>

#define MAX 100
#define NAME "Diego"

int main(int argc, char* argv[]) {
    printf("hell world\\\n");    // back slash itself
    printf("hell world\"\n");    // double quote
    printf("hell world\bcd\n");  // will print hello worlcd (\b moves cursor one space back, e.g. moves back to infront
                                 // of 'l' and prints 'c' there and goes on)
                                 //
    printf("%6d %d\n", 100, 50);
    printf("%6d\n", -6);
    printf("%6.1f\n", 6.2);
    printf("%x\n", 0x10f);

    // using symbolic constants
    printf("%s\n", NAME);
    printf("%d\n", MAX);
    return 0;
}
