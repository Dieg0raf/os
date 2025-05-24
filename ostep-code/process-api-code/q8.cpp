#include <fcntl.h>
#include <unistd.h>

#include <cerrno>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    int fides[2];
    pipe(fides);
    pid_t child_proc_1 = fork();
    if (child_proc_1 < 0) {
        cerr << errno << endl;
        return 1;
    } else if (child_proc_1 == 0) {
        // Child Process
        close(fides[0]);
        dup2(fides[1], STDOUT_FILENO);
        close(fides[1]);
        const char* msg = "Hello, World!\n";
        write(STDOUT_FILENO, msg, strlen(msg));
        return 0;
    }

    pid_t child_proc_2 = fork();
    if (child_proc_2 < 0) {
        cerr << errno << endl;
        return 1;
    } else if (child_proc_2 == 0) {
        // Child Process
        close(fides[1]);
        char buf[1024];
        int rc = 0;
        while ((rc = read(fides[0], buf, sizeof(buf))) > 0) {
            write(STDOUT_FILENO, buf, rc);
        }
        return 0;
    }

    close(fides[0]);
    close(fides[1]);
    wait(NULL);
    wait(NULL);
    return 0;
}
