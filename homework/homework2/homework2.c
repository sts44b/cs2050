#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Assume max char count in file */
#define MAX 20

/* library struct - DO NOT CHANGE */
typedef struct library
{
	char *genre; 
	char *band;
	char *album;
	float rating;
	struct library *next;  
}Library;

/* Function Prototypes - DO NOT CHANGE */
Library *Read_File(FILE *);
void Print(Library *);
Library *Create_List(Library *, Library *);
Library *Create_Album(char *, char *, char *, float);
Library *Merge(Library *, Library *);
int Count_List(Library *);
void Split_List(Library *, Library **, Library **);
Library *Merge_Sort(Library *);
Library *Delete_Genre(Library *);
void Free_Entry(Library *);
Library *Clean(Library *);

	/* MAIN 
 * 	* Error check file parameter
 * 		* Call Read_File to fill our list
 * 			* Print our list
 * 				* Merge Sort the linked list (by genre)
 * 					* Delete a genre
 * 						* Free the list
 * 							*/
//reformatted layout so I didn't have to scroll so much	
int main(int argc, char **argv){
		
		if(argc != 2)
		{
			printf("Not enough arguments.\n");
			return 0; 
		}
		
		FILE *fp = NULL;

		if((fp = fopen(argv[1], "r")) == NULL)
		{
			printf("File can not be opened.\n");
			return 0;
		}

		Library* Head = NULL;/*make head a pointer*/
		Head = Read_File(fp);
//		Print(Head);/*send head not address of head*/
		
//		Merge_Sort(Head);
//		Print(Head);/*send head not address of head*/

//		Head = Delete_Genre(Head);
//		Print(Head);//send head not address of head

//		Head = Clean(Head);
//		Print(Head);//send head not address of head		

		return 0;
}

/* Clean()* 	*Delete the linked list, recursively*/
Library *Clean(Library *Head){
		if(Head) return NULL;

		Library *Tmp = Head->next;
		Free_Entry(Head);
		Clean(Tmp->next);
}
	
/* Free_Entry()* 	*wrapper function to free a struct Library*/
void Free_Entry(Library *Entry)
	{
		free(Entry);
	}
	
/* Delete_Genre()* 	*Deletes a genre inputted by user
* Logic:* prompt user for genre input* traverse list deleting all structs that contain the genre*/
Library *Delete_Genre(Library *Head){

		if(!Head)
		{
			printf("List Empty.\n");
			return NULL;
		}
		
		char *input = malloc(MAX * sizeof(char *));
		Library *Current = Head;
		Library *Tail = NULL;

		printf("Which genre would you like to delete?\n");

		scanf("%s", input);		
	
		while(Current)
		{
			if(strcmp(Current->genre, input))
			{
				if(Current = Head)
				{
					Head = Head->next;
					Free_Entry(Current);
					Current = Head; 
				}
				else
					Tail->next = Current->next;

			}
			else
				Current = Current->next;
		}
}

/* Read_File()* 	* Open file fp * Create a struct from information in text file * Link our list with newly created struct*/
Library *Read_File(FILE *fp){

		Library *Head, *Entry;
		Head = Entry = NULL;
	
		char *genre, *band, *album; 
		float rating;		

		while(/*1*/!feof(fp))
		{
			fscanf(fp, "%s %s %s %f", genre, band, album, &rating);
printf("%s\n", genre);		
	/*want while loop to break if it IS the end of the file*/
			if(/*!*/feof(fp))
				break;
//			Entry = Create_Album(genre, band, album, rating);
//			Head = Create_	}

/* Print()* 	* Print the linked list*/
void Print(Library *Head){

		if(Head == NULL)/*add case that head == NULL*/
		{
			printf("Library is empty.\n");
			return;
		} 
		
		while(Head->next != NULL)/*add end loop scenario*/
		{
			printf("%20s %20s %20s %20.2f \n", 
				Head->genre, Head->band, Head->album, Head->rating);
			Head = Head->next;
		}
		printf("\n\n");
		/*return Head; no return for this function, returning void*/
	}

/* Create_Album* 	* Create a struct and assign the given args to it as appropriate*/

Library *Create_Album(char *genre, char *band, char *album, float rating){

		Library *Entry = malloc(sizeof(Library));
		strcpy(Entry->genre, genre);
		strcpy(Entry->band, band);
		strcpy(Entry->album, album);
		Entry->rating = rating; 
		Entry->next = NULL;

		return Entry;
}

/* Create_List()* 	* Push Entry onto our List*/
Library *Create_List(Library *Head, Library *Entry){

		if(!Head) 
			return Entry;

		Entry->next = Head; 
		return Entry;
}
/* Merge_Sort()* 	* Recursively split our list between Left and Right* Merge our Left and Right lists*/
Library *Merge_Sort(Library *Head){

    	Library *Tmp = Head;
    	Library *Left, *Right, *Result;
    	Left = Right = Result = NULL;

    	int count = Count_List(Head);
    		
    	if(count = 1)
        	return Tmp;

	/*removed star from pionter being passed*/	
	Left = Merge_Sort(/**/Left);
	Right = Merge_Sort(/**/Right);

    	Result = Merge(Left, Right);
    
	return Result;
}
/* Split_List()* 	* split our list in half*/
void Split_List(Library *Head, Library **Left, Library **Right){

    	int size = Count_List(Head);
	int i;

	Library* Tmp;/*declare tmp*/

    	*Left = Head;
    		
    	for(i=1; i<size/2; ++i)
        	Tmp=Tmp->next;

    	*Right = Tmp->next;
    	Tmp->next = NULL;
	}
	
/* Merge()* 	* Merge two linked lists Left and Right together in sorted order*/
Library *Merge(Library *Left, Library *Right) {

		Library *Result, *Tmp;
		Result = Tmp = NULL;

        	if(strcmp(Left->genre, Right->genre) <= 0){
            	Result = Left;
            	Left = Left->next;
        	}

        	else{
            	Result = Right;
            	Right = Right->next;
        	}

        	Tmp = Resul
