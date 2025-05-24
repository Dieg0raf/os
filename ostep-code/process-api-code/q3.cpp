#include <fcntl.h>
#include <unistd.h>

#include <cerrno>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    int hasWritten = false;
    pid_t child_proc = fork();
    if (child_proc < 0) {
        cerr << errno << endl;
        return 1;
    } else if (child_proc == 0) {
        // Child Process
        cout << "hello" << endl;
        hasWritten = true;

    } else {
        // Parent Process
        pid_t childProcess = wait(NULL);
        cout << "Finished waiting for PID: " << childProcess << endl;
        cout << "bye" << endl;
    }
    return 0;
}
