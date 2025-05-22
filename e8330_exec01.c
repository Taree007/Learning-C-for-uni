#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    pid_t pid = getpid();
    pid_t ppid = getppid();
    
    printf("Process PID: %d, Parent PID: %d\n", pid, ppid);
    
    if (argc > 1) {
        // If argument exists, print it
        printf("Received argument: %s\n", argv[1]);
    } else {
        // No argument, self-execute with one
        printf("No argument provided, self-executing with argument\n");
        
        char arg[20];
        sprintf(arg, "%d", 42);  // Example argument
        
        // Execute self with the argument
		//path, name, pats argumentas, null pazymi argumentu saraso gala
        if (execl(argv[0], argv[0], arg, NULL) == -1) {
            perror("execl failed");
            exit(1);
        }
        
        // This code will never execute if exec succeeds
        printf("This will never be printed if exec succeeds\n");
    }
    
    return 0;
}