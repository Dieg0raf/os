#include <unistd.h>

#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    int rc = fork();
    if (rc < 0) {
        cerr << "fork failed" << endl;
    } else if (rc == 0) {  // child process
        cout << "Child process: (" << (int)getpid() << ")" << endl;
        char *chargs[3];
        chargs[0] = strdup("/usr/bin/wc");
        chargs[1] = strdup("test.cpp");
        chargs[2] = NULL;
        execv(chargs[0], chargs);
        cout << "execv failed" << endl;
    } else {                       // parent process
        int wait_rc = wait(NULL);  // wait for child process to finish
        cout << "Parent process: (" << (int)getpid() << ")" << endl;
        cout << "Child process finished with PID: " << wait_rc << endl;
    }

    // should only be printed by the parent process only
    cout << "printed by: (" << (int)getpid() << ")" << endl;
    return 0;
}
