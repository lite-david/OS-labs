#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>

int main(){

	int i,cid,j,status = 0,level = 0;
	key_t key;
	pid_t npid;
	if((key = ftok("process_tree.c", 0xff)) == -1 ){
		perror("ftok");
		exit(1);
	} 	
	int id;
	if((id =  shmget(key, sizeof(int) * 100, 0644 | IPC_CREAT)) == -1 ) {
		perror("shmget");
		exit(1);
	}
	int *shared_memory = (int *)shmat(id, NULL, 0);
	*shared_memory = 1;
	pid_t rpid = getpid();

	for(i = 0;i<3;i++){
		cid = fork();
		if(cid == 0)
			level+=1;

		npid = getpid();

		if(cid == 0){
			int *shared_memory = (int *)shmat(id, NULL, 0);
			j = *shared_memory;
			*(shared_memory + j) = getpid();
			*(shared_memory + j+1) = getppid();
			*shared_memory = j+2;
		}
		if(rpid == getpid())
			wait(NULL);
	}
	
	if(rpid == getpid()){
		printf("%d \n",*(shared_memory));
		for(i = 1;i<15;i+=2){
			printf("Parent: %d \n",*(shared_memory+i));
			printf("Child: %d \n",*(shared_memory+i+1));
		}
	}
	

	shmdt(shared_memory);
	//wait unitl all processes have detached from shared memory
	wait(&status);

	//to delete the shared memory
	shmctl(id,IPC_RMID,NULL);
	return 0;
}