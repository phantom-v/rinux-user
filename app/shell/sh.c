#include "user.h"

int fork_(void);
void panic(char*);
void runcmd(char* cmd);
int getcmd(char *buf, int nbuf);

int main(void)
{
	static char buf[100];
	int fd;
	long pid = getpid();
	while(getcmd(buf,sizeof(buf)) >= 0) {
		if(fork_() == 0)
		{
			runcmd(buf);
		}
		wait();
	}

	exit(0);

}

int fork_(void)
{
	int pid;
	pid = fork();
	if(pid == -1)
		panic("fork");
	return pid;
}

void panic(char* s)
{
	fprintf(2,"%s\n",s);
	exit(1);
}

void runcmd(char* cmd)
{
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

int getcmd(char *buf, int nbuf)
{
	fprintf(2, "$ ");
	memset(buf, 0, nbuf);
	gets(buf, nbuf);
	if(buf[0] == 0)
		return -1;
	return 0;
}
