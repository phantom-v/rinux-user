#include "types.h"

// fcntl.h
#define O_RDONLY  0x000
#define O_WRONLY  0x001
#define O_RDWR    0x002
#define O_CREATE  0x200
#define O_TRUNC   0x400

// syscall
int fork(void);
int exit(int);
int wait(void);
int exec(char*);	// modified

int open(const char*, int);
int read(int, void*, int);
int write(int, const void*, int);
int close(int);

int getpid(void);
// ulib.c
int fprintf(int, const char*, ...);
char* gets(char*, int max);
void* memset(void*, int, uint);
