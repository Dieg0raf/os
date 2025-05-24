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

        char* args[4];
        args[0] = strdup("/bin/ls");  // strdup returns the pointer of the string allocated in memory
        args[1] = strdup("-l");
        args[2] = strdup(".");
        args[3] = NULL;

        // using **execv()** (v - for (v)ector(array))
        if (execv(args[0], args) < 0) {
            cerr << errno << endl;
            return 1;
        }

        // using **execl()** (l - for (l)ist)
        // if (execl(args[0], args[0], args[1], args[2], args[3]) < 0) {
        //     perror("Error occured during execl");
        // }

        // using *execle** (e - for (e)nvironment)
        // const char* newenv[] = {"USER=custom_user", "PATH=/custom/bin", "HOME=/custom/home", NULL};
        // if (execle("/usr/bin/env", "env", NULL, newenv) < 0) {
        //     perror("Error occurred during execle");
        // }
        //
    } else {
        // Parent Process
        pid_t childProcess = wait(NULL);
        cout << "Finished waiting for PID: " << childProcess << endl;
    }
    return 0;
}
