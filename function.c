#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

void display_prompt(void) {
    printf("#cisfun$ ");
}

int main(void) {
    char buffer[BUFFER_SIZE];

    while (1) {
        display_prompt();

        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            // Handle end of file (Ctrl+D)
            printf("\n");
            break;
        }

        // Remove the newline character
        buffer[strcspn(buffer, "\n")] = '\0';

        // Fork a new process
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            // Child process
            if (execve(buffer, NULL, NULL) == -1) {
                // Handle command not found
                perror(buffer);
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process
            // Wait for the child to finish
            wait(NULL);
        }
    }

    printf("\n");
    return 0;
}
