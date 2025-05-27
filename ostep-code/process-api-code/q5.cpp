#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

#include <cerrno>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    pid_t child_proc = fork();
    if (child_proc < 0) {
        cerr << errno << endl;
        return 1;
    } else if (child_proc == 0) {
        // Child Process
        cout << "hello" << endl;
        // Returns -1 (The calling process has no existing unwaited-for child process)
        // pid_t childProcess = wait(NULL);
        // cout << "Finished waiting for PID in child: " << childProcess << endl;

    } else {
        // Parent Process
        pid_t childProcess = wait(NULL);
        cout << "Finished waiting for PID: " << childProcess << endl;
        cout << "bye" << endl;
    }
    return 0;
}
