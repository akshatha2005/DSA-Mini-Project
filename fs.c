#include "fs.h"

// Create a new node (file/folder)
FSNode* createNode(char *name, int isFile) {
    FSNode *node = malloc(sizeof(FSNode));
    strcpy(node->name, name);
    node->isFile = isFile;
    node->parent = NULL;
    node->child = NULL;
    node->sibling = NULL;
    return node;
}

// Check if a child with the same name already exists
int nameExists(FSNode *parent, char *name) {
    FSNode *temp = parent->child;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0)
            return 1;
        temp = temp->sibling;
    }
    return 0;
}

// Add a child (file/folder) inside a directory
void addChild(FSNode *parent, FSNode *child) {
    if (nameExists(parent, child->name)) {
        printf("Error: '%s' already exists in this directory.\n", child->name);
        free(child);
        return;
    }

    if (parent->child == NULL) {
        parent->child = child;
    } else {
        FSNode *temp = parent->child;
        while (temp->sibling != NULL)
            temp = temp->sibling;
        temp->sibling = child;
    }
    child->parent = parent;
    printf("%s created successfully.\n", child->name);
}

// Find a file or folder by name inside the current directory
FSNode* findChild(FSNode *parent, char *name) {
    FSNode *temp = parent->child;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0)
            return temp;
        temp = temp->sibling;
    }
    return NULL;
}

// Remove a file or folder from the current directory
void removeChild(FSNode *parent, char *name, int isFileOnly) {
    if (strcmp(parent->name, "root") == 0 && parent->parent == NULL && strcmp(name, "root") == 0) {
        printf("Error: Cannot delete the root directory.\n");
        return;
    }

    FSNode *temp = parent->child;
    FSNode *prev = NULL;

    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            if (isFileOnly && !temp->isFile) {
                printf("Error: '%s' is a folder, not a file. Use 'rd' to remove directories.\n", name);
                return;
            }
            if (!isFileOnly && temp->isFile) {
                printf("Error: '%s' is a file, not a folder. Use 'del' to delete files.\n", name);
                return;
            }

            if (prev == NULL)
                parent->child = temp->sibling;
            else
                prev->sibling = temp->sibling;

            freeFileSystem(temp);
            printf("%s deleted successfully.\n", name);
            return;
        }
        prev = temp;
        temp = temp->sibling;
    }
    printf("Error: '%s' not found.\n", name);
}

// List contents of the current directory
void listDirectory(FSNode *current) {
    FSNode *temp = current->child;
    if (temp == NULL) {
        printf("(empty)\n");
        return;
    }

    while (temp != NULL) {
        if (temp->isFile)
            printf("       %s\n", temp->name);
        else
            printf("<DIR>  %s\n", temp->name);
        temp = temp->sibling;
    }
}

// Change directory into a subfolder
void changeDirectory(FSNode **current, char *name) {
    FSNode *temp = findChild(*current, name);
    if (temp != NULL && !temp->isFile) {
        *current = temp;
    } else {
        printf("Error: Folder '%s' not found.\n", name);
    }
}

// Move back to parent directory
void goToParent(FSNode **current) {
    if ((*current)->parent != NULL)
        *current = (*current)->parent;
    else
        printf("Already at root directory.\n");
}

// Print the current working directory path
void printWorkingDirectory(FSNode *current) {
    if (current->parent != NULL) {
        printWorkingDirectory(current->parent);
        printf("\\%s", current->name);
    } else {
        printf("C:");
    }
}

// Display the full tree structure (recursively)
void displayTree(FSNode *root, int depth) {
    for (int i = 0; i < depth; i++)
        printf("    ");
    printf("%s%s\n", root->name, root->isFile ? "" : "/");

    FSNode *temp = root->child;
    while (temp != NULL) {
        displayTree(temp, depth + 1);
        temp = temp->sibling;
    }
}

// Free memory recursively
void freeFileSystem(FSNode *root) {
    if (root == NULL) return;
    FSNode *temp = root->child;
    while (temp != NULL) {
        FSNode *next = temp->sibling;
        freeFileSystem(temp);
        temp = next;
    }
    free(root);
}
