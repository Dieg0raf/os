#include <unistd.h>

#include <cerrno>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    int x = 100;
    pid_t child_proc = fork();
    if (child_proc < 0) {
        cerr << errno << endl;
        return 1;
    } else if (child_proc == 0) {
        // Child Process
        x = 5;
        cout << "Child " << getpid() << " Process variable x: " << x << endl;

    } else {
        // Parent Process
        x = 50;
        cout << "Parent " << getpid() << " Process variable x: " << x << endl;
    }
    return 0;
}
