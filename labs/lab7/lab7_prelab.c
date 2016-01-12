//Seanmichael Stanley
//sts44b
//08375210
//10/14/13
//Lab 7


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node_{
        int value;
        struct node_ *next;
}Queue;

Queue* enqueue(Queue* head, int value);
int dequeue(Queue** head);
void print_list (Queue* head);


int main(int argc, char** argv)
{
	int num;
	Queue *head = NULL;

	if (argc != 2){
		printf("\nInsufficient arguments.\n");
		return 0;
	}

	FILE* in = NULL;
	FILE* out = NULL;

	in = fopen(argv[1], "r"); 

	if (in == NULL){
		printf("File cannot be opened.\n");
		return 0;
	}

	while (!feof(in)){
		fscanf(in, "%d", &num);
		head = enqueue(head, num);		
			
		printf("\n");
		print_list(head);
		

	}

	while (num != -1){
		num = dequeue(&head);
		printf("%d\n", num);
		print_list(head);
	}
}


Queue* enqueue(Queue* head, int value){
	Queue* current = head;
	Queue* temp;
	temp = (Queue*)malloc(sizeof(Queue));	
	temp->value = value;
	temp->next = NULL;

	if (head == NULL){
		head = temp;
		return head;
	}
	else{
		while(current->next != NULL){
			current = current->next;
		}
		current->next = temp;
	return head;
	}	
}

int dequeue(Queue** head){
	Queue* temp = *head;
	int x;

	if (*head == NULL){
		printf("\nQueue is empty.");
		return -1;
	}
	else{
		int x = temp->value;
		*head = temp->next;
		free(temp);
		return x;	
	}		

}

void print_list (Queue* head)
{
        if (head->next != NULL){
                printf("%d-> ", head->value);
                print_list(head->next);
        }

        else{
                printf("NULL\n");
        }
}
