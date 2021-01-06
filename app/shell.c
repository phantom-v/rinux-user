#include "syscall.h"
#include "stdio.h"
#include "string.h"

int fork_(void) {
	int pid;
	pid = fork();
	if(pid == -1)
		panic("panic fork");
	return pid;
}

void runcmd(char* cmd) {
	int i;
	for(i = 0; cmd[i] != '\0'; i++){
		if(cmd[i] == '\n'){
			cmd[i] = '\0';
			break;
		}
	}
	exec(cmd);
	fprintf(2,"exec %s failed\n",cmd);
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

        /*
	while((fd = open("console", O_RDWR)) >= 0){
		if(fd >= 3){
			close(fd);
			break;
		}
	}
        */
	
	while(getcmd(buf,sizeof(buf)) >= 0) {
                fprintf(2, "%s\n", buf);
		if(fork_() == 0)
			runcmd(buf);
		wait();
	}

	exit(0);
}