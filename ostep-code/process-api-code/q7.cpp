#include <fcntl.h>
#include <unistd.h>

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
        close(STDOUT_FILENO);             // closes stdout fd for the child process
        cout << "Hello, World!" << endl;  // doesn't print anything
    } else {
        // Parent Process
        cout << "Parent process" << endl;
    }
    return 0;
}
