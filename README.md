<p align="center">
  <img width="128" align="center" src="/assets/logo.svg">
</p>

# PADS

PADS, short for Preprocessor Abstracted Data Structures, is a personal project that aims to recreate popular data structures for the C programming language. The project includes single header libraries for each structure that use the preprocessor for data type abstraction.

PADS data structures are each divided into at least three modes with support for:

- Infinitely expandable structure via memory reallocation
- Finite structure of variable allocated size
- Finite predefined size array structure using preprocessor

## Prerequisite
C compiler that at least supports the **C99 standard**, for example:
- [GNU Compiler Collection (gcc)](https://gcc.gnu.org), 
- [Microsoft Visual C++ (MSVC)](https://visualstudio.microsoft.com/vs/features/cplusplus/),
- [Clang](https://clang.llvm.org)

## Download
- Go to the list below and click on the link with **Available** data structures.
- Click on the specific ```*.h``` file.
- Press ```Ctrl + Shift + s``` to download the header.

> [!WARNING]
> Only one header can be included **per executable** file. If a separate header file includes stack.h, then no other file with the 'separate header' can use stack.h. The header will generate an **error** if they collide.

## **List of Data Structures:**

### [SEQUENTIAL](https://github.com/TheGAzed/pads/blob/main/source/sequential)
- [STACK](https://github.com/TheGAzed/pads/blob/main/source/sequential/stack)
- [QUEUE](https://github.com/TheGAzed/pads/blob/main/source/sequential/queue)
- [DEQUE](https://github.com/TheGAzed/pads/blob/main/source/sequential/deque)

### [LIST](https://github.com/TheGAzed/pads/blob/main/source/list)
- [STRAIGHT LIST](https://github.com/TheGAzed/pads/blob/main/source/list/straight_list)
- [CIRCULAR LIST](https://github.com/TheGAzed/pads/blob/main/source/list/circular_list)
- [DOUBLE LIST](https://github.com/TheGAzed/pads/blob/main/source/list/double_list)

### **In Progress:**

- [BINARY SET](https://github.com/TheGAzed/pads/blob/main/source/set/binary_set)
- [MATRIX GRAPH](https://github.com/TheGAzed/pads/blob/main/source/graph/matrix_graph)
