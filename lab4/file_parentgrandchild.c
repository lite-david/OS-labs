#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>	

int main(){

	pid_t rpid,npid;
	rpid = getpid();
	FILE *wfp,*rfp;
	wfp = fopen("ipcfile.txt","w");
	fclose(wfp);
	char buff[100];
	int level = 0,cid,i,clear_mem = 0,j,status = 0,counti =0;

	for(i = 0;i<3;i++){
		cid = fork();
		if(cid == 0)
			level+=1;

		npid = getpid();

		if(i == 2 && rpid != npid){
			printf("%d %d \n",level,npid);

			//doing an append to file
			wfp = fopen("ipcfile.txt","a");
			fprintf(wfp,"%d",level);
			fclose(wfp);
		}
}
	if(rpid == getpid()){
		while(counti != 2){
		counti = 0;

		rfp = fopen("ipcfile.txt","r");
		fscanf(rfp,"%s",buff);
		fclose(rfp);

		for(j = 0;j<7;j++){
			if(buff[j] == '2')
				counti+=1;
			buff[j] = '0';
		}
		
		if(counti == 2){
			printf("2 grandchildren terminated\n");
		}
	}
	}

	return 0;
}