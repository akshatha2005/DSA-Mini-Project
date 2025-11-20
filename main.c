#include "fs.h"

int main() {
    char command[100], name[50];
    FSNode *root = createNode("root", 0);
    FSNode *current = root;

    printf("File System Simulator\n");
    printf("Type 'help' to see available commands.\n\n");

    while (1) {
        printWorkingDirectory(current);
        printf("> ");
        fgets(command, sizeof(command), stdin);

        command[strcspn(command, "\n")] = '\0'; // remove newline

        if (strncmp(command, "md ", 3) == 0) {
            strcpy(name, command + 3);
            if (strlen(name) == 0) {
                printf("Error: Folder name cannot be empty.\n");
                continue;
            }
            FSNode *newFolder = createNode(name, 0);
            addChild(current, newFolder);
        }

        else if (strncmp(command, "type nul > ", 11) == 0) {
            strcpy(name, command + 11);
            if (strlen(name) == 0) {
                printf("Error: File name cannot be empty.\n");
                continue;
            }
            FSNode *newFile = createNode(name, 1);
            addChild(current, newFile);
        }

        else if (strcmp(command, "dir") == 0) {
            listDirectory(current);
        }

        else if (strcmp(command, "cd ..") == 0) {
            goToParent(&current);
        }

        else if (strncmp(command, "cd ", 3) == 0) {
            strcpy(name, command + 3);
            changeDirectory(&current, name);
        }

        else if (strcmp(command, "cd") == 0) {
            printf("Current Directory: ");
            printWorkingDirectory(current);
            printf("\n");
        }

        else if (strncmp(command, "del ", 4) == 0) {
            strcpy(name, command + 4);
            removeChild(current, name, 1);
        }

        else if (strncmp(command, "rd ", 3) == 0) {
            strcpy(name, command + 3);
            removeChild(current, name, 0);
        }

        else if (strcmp(command, "tree") == 0) {
            printf("C:\\\n");
            displayTree(root, 1);
        }

        else if (strcmp(command, "help") == 0) {
            printf("\nAvailable commands:\n");
            printf("  md <folder>        - Create folder\n");
            printf("  type nul > <file>  - Create file\n");
            printf("  dir                - List contents\n");
            printf("  cd <folder>        - Change directory\n");
            printf("  cd ..              - Move to parent\n");
            printf("  cd                 - Show current directory\n");
            printf("  del <file>         - Delete file\n");
            printf("  rd <folder>        - Delete folder\n");
            printf("  tree               - Show full structure\n");
            printf("  exit               - Quit program\n\n");
        }

        else if (strcmp(command, "exit") == 0) {
            printf("Exiting and freeing memory...\n");
            freeFileSystem(root);
            break;
        }

        else if (strcmp(command, "") == 0) {
            continue;
        }

        else {
            printf("Unknown command. Type 'help' for list.\n");
        }
    }

    return 0;
}
