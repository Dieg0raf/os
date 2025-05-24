#include <fcntl.h>
#include <unistd.h>

#include <cerrno>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    int fd = open("q2-test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    pid_t child_proc = fork();
    if (child_proc < 0 || fd < 0) {
        cerr << errno << endl;
        return 1;
    } else if (child_proc == 0) {
        // Child Process
        char buf[] = "Child Process wrote this\n";
        if (write(fd, buf, sizeof(buf)) < 0) {
            cerr << errno << endl;
            return 1;
        }
        cout << "Child " << getpid() << " Process variable fd: " << fd << endl;

    } else {
        // Parent Process
        char buf[] = "Parent Process wrote this\n";
        if (write(fd, buf, sizeof(buf)) < 0) {
            cerr << errno << endl;
            return 1;
        }
        cout << "Parent " << getpid() << " Process variable fd: " << fd << endl;
    }
    return 0;
}
