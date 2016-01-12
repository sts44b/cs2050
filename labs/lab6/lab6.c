//Seanmichael Stanley
//sts44b
//08375210
//Lab 6
//10/7/2013

#define MAX_FILE_LENGTH 20

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct node_{
	int value;
	struct node_* next;
} Node;

typedef Node* List;

Node* new_node(int value);
int list_sum(Node* head);
void print_list(List* array, int length);
void insertion_sort(List* array, int length);
void free_list(List* array, int length);

int main(int argc, char** argv)
{
	int length;
	Node* head;
	int i;
	List* array;
		
	

	FILE* in;
	
	in = fopen(argv[1], "r");
	
	if (in == NULL){
		printf("\nUnable to open file, enter new file name:\n");
	return 0;
	}	

	length = create_list(&array, in);
	
	print_list(array, length);
	
	free_list(array, length);

	//insertionsort(array, length);
	printf("\n\nAttempted insertion sort\n");
return 0;
}

int create_list(List** array, FILE* fp)
{
	int length;
	int i;
	int value;
	Node* new;
	Node* temp;

	fscanf(fp, "%d", &length);
	*array = malloc(length * sizeof(Node*));
	
	for(i = 0; i < length; i++){
		(*array)[i] = NULL;
	}

	while (!feof(fp)){
		fscanf(fp, "%d %d", &i, &value);
		new = new_node(value);
		new->next = (*array)[i];
		(*array)[i] =  new;
	}
		
return length;
}

Node* new_node(int value){
	Node* new;
	
	new = malloc(sizeof(Node*));
	new->value = value;
return new;
}

void print_list(List* array, int length){

	int i;

	for(i = 0; i < length; i++){
	
		printf("|%d| ", i);
		Node* list = array[i];
		int sum = list_sum(list);

		if (list == NULL){
			break;
		}

		while (list != NULL){
			printf("%d->", list->value);
			list = list->next;
		}
		printf("NULL = %d\n", sum);
	}
}

int list_sum(Node* head){
	int sum = 0;
	
	if (head == NULL)
		return 0;

	while (head != NULL){
		sum += head->value;
		head = head->next;
	}


return sum;
}

void free_list(List* array, int length)
{
	int i;

	for (i = 0; i < length; i++)
	{
		Node* temp = array[i];
		Node* current = array[i];
		while(current->next != NULL){
			temp = current;
			current = current->next;
			free(temp);
		}
	
	}

}
/*void insertion_sort(List* array, int length)
{
	int i;
	
	for (i=0; i < length; i++) {
	
		int j;
		Node* temp = (*array)[i];
	
		for (j = i - 1; j >= 0; j--) {
    			if ((*array)[j] <= temp) break;
    			(*array)[j + 1] = (*array)[j];
		}
		(*array)[j + 1] = temp;
	}
}*/
