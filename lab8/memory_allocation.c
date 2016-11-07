#include <stdio.h>
#include <stdlib.h>
#define MEM_SIZE 600
int memory[MEM_SIZE];

struct node{
	struct node* next;
	struct node* prev;
	int status;
	int size;
	int sindex;
	int eindex;
};

typedef struct node node;

node* initialize_ll(){
	node* head;
	head = (node*)malloc(sizeof(node));
	head->prev = NULL;
	head->next = NULL;
	head->status = 0;
	head->size = MEM_SIZE;
	return head;
	//head->sindex = 0;
	head->eindex = 900;
}

node* getTail(node* head){
	if(head ==  NULL)
		return NULL;
	else
		while(head->next != NULL);
	return head;
}

node* addNodeToTail(node* tail,int size,int status){
	node* new_node = (node*) malloc(sizeof(node));
	tail->next = new_node;
	new_node->next = NULL;
	new_node->prev = tail;
	new_node->size = tail->size - size;
	tail->size = size;
	tail->status = status;
	new_node->status = 0;
	return new_node;
}

void printSnapshot(node* head){
	printf("########## memory snapshot ##########\n");
	while(head != NULL){
		printf("%d size block",head->size);
		if(head->status == 1){
			printf(" occupied\n");
		}
		else{
			printf(" empty\n");
		}
		head = head->next;	
	}
}

node* initializer(){
	int i = 0,psize;
	static status = 0;
	node* head = initialize_ll();
	node* tail = getTail(head);
	srand(time(NULL));
	for(i = 0;i<10;i++){
		psize = rand()%100;
		tail = addNodeToTail(tail,psize,status);
		status = 1 - status;
	}
	printSnapshot(head);
	return head;
}

void split(node* n,int size){
	if(n->size - size == 0){
		n->status = 1;
	}
	else{
		node* new_node = (node*)malloc(sizeof(node));
		new_node->status = 0;
		new_node->size = n->size - size;
		new_node->prev = n;
		new_node->next = n->next;
		n->next = new_node; 
		n->size = size;
		n->status = 1;
	}
	
}

void firstFit(int* process,int size,node* head){
	int i = 0;
	node* temp;
	for(i = 0;i<size;i++){
		temp = head;
		while(temp != NULL){
			if(temp-> size > process[i] && temp->status == 0){
				split(temp,process[i]);
				printSnapshot(head);
				process[i] = 0;
				break;
			}
			temp = temp->next;
		}
	}

}


int main(){
	node* n = initializer();
	int process[6] = {50,100,34,11,3,77};
	firstFit(process,6,n);
	int i;
	for(i = 0;i<6;i++){
		if(process[i] != 0)
			printf("could not allocate space of size %d\n",process[i]);
	}
	return 0;
}