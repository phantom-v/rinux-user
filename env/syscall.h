#pragma once
/*
 * Number from:
 * /include/uapi/asm-generic/unistd.h
 * Function from:
 * /include/linux/syscalls.h
 */

#define SYS_FORK 220
/*
 * long sys_clone3(struct clone_args __user *uargs, size_t size);
 */
#define SYS_EXEC 221
/*
 * long sys_execve(const char __user *filename,
 * 		const char __user *const __user *argv,
 * 		const char __user *const __user *envp);
 */
#define SYS_EXIT 93
/*
 * long sys_exit(int error_code);
 */
#define SYS_WAIT 260
/*
 * long sys_wait4(pid_t pid, int __user *stat_addr,
 * 				int options, struct rusage __user *ru);
 */
#define SYS_OPEN 56
/*
 * long sys_openat(int dfd, const char __user *filename, int flags,
 * 			   umode_t mode);
 */
#define SYS_CLOSE 57
/*
 * long sys_close(unsigned int fd);
 */
#define SYS_READ 63
/*
 * long sys_read(unsigned int fd, char __user *buf, size_t count);
 */
#define SYS_WRITE 64
/*
 * long sys_write(unsigned int fd, const char __user *buf,
 * 			  size_t count);
 */
#define SYS_GETPID 172
/*
 * long sys_getpid(void);
 */
