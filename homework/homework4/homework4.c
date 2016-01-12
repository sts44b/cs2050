//Seanmichael Stanley
//sts44b
//08375210
//Homework 4

//function libraries
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//structure for linked list of classes
typedef struct node_{
        char* courseNum;
	char* courseDesc;
	char* prof;
	char* initial;
	int credit;
        struct node_* next;
} Node;


//function prototypes
void delete_list(Node* head);
int creditHours(Node* head);
char *trimwhitespace(char *str);
int menu(void);
void printCourseList(Node* head);
Node* addCourse(FILE* in, Node* head);
Node* createNode(char* course, int credit, char* courseDesc, char* prof, char* initial, Node* head);

//defintitions for mallocing strings
#define MAX_LINE 250
#define MAX_TKN 20

//program to enroll in courses
int main(int argc, char** argv){
	
	//variables for function main
	int choice;
	Node* head = NULL;
	int hours = 0;

	//check to see if there are the proper number of arguments on the command line
	if (argc != 2){
		printf("\nInsufficient arguments.\n");
		return 0;
	}

	//pointer to input file
	FILE* in = NULL;

	//open the file
	in = fopen(argv[1], "r");

	//check that file is properly opened
	if (in == NULL){
		printf("\nUnable to open file.\n");
		return 0;
	}
	
	//loop to enrol in courses until user quits
	while (1){
		//call the menu funtion to get an input from the user
		choice = menu();
	
		//if user wants to exit, print the courses registered in and the total credit hours
		if (choice == 3){
			if (head != NULL){
				printf("\nYou have registered for: ");
			}

			//print course list
			printCourseList(head);
			
			//calculate the number of credit hours enrolled in
			hours = creditHours(head);
			
			if (hours > 0){
				printf("\nFor a total of %d credit hours.", hours);	
			}
	
			printf("\nPROGRAM TERMINATED\n");
			delete_list(head);//free memory
			fclose(in);
			return 0;//end program
		}
		
		//display the courses enrolled in
		else if (choice == 2){
			if (head != NULL)
				printf("\nYou are currently enrolled in: ");
			printCourseList(head);//print courses
		}

		//prompt user to enter the course they wish to enroll in
		else if (choice == 1){
			rewind(in);//rewind in to beginning of file for new course
			head = addCourse(in, head);//add course to linked list
		}	
		
		//for some reason if you entered a character this loop would become infinite with no regard for the function menu
		else{
			printf("\nInvalid entry. Course registration lost. Please try again by restarting program\n\nIMPORTANT: DO NOT ENTER ANYTHING OTHER THAN 1, 2, OR 3");
			if (head != NULL)
				delete_list(head);
			fclose(in);
			return 0;
		}
	}


	fclose(in);//close file
	delete_list(head);//free memory
	return 0;//end function main
}
/*Function to iterate through the linked list of courses that the user has registered for and calculate
 * the total number of credit hours they are enrolled in and return that value to function main to be displayed before exiting the program*/
int creditHours(Node* head){
	int hours;
	
	while (head != NULL){
		hours += head->credit;
		head = head->next;
	}

return hours;
}

/*Function to parse through a file and find the course that the user wants to enroll in. If the course is present the course description, credit hours,
 * course number, and professor are gathered and sent to create node to be added to a node and placed in the front of alinked list*/
Node* addCourse (FILE* in, Node* head){
	
	//allocate memory and variables for the information gathered from the course catalog
	char* course = (char*)malloc(MAX_TKN * sizeof(char));
	int check = 0;
	int credit;
	char* courseDesc = (char*)malloc(MAX_TKN * sizeof(char));
	char* initial = (char*)malloc(MAX_TKN * sizeof(char));
	char* prof = (char*)malloc(MAX_TKN * sizeof(char));

	printf("\nWhich course would you like to register for? ");
	scanf("%s", course);

	char* buffer = (char*)malloc(MAX_LINE * sizeof(char));
	
	//block of code for parsing
	while(fgets(buffer, MAX_LINE, in)){
                if(buffer[strlen(buffer) - 1] == '\n')
                        buffer[strlen(buffer) - 1] = '\0';
                char* token = strtok(buffer, " ,\t");
                while (token != NULL){

			//if a match is found with the course entered by the user the information associated with that course is gathered
                        if (strcmp(course, token) == 0){
				++check;//flag to show that a match has been found

				token = strtok(NULL, "%d");

				//get the last character in the string which should be the credit hours
				credit = atoi(&token[strlen(token)-1]);//only works if there are no spaces after the credit hours
				token[strlen(token)-1] = '\0';//remove the credit hours from the string
				
				strcpy(courseDesc, token);//copy the string into the variable for course description
				courseDesc = trimwhitespace(courseDesc);//remove the spaces around course description
				break;			
			}
			
			//find the professors name and initial
			if((check == 1) && (token[0] >= 'A' && token[0] <= 'Z') && (token[1] >= 'a' && token[1] <= 'z')){
				prof = token;
				prof = trimwhitespace(prof);

				initial = strtok(NULL, " ,\t");
				initial = trimwhitespace(initial);
				head = createNode(course, credit, courseDesc, prof, initial, head);//once all information is gathered sent it to create a node and add course to the linked list
	
				free(buffer);
				buffer = NULL;
				return head;
			}
			token = strtok(NULL, " ,\t");

                }
        }

	// if the course is not found return to the menu
	if (check == 0){
		printf("\nINVALID - Course not found. Try again.");
	}
free(buffer);
buffer = NULL;
return head;
}

/*this function takes in the head of a linked list and erases the member and the entire node of each node in the linked list*/
void delete_list(Node* head)
{
        if (head->next != NULL){
                Node* temp = head;
                head = head->next;
                free(temp->courseNum);
			temp->courseNum = NULL;
		free(temp->courseDesc);
			temp->courseDesc = NULL;
		free(temp->prof);
			temp->prof = NULL;
		free(temp->initial);
			temp->initial = NULL;
		free(temp);
			temp = NULL;
                delete_list(head);
        }

}

/*this function takes in the information from the function addClass and creates a node, the node is then added to a linked list*/
Node* createNode(char* course, int credit, char* courseDesc, char* prof, char* initial, Node* head)
{
	//allocate memory for the member of the node
	Node* new = (Node*)malloc(sizeof(Node));
	new->courseNum = (char*)malloc(MAX_TKN * sizeof(char));
	new->courseDesc = (char*)malloc(MAX_TKN * sizeof(char));
	new->prof = (char*)malloc(MAX_TKN * sizeof(char));
	new->initial = (char*)malloc(MAX_TKN * sizeof(char));

	//assign values from the function addClass to the members of the node
	new->credit = credit;
	strcpy(new->courseNum, course);
	strcpy(new->courseDesc, courseDesc);
	strcpy(new->prof, prof);
	strcpy(new->initial, initial);

	//add the node to the linked list
	if(head == NULL){
		new->next = NULL; 		
		head = new;
	}

	else{
		new->next = head;
		head = new;
	}
	
	printf("\nYou are now registered for this course.");
//return the front of the linked list
return head;
}

/*this function displays the menu fot the user to choose from*/
int menu(void){

	int choice;

		printf("Select your option below:\n1-Register for a Course\n2-See my total\n3-Exit\nChoice: \n");		
		scanf("%1d", &choice);

return choice;	
}


/*this function will print all of the courses that the user has enrolled in*/
void printCourseList(Node* head){

	if (head == NULL){
		printf("\nYou have not registered for any courses.");
		return;
	}

	else{
		while (head != NULL){
			printf("\n%-10s%-25s Credit: %d hours Professor: %-10s%-3s", head->courseNum, head->courseDesc, head->credit, head->prof, head->initial);
			head = head->next;
		}
		return;
	}
return;
}

/*this function will trim the spaces and tabs from the ends of a string*/
char *trimwhitespace(char *str){
	
	char *end;

	// Trim leading space
	while(isspace(*str)) str++;
  
	if(*str == 0)  // All spaces?
		return str;
  
	// Trim trailing space
	end = str + strlen(str) - 1;
	while(end > str && isspace(*end)) 
		end--;
  
	// Write new null terminator
	*(end+1) = 0;
  
return str;
}

	
