#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024

void display_prompt(void) {
    printf(":) ");
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

        // Check if the command is empty
        if (buffer[0] == '\0') {
            continue;
        }

        // Fork a new process
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            // Child process
            char *args[32]; // Adjust the array size accordingly
            char *token = strtok(buffer, " ");
            int i = 0;

            while (token != NULL && i < 31) {
                args[i] = token;
                token = strtok(NULL, " ");
                i++;
            }

            args[i] = NULL; // Null-terminate the array

            // Check if the command exists in the PATH
            if (execvp(args[0], args) == -1) {
                // Handle command not found
                perror(args[0]);
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
