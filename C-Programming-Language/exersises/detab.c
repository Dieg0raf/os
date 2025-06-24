#include <stdio.h>

// Write a program detab that replaces tabs in the input with the proper number of blanks to space to the next tab stop.
// Asssume a fixed set of tabs stops, say every n columns. Should n be a variable or a symbolic parameter?

// 1 % 8 = 1 --> 8 - 1 = 7
// 8 % 8 = 0 --> 8 - 0 = 8
// 9 % 8 = 1 --> 8 - 1 = 7
// 13 % 8 = 5 --> 8 - 5 = 3

const int TAB_STOP_OCUR = 8;

int main(int argc, char* argv[]) {
    int c, j;
    int charIndex = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            for (j = 0; j < TAB_STOP_OCUR - (charIndex % TAB_STOP_OCUR); j++) {
                printf(" ");
            }
            charIndex += j;
        } else {
            putchar(c);
            charIndex++;
            if (c == '\n') {
                charIndex = 0;
            }
        }
    }
    return 0;
}
