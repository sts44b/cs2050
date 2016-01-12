//Seanmichael Stanley
//sts44b
//08375210
//Lab 4
//function libraries to be used in this program
#include<stdio.h>
#include<stdlib.h>

//struct to be used for crating nodes of a linked list
typedef struct node{
	int value;
	struct node* next;
} Node;


//function prototypes
Node* insert_end(Node* head, int data);
int factorial(int n);
void print_list(Node* data);
int search(Node* head, int data);
void factorial_list(Node* head);
void delete_list(Node* head);

//program to utilize recursive functions and linked lists
int main(int argc, char** argv)
{
	//variables to be utilized in this program
	Node* head = NULL;
	int n;
	int value;

	FILE* in = fopen(argv[1], "r");//pointer to a file to be opened

	if (argc != 2){//check to see that there are enough arguments in the command line
		printf("\nInsufficient arguments");
	return 0;
	}

	if (in == NULL){//check that the file was opened
		printf("\nUnable to open file");
	return 0;
	}

	while(!feof(in)){//add numbers listed in a file to thier own node of a linked list
		fscanf(in, "%d", &value);
		head = insert_end(head, value);
	}

	print_list(head);//print the values of the linked list
	
	printf("Enter a number to search for: ");//prompt the user of a value to search for
	scanf("%d", &n);

	int s = search(head, n);//search to see if a number entered by the user is present

	if (s > 0){
		printf("\n%d was found.\n", n);
	}

	else{
		printf("\n%d was not found.\n", n);
	}

	factorial_list(head);//change values of the liked list to their factorials
	
	printf("\nFactorials of values in the linked list:\n")
	
	print_list(head);//print new values of linked list

	delete_list(head);//delete linked list

return 0;
}

//function to traverse a linked list to it's end and insert a new node
Node* insert_end(Node* head, int data)
{
	Node* temp = head;
	Node* current = head;	

	if(head == NULL){
		Node* new;
		new = (Node*) malloc(sizeof(Node));
		new->value = data;
		new->next = NULL;
	return new;
	}
	
	else if(head->next == NULL){
		Node* new = (Node*) malloc(sizeof(Node));
		new->value = data;
		new->next = NULL;
		head->next = new;
	return head;
	}

	else{
		current = current->next;
		temp = insert_end (current, data);
	}
	
return head;		
}

//function to print a linked list using recursion
void print_list (Node* head)
{
	if (head->next != NULL){
		printf("%d-> ", head->value);
		print_list(head->next);
	}

	else{
		printf("NULL\n");
	}
}

//function to seach a linked list recursively for a value
int search(Node* head, int data)
{
	int static x = 0;

	if (head->next != NULL){
		if (head->value == data){
			return ++x;
		}
		else{
			x = search(head->next, data);
		}
	}	

return x;
}

//function to traverse a linked list and change each value to its factorial
void factorial_list(Node* head)
{
	
	if (head->next != NULL){
		head->value = factorial(head->value);
		factorial_list(head->next);
	} 
		
}

//function to take a number and return the factorial of that number
int factorial(int n)
{
	if (n <= 1){
		return 1;
	}

	else{
		return (n * factorial(n - 1));
	}
}

//function to delete a linked list using recursion
void delete_list(Node* head)
{
	if (head->next != NULL){
		Node* temp = head;
		head = head->next;
		free(temp);
		delete_list(head);
	}

}
