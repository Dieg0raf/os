#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
  int p[2], p2[2], bytesRead;
  const char* pingmsg = "ping";
  const char* pongmsg = "pong";
  char buf[1024];
  
  // initalize pipes
  pipe(p); 
  pipe(p2); 

  if (argc > 1) {
    printf(1, "pingpong: to many arguments\n");
  }

  int childpid = fork();
  if (childpid == 0) {
    // child process
    close(p[1]); 
    close(p2[0]);
    while ((bytesRead = read(p[0], buf, sizeof(buf))) > 0) {
      printf(1, "received ping\n");
    }

    if (bytesRead != 0) {
      printf(2, "Error occurred\n");
      exit();
    }
    
    write(p2[1], pongmsg, 5);
    close(p2[1]);
    close(p[0]);

  } else {
    // parent process (closed automatically since they are not in use)
    close(p[0]);
    close(p2[1]);

    write(p[1], pingmsg, 5); // write to child (through pipe write end)
    close(p[1]); // close automatically (reasoning: child process gets stuck in while loop waiting for more data if writing end of pipe is still open - causing an infinite wait)
    // closing the write end of the pipe tells the read() there won't be any more data

    wait();
    while ((bytesRead = read(p2[0], buf, sizeof(buf))) > 0) {
      printf(1, "received pong\n");
    }

    if (bytesRead != 0) {
      printf(2, "Error occurred\n");
      exit();
    }
    close(p2[0]);
  }

  exit();
}
