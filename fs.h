#ifndef FS_H
#define FS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a file or folder
typedef struct FSNode {
    char name[50];
    int isFile;                  // 0 = folder, 1 = file
    struct FSNode *parent;       // Pointer to parent folder
    struct FSNode *child;        // Pointer to first item inside 
    struct FSNode *sibling;      // Pointer to next item in the same folder
} FSNode;

// Function declarations
FSNode* createNode(char *name, int isFile);
void addChild(FSNode *parent, FSNode *child);
int nameExists(FSNode *parent, char *name);
FSNode* findChild(FSNode *parent, char *name);
void removeChild(FSNode *parent, char *name, int isFileOnly);
void listDirectory(FSNode *current);
void changeDirectory(FSNode **current, char *name);
void goToParent(FSNode **current);
void printWorkingDirectory(FSNode *current);
void displayTree(FSNode *root, int depth);
void freeFileSystem(FSNode *root);

#endif
