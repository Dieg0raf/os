#include "types.h"
#include "stat.h"
#include "user.h"

int 
main(int argc, char *argv[]) {
  printf(1, "=== System Information ===\n");
  printf(1, "My process ID: %d\n", getpid());
  printf(1, "Hello from xv6!\n");
  exit();
}
