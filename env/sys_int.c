#include "syscall.h"
#include "stdio.h"
#include "user.h"

int fork(void)
{
	long ret;
	asm volatile (	"li a7, %1\n"
					"mv a0, zero\n"
					"mv a1, zero\n"
					"ecall \n"
					"mv %0, a0\n"
					: "+r" (ret)
					: "i" (SYS_FORK)
					);
	return ret;
}
int exit(int stat)
{
	long ret;
	asm volatile (	"li a7, %2\n"
					"mv a0, %1\n"
					"ecall\n"
					"mv %0, a0\n"
					: "+r" (ret)
					: "r" (stat), "i" (SYS_EXIT)
					);
	return ret;
}
int wait()
{
	long ret;
	// wait4(-1,NULL,0,NULL);
	asm volatile (	"li a7, %1\n"
					"li a0, -1\n"
					"mv a1, zero\n"
					"mv a2, zero\n"
					"mv a3, zero\n"
					"ecall\n"
					"mv %0, a0\n"
					: "+r" (ret)
					: "i" (SYS_WAIT)
					);
	return ret;
}
int exec(char* path)
{
	long ret;
	asm volatile (	"li a7, %2\n"
					"mv a0, %1\n"
					"mv a1, zero\n"
					"mv a2, zero\n"
					"ecall\n"
					"mv %0, a0\n"
					: "+r" (ret)
					: "r" (path), "i" (SYS_EXEC)
					);
	return ret;
}

int open(const char* name, int pri)
{
	long ret;
	asm volatile (	"li a7, %3\n"
					"mv a0, %2\n"
					"mv a1, %1\n"
					"ecall\n"
					"mv %0, a0\n"
					: "+r" (ret)
					: "r" (pri), "r" (name), "i" (SYS_OPEN)
					);
	return ret;
}
int read(int fd, void* buf, int nbuf)
{
	long ret;
	asm volatile (	"li a7, %4\n"
					"mv a0, %3\n"
					"mv a1, %2\n"
					"mv a2, %1\n"
					"ecall\n"
					"mv %0, a0\n"
					: "+r" (ret)
					: "r" (nbuf), "r" (buf), "r" (fd),
					"i" (SYS_READ)
					);
	return ret;
}
int write(int fd, const void* buf, int nbuf)
{
	long ret;
	asm volatile (	"li a7, %4\n"
					"mv a0, %3\n"
					"mv a1, %2\n"
					"mv a2, %1\n"
					"ecall\n"
					"mv %0, a0\n"
					: "+r" (ret)
					: "r" (nbuf), "r" (buf), "r" (fd),
					"i" (SYS_WRITE)
					);
	return ret;
}
int close(int fd)
{
	long ret;
	asm volatile (	"li a7, %2\n"
					"mv a0, %1\n"
					"ecall\n"
					"mv %0, a0\n"
					: "+r" (ret)
					: "r" (fd), "i" (SYS_CLOSE)
					);
	return ret;
}
int getpid(void)
{
  long ret;
  asm volatile ("li a7, %1\n"
                "ecall\n"
                "mv %0, a0\n"
                : "+r" (ret) : "i" (SYS_GETPID));
  return ret;
}
