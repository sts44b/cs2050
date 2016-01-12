//Seanmichael Stanley
//08375210
//10.14.13
//Lab7

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct spqueue{
	int priority;
	char* value;
	struct spqueue* next;
}SubPQueue;

typedef struct pqueue{
	int priority;
	SubPQueue* subQueue;
	struct pqueue* next;
}PQueue;

#define MAX_VALUE_SIZE 20
#define MAX_LINE_LENGTH 100

void enqueue(PQueue** queue, int priority1, int priority2, char* value);
char* dequeue(PQueue** queue);
void free_sub_node(SubPQueue* node);
void print_queue(PQueue* node);
int isElement(PQueue* queue, int priority);

int main(int argc, char** argv)
{
	char action[MAX_LINE_LENGTH];
	char* input = (char*)malloc(MAX_VALUE_SIZE * sizeof(char));
	int priority1;
	int priority2;
	PQueue* queue = NULL;
	SubPQueue* node1 = NULL;
	PQueue* node2 = NULL;
	char Ch;

        if (argc != 2){
                printf("\nInsufficient arguments.\n");
                return 0;
        }

        FILE* in = NULL;

        in = fopen(argv[1], "r");

        if (in == NULL){
                printf("File cannot be opened.\n");
                return 0;
        }

	while (!feof(in)){	
		fscanf(in, "%s", action);

		if (strcmp(action, "enqueue") == 0){
			fscanf(in, "%d%d%s", &priority1, &priority2, input);
			enqueue(&queue, priority1, priority2, input);
		}

//		else if(strcmp(action, "dequeue") == 0){

//		}

//		else if(strcmp(action, "print") == 0){

//		}

//		else{
//			printf("\nInvalid Command: %s", action);
//	
//		}
		if (feof(in))
			break;
	}

	print_queue(queue);
return 0;			
}


void enqueue(PQueue** queue, int priority1, int priority2, char* value)
{	
	PQueue *current = *queue;
	PQueue *prev = *queue;
	int check;
	SubPQueue *currentSub, *prevSub;
	currentSub = prevSub = NULL;
	
	check = isElement(*queue, priority1);

	if (*queue == NULL){
		PQueue *c = (PQueue*)malloc(sizeof(PQueue));
		c->priority = priority1;
		c->next = NULL;
		c->subQueue = NULL;
		*queue = c;
	}

	else if (check == 0){
		PQueue* newP = (PQueue*)malloc(sizeof(PQueue));
		newP->priority = priority1;
		newP->next = NULL;
		newP->subQueue = NULL;
		if((current->priority) < (newP->priority)){
			newP->next = current;
                        *queue = newP;
                        return;
		}
		
		else{	
			while ((current->priority) > (newP->priority && current != NULL)){					
				
				prev = current;
				current = current->next;
			}
			newP->next = current;
			prev->next = newP;
		}
	}

	else{
		while(current->priority != priority1){
			current = current->next;
		}
					
		SubPQueue* newSub = (SubPQueue*)malloc(sizeof(SubPQueue));
                newSub->priority = priority2;
                newSub->value = value;
                newSub->next = NULL;

		if ((current->subQueue) = NULL){
			current->subQueue = newSub;
		}

                else if((currentSub->priority) < (newSub->priority)){
                        newSub->next = currentSub;
                        current->subQueue = newSub;
                        return;
                }

                else{
                        while ((currentSub->priority) > (newSub->priority && currentSub != NULL)){

                                prevSub = currentSub;
                                currentSub = currentSub->next;
                        }
			newSub->next = currentSub;
                        prevSub->next = newSub;

                }
	}
}
char* dequeue(PQueue** queue){


}
void free_sub_node(SubPQueue* node){


}
void print_queue(PQueue* node){
	while(node != NULL){
		printf("%d\n", node->priority);
		node = node->next;
	}
}
int isElement(PQueue* queue, int priority){
	PQueue* current = queue;	

	while (current != NULL){
		if (current->priority == priority){
			return 1;
		}

		
		
		current = current->next;
	}
	return 0;
}

