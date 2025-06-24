#include <stdio.h>

int main(int argc, char* argv[]) {
    printf("EOF is %d\n", EOF);  // EOF is equal to -1
    int a;
    printf("return value of expression: %d\n", (a = -50));

    int c = getchar();
    putchar(c);
    // while ((c = getchar()) != EOF) {
    //     // putchar(c);
    //     printf("character num: %d\n", c);
    // }
    //
    // long nc = 0;
    // printf("size of int: %zu\n", sizeof(int));
    // printf("size of long: %zu\n", sizeof(long));
    // while (getchar() != EOF) ++nc;
    // printf("%ld characters read so far\n", nc);

    // double nc;
    // for (nc = 0; getchar() != EOF; ++nc);
    // printf("%.2f characters read so far\n", nc);
    return 0;
}
