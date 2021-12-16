// Program to demonstrate bottom to up execution
// of processes using fork() and wait()
#include <stdio.h>
#include <sys/wait.h> // for wait()
#include <unistd.h> // for fork()
int main()
{
    // creating 4 process using 2 fork calls
    // 1 parent : 2 child : 1 grand-child
    pid_t id1 = fork();
    pid_t id2 = fork();
    pid_t id3 = fork();

    // parent process
    if (id1 > 0 && id2 > 0 && id3 > 0) {
        wait(NULL);
        wait(NULL);
        wait(NULL);
        printf("Parent Terminated \n");
    }

    // 1st child
    else if (id1 == 0 && id2 > 0 && id3 > 0) {

        // sleep the process for 2 seconds
        // to ensure 2nd child executes first
        sleep(6);
        wait(NULL);
        printf("1st child Terminated\n");
    }

    else if (id1 > 0 && id2 == 0 && id3 > 0) {

        // sleep the process for 2 seconds
        // to ensure 2nd child executes first
        sleep(5);
        wait(NULL);
        printf("2nd child Terminated\n");
    }

    else if (id1 > 0 && id2 > 0 && id3 == 0) {

        // sleep the process for 2 seconds
        // to ensure 2nd child executes first
        sleep(4);
        wait(NULL);
        printf("3nd child Terminated\n");
    }

    else if (id1 == 0 && id2 == 0 && id3 > 0) {

        // sleep the process for 2 seconds
        // to ensure 2nd child executes first
        sleep(3);
        wait(NULL);
        printf("4nd child Terminated\n");
    }

    else if (id1 > 0 && id2 == 0 && id3 == 0) {

        // sleep the process for 2 seconds
        // to ensure 2nd child executes first
        sleep(2);
        wait(NULL);
        printf("5nd child Terminated\n");
    }

    // second child
    else if (id1 == 0 && id2 > 0 && id3 == 0) {
        // sleep the process for 1 second
        sleep(1);
        printf("6nd Child Terminated\n");
    }

    // grand child
    else {
        printf("7nd Child Terminated\n");
    }

    return 0;
}
