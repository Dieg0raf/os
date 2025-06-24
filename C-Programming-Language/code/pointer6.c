#include <stdio.h>

int main(int argc, char* argv[]) {
    printf("character \'0\': %d\n", '0');
    printf("character \'9\': %d\n", '9');
    printf("character \'9 - 0\': %c\n", '9' - '0');
    int c = getchar();
    printf("You entered: %d\n", c);
    putchar(c);
    return 0;
}
