#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>

int main(int argc,char *argv){
	int i,cpid;
	pid_t pid,ppid;
	int status,mon;

	key_t key = ftok("~/Study/OS/lab3/lab5.c", 0xff);
	
	for(i = 0;i<3;i++){
		cpid = fork();
		pid = getpid();

		printf(" level is: %d proc id is %d\n",i,pid);
		mon = wait(&status);
		if(i == 0 && mon!=-1){
			printf("2 grand children ended \n");
		}
	}
	return 0;
}