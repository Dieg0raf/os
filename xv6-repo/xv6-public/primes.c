#include "types.h"
#include "stat.h"
#include "user.h"

void seive(int readFd) {
  int primeNum;
  if (read(readFd, &primeNum, sizeof(int)) != sizeof(int)) { // reading in prime number first
    close(readFd);
    exit();
  }

  printf(1, "prime %d\n", primeNum);

  int fd[2];
  int n;
  pipe(fd);

  while(read(readFd, &n, sizeof(int)) == sizeof(int)) {
    if (n % primeNum != 0) {
      if (write(fd[1], &n, sizeof(int)) < 0) {
        printf(2, "primes: error occured sending\n");
      }
    }
  }

  close(fd[1]);
  if (fork() == 0) {
    seive(fd[0]);
    close(fd[0]);
  } else {
    close(fd[0]);
    wait();
  }
}

int main(int argc, char *argv[]) {
  int fd[2];
  pipe(fd);
  
  // sending nums down first pipe
  for(int i = 2; i <= 35; i++){
    if (write(fd[1], &i, sizeof(int)) < 0) {
      printf(2, "primes: error occured sending\n");
    }
  }
  close(fd[1]);

  if (fork() == 0) {
    seive(fd[0]);
    close(fd[0]);
  } else {
    close(fd[0]);
    wait();
  }

  exit();
}
