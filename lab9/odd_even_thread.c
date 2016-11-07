#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_var = PTHREAD_COND_INITIALIZER;
pthread_cond_t a = PTHREAD_COND_INITIALIZER;
pthread_mutex_t b = PTHREAD_MUTEX_INITIALIZER;
int count = 1;

void *eventhread(){
	for(;;){
		pthread_mutex_lock(&count_mutex);
		if(count >= 15){
			pthread_mutex_unlock(&count_mutex);
			pthread_cond_signal(&condition_var);
			return 0;
		}
		printf("even_thread: thread_id = 1, ");
		printf("count = %d \n",count);
		if(count % 2 != 0){
			printf("Odd count found, signalling to odd thread \n");
			//pthread_mutex_lock(&b);
			pthread_mutex_unlock(&count_mutex);
			pthread_cond_signal(&condition_var);
			sleep(1);
			//pthread_cond_wait(&a,&b);
		}	
		else{
			count++;
			pthread_mutex_unlock(&count_mutex);
		}
		
	}	
}

void *oddthread(){

	for(;;){
		pthread_mutex_lock(&count_mutex);
		//pthread_mutex_lock(&b);
		pthread_cond_wait(&condition_var,&count_mutex);
		if(count > 15){
			pthread_mutex_unlock(&count_mutex);
			return 0;
		}
		printf("odd_thread: thread_id = 2, ");
		printf("count = %d \n",count);
		if(count ==  15){
			printf("Threshold reached \n");
			pthread_mutex_unlock(&count_mutex);
			return 0;
		}
		count++;
		//pthread_mutex_unlock(&b);
		pthread_mutex_unlock(&count_mutex);
		//pthread_cond_signal(&a);
	}	

}

int main(){

	pthread_t thread1,thread2;

	pthread_create(&thread1,NULL,&eventhread,NULL);
	pthread_create(&thread2,NULL,&oddthread,NULL);

	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	return 0;
}