#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void handler(int signum) {
    printf("Caught signal %d (SIGFPE) - divide by zero error!\n", signum);
    exit(1);
}

int main() {
    signal(SIGFPE, handler);
    int a = 5;
    int b = 0;
    int c = a / b;  // Still traps, but now we handle it
    printf("Result: %d\n", c);
    return 0;
}


