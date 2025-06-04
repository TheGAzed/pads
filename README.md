<p align="center">
  <img width="128" align="center" src="/assets/logo.svg">
</p>

# PADS

PADS, short for Preprocessor Abstracted Data Structures, is a personal project that aims to recreate popular data structures for the C programming language. The project includes single header libraries for each structure that use the preprocessor for data type abstraction.

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
> Only one specific PADS header can be included **per executable** file. If a separate header file includes it, then no other file with the 'separate header' can use it. The headers will generate an **error** if they collide.

## **List of Data Structures:**

### [SEQUENTIAL](https://github.com/TheGAzed/pads/blob/main/source/sequence)
- STACK
- QUEUE
- DEQUE

### [PRIORITY](https://github.com/TheGAzed/pads/blob/main/source/priority)
- BINARY HEAP

### [LIST](https://github.com/TheGAzed/pads/blob/main/source/list)
- STRAIGHT LIST
- CIRCULAR LIST
- DOUBLE LIST

### [SET](https://github.com/TheGAzed/pads/blob/main/source/set)
- BINARY SET
- BITWISE SET
