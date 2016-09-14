#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>	

int main(){

	pid_t rpid,npid;
	rpid = getpid();
	//key_t key = ftok("sharemem_parentgrandchild.c", 0xff);
	//int id = shmget(key, sizeof(int) * 10, 0644 | IPC_CREAT);
	key_t key;
	if((key = ftok("sharemem_parentgrandchild.c", 0xff)) == -1 ){
		perror("ftok");
		exit(1);
	} 	
	int id;
	if((id =  shmget(key, sizeof(int) * 10, 0644 | IPC_CREAT)) == -1 ) {
		perror("shmget");
		exit(1);
	}

	int level = 0,cid,i,clear_mem = 0,j,status = 0,counti =0;
	int *shared_memory = (int *) shmat(id, NULL, 0);

	for(i = 0;i<3;i++){
		//wait(NULL);
		cid = fork();
		if(cid == 0)
			level+=1;

		npid = getpid();

		if(i == 2 && rpid != npid){
			printf("%d %d \n",level,npid);
			int *shared_memory = (int *) shmat(id, NULL, 0);
			*(shared_memory+(npid%10)) = level;
			exit(0);
		}	
}

	if(rpid == getpid()){
		while(counti != 2){
		counti = 0;
		int *shared_memory = (int *) shmat(id, NULL, 0);
		for(j = 0;j<10;j++){
			if(*(shared_memory+j) == 2)
				counti+=1;
		}
		if(counti == 2){
			printf("2 grandchildren terminated\n");
		}
	}
	}

	shmdt(shared_memory);
	//wait unitl all processes have detached from shared memory
	wait(NULL);
	//to delete the shared memory
	shmctl(id,IPC_RMID,NULL);
	return 0;

}