#include "syscall.h"
#include "stdio.h"

register void* current_sp __asm__("sp");

static inline long getpid() {
  long ret;
  asm volatile ("li a7, %1\n"
                "ecall\n"
                "mv %0, a0\n"
                : "+r" (ret) : "i" (SYS_GETPID));
  return ret;
}

static inline int exec(const char *path) {
  int ret;
  asm volatile ("li a7, %1\n"
                "mv a0, %2\n"
                "ecall\n"
                "mv %0, a0\n"
                : "+r" (ret) : "i" (SYS_EXEC), "r" (path));
  return ret;
}

int main() {
  while (1) {
    printf("[User] pid: %ld, sp is %lx\n", getpid(), current_sp);
    for (unsigned int i = 0; i < 0xFFFFFFF; i++);
    printf("[User] pid: %ld, exec\n", getpid());
    exec("getpid");
  }
  
  return 0;
}
