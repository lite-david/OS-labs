#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	pid_t pid;
	int i;
	char buffchild[100];
	char buffparent[100];
	i = fork();
	if(i == 0){
		sprintf(buffchild,"child \n");
		write(1,buffchild,strlen(buffchild));
		return 0;
		//sleep(0.4);
	}
	else if(i> 0){
		sprintf(buffparent,"parent \n");
		write(1,buffparent,strlen(buffparent));
		return 0;
		//sleep(0.4);
	}
}