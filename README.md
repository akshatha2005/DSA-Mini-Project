File System Simulator (Terminal-Based)
A simple terminal-based File System Simulator built using C and an n-ary tree and linked list data structures.
The project mimics core operations of an operating system’s file explorer—allowing users to create/delete files or folders, navigate directories, and visualize the full directory hierarchy.

Features:
Create folders and files
Delete folders and files
Navigate into subdirectories (cd)
Move to parent directory
List contents of a directory (ls)
Display entire file system tree
Print current working directory

Data Structure:
n-Ary Tree
Linked list
Used to represent the hierarchical structure of a file system.
Each node stores:
Name
Type (file/folder)
List of children
Pointer to parent


Core Operations (ADT)
createNode(name, isFile)
addChild(parent, child)
removeChild(parent, name, type)
findChild(parent, name)
changeDirectory(current, name)
goToParent(current)
listDirectory(current)
displayTree(root)

How to Run:
gcc main.c fs.c -o filesystem
./filesystem

Team:
Team: CodeStruct
Aadya Arvind – PES2UG24CS008
Aanya K – PES2UG24CS011
Akshatha P – PES2UG24CS048
