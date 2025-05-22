#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    
    printf("Parent process (PID: %d) starting\n", getpid());
    
    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child process (PID: %d) starting and will exit soon\n", getpid());
        exit(0);  // Child terminates immediately
    } else {
        // Parent process
        printf("Parent (PID: %d) created child with PID: %d\n", getpid(), pid);
        printf("Parent sleeping for 30 seconds - child becomes zombie\n");
        printf("You can run 'ps -l' to see zombie process\n");
        sleep(30);  // Sleep without calling wait() - child becomes zombie
        
        // Now collect the zombie
        int status;
        pid_t child_pid = wait(&status);
        printf("Parent collected zombie child (PID: %d), status: %d\n", child_pid, status);
    }
    
    return 0;
}