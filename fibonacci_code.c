#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>

// Function to generate and print Fibonacci sequence
void fibonacci(int n) {
    int a = 0, b = 1, next;
    printf("Fibonacci sequence:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", a);  // Print current term
        next = a + b;      // Calculate next term
        a = b;
        b = next;
    }
    printf("\n");
}

int main() {
    pid_t pid;  // Process ID variable
    int n;      // Number of Fibonacci terms

    // Ask user for input
    printf("Enter the number of Fibonacci terms: ");
    scanf("%d", &n);

    // Create a child process using fork()
    pid = fork();

    // Check if fork() failed
    if (pid < 0) {
        printf("Fork failed.\n");
        return 1;  // Exit with error
    }
    // Child process code
    else if (pid == 0) {
        printf("Child process started (PID: %d)\n", getpid());       // Show child PID
        printf("Parent PID from child process: %d\n", getppid());    // Show parent PID
        fibonacci(n);  // Call Fibonacci function
        printf("Child process exiting.\n");
    }
    // Parent process code
    else {
        printf("Parent process started (PID: %d)\n", getpid());  // Show parent PID
        wait(NULL);  // Parent waits until child process is done
        printf("Parent process waited for child (PID: %d) to complete.\n", pid);
    }

    return 0;
}