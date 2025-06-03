#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf(1, "sleep: need integer argument\n");
    exit();
  }
  int sleeptime = atoi(argv[1]);
  if (sleeptime < 0 || sleeptime > 10) {
      printf(1, "sleep: time is to low or to high\n");
      exit();
  }
  printf(1, "About to sleep\n");
  sleep(sleeptime * 100); // times by 100 because sleep takes takes in ms (500ms = 5 seconds)
  printf(1, "After sleeping\n");
  exit();
}
