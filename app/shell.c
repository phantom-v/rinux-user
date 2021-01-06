#include "syscall.h"
#include "stdio.h"
#include "string.h"

int fork_(void) {
	int pid;
	pid = fork();
	printf("after fork %d\n", pid);
	if(pid < 0)
		panic("panic fork");
	return pid;
}

void runcmd(char* cmd) {
	exec(cmd);
	fprintf(2, "exec %s failed\n", cmd);
	exit(0);
}

int getcmd(char *buf, int nbuf) {
	fprintf(2, "$ ");
	memset(buf, 0, nbuf);
	gets(buf, nbuf);
	if(buf[0] == 0)
		return -1;
	return 0;
}

int main(void) {
	static char buf[100];
	int fd;
	
	while(getcmd(buf,sizeof(buf)) >= 0) {
        fprintf(2, "%s\n", buf);

		if (strcmp(buf, "hello") == 0) {
			if(fork_() == 0)
				runcmd(buf);
			wait();
		}
		else {
			printf("Invalid command %s\n", buf);
		}
		

	}

	exit(0);
}