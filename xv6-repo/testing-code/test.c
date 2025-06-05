#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
  char buffer[] = "hello world";
  memmove(buffer + 5, buffer, 5);
  buffer[11] = '\0';
  printf("%s\n", buffer);
  return 0;
}
