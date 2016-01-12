/*Seanmichael Stanley*/
/*sts44b*/
/*08375210*/
/*Lab 3*/

/*function libraries for this program*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct node{
	int value;
	struct node* next;
}Node;



/*function prototypes for this program*/
Node* Create_Node(int data);
Node* Insert_Front(Node* list, Node* new_node);
void Print_list(Node* list);
void Delete_List(Node* list);
void Add_Int(Node* list, int value);
Node* Delete_Range(Node* list, int low, int high);

int main(int argc, char** argv)
{
	int fnum;
	Node *list;
	Node *new = NULL;
	int value, low, high;	

	list = malloc(sizeof(Node));
	list = NULL;	

	if (argc != 2){
		printf("\nInsufficient Arguments\n");
	return 0;
	}

	FILE* in;
	in = fopen(argv[1], "r");

	if (in == NULL){
		printf("\nUnable to open file\n");
	return 0;
	}
	
	while (!feof(in)){
		fscanf(in, "%d", &fnum);
		
		new = Create_Node(fnum);

		list = Insert_Front(list, new);
	}	

	Print_list(list);
	
	if (list != NULL){
		printf("Enter a value to add: ");
		scanf("%d", &value);

		Add_Int(list, value);
		Print_list(list);

		printf("Enter a range (LOWER integer first, then the HIGHER separated by a space): ");
		scanf("%d %d", &low, &high);
	
		list = Delete_Range(list, low, high);
		Print_list(list);
	}

	else{
		printf("No entries to change");
	}

	Delete_List(list);

return 0;	
}

Node* Create_Node(int data)
{
	Node* newNode;

	newNode = malloc(sizeof(Node));

	newNode->value = data;
	newNode->next = NULL;

return newNode;
}
Node* Insert_Front(Node* list, Node* new_node)
{
	if (list == NULL){
		list = new_node;
	}
	else{
		new_node->next = list;
		list = new_node;
	}
return list;
}
void Print_list(Node* list)
{
	Node* currentPtr;

	currentPtr = list;

	while(currentPtr != NULL)
	{
		printf(" %d ->", currentPtr->value);
		currentPtr = currentPtr->next;
	}

	printf("NULL\n");
}
void Add_Int(Node* list, int value)
{
	Node* currentPtr;
	currentPtr = list;

	while(currentPtr != NULL){
		currentPtr->value = (currentPtr->value + value);
		currentPtr = currentPtr->next;
	}
			
}
Node* Delete_Range (Node* list, int low, int high)
{
	if(low > high){
		return list;
	}

	Node* head;
	head = list;

	Node* tempPtr = NULL;

	Node* currentPtr;
	currentPtr = list;
	
	Node* prevPtr;
	prevPtr = list;

	while(currentPtr->value >= low && currentPtr->value <= high){
		tempPtr = head;
		head = head->next;
		free(tempPtr);
		currentPtr = head;
		prevPtr = head;
		
		if(head == NULL)
			break;
	}

	while(currentPtr != NULL){
		prevPtr = currentPtr;
		currentPtr = currentPtr->next;
		
		if(currentPtr == NULL)
			break;

		if(currentPtr->value >= low && currentPtr->value <= high){
			if(currentPtr->next == NULL){
				tempPtr = currentPtr;
				prevPtr->next = NULL;
				free(tempPtr);
			return head;
			}

			else{
				tempPtr = currentPtr;
				currentPtr = currentPtr->next;
				free(tempPtr);
			}
		
	
		}

	}
return head;
}
void Delete_List(Node* list){
	
	Node* currentPtr;
	Node* tempPtr;
	tempPtr = NULL;
	currentPtr = list;

	while( currentPtr != NULL){
		tempPtr = currentPtr;
		currentPtr = currentPtr->next;
		free(tempPtr);
	}
}

