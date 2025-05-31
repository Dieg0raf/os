#include <iostream>
#include <sys/time.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) {
  struct timeval start, end;
  // time the sys call
  gettimeofday(&start, nullptr);
  getpid();
  getpid();
  gettimeofday(&end, nullptr);

  long seconds = end.tv_sec - start.tv_sec;
  long microseconds = end.tv_usec - start.tv_usec;
  double elapsed = seconds * 1e6 + microseconds;
  cout << "getpid() took " << elapsed << " microseconds \n";

  return 0;
}
