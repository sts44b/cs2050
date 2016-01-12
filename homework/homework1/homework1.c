//Seanmichael Stanley
//sts44b
//08375210
//homework1

//reference function libraies to be used in this program
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//define the length of string categories
#define SONG_LENGTH 10
#define ARTIST_LENGTH 16
#define CD_LENGTH 20

//define the structure for data being handled
typedef struct song_ {
	char* song;
	char* artist;
	char* cd;
	int rating;

	struct song_ *next;
}Song;

//function prototypes for the functions created for this program
Song* new_song(char* song, char* artist, char* cd, int rating);
Song* insert_by_song(Song* head, Song* node);
void print_list(Song* head);
int update_song(Song* head, char* name, int rating);
void free_node(Song* node);
Song* delete_odd(Song* head);
Song* delete_even(Song* head);


//begin function main, program to sort playlist data in a linked list and manipulate list
int main (int argc, char** argv)
{
	//declare variables for function main to pass to other functions
	Song* newSong = NULL;
	Song* head = NULL;
	char *song, *artist, *cd;
	int rating;
	 
	//check to be sure of proper command line arguments
	if (argc != 2){
		printf("Insufficient Arguments\n");
		return 0;
	}

	//open file for reading
	FILE* in;
	in = fopen(argv[1], "r");

	//check that file was opened correctly
	if (in == NULL){
		printf("Unable to open file\n");
		return 0;
	}

	song = (char*)malloc(10 * sizeof(char));
	artist = (char*)malloc(16 * sizeof(char));
	cd = (char*)malloc(20 * sizeof(char));



	while(!feof(in)){
		fscanf(in, "%s%s%s%d", song, artist, cd, &rating);
		newSong = new_song(song, artist, cd, rating);
		head = insert_by_song(head, newSong);
	}
	
	free(song);
	free(artist);
	free(cd);

	print_list(head);

	char name[11];
	int newRating;

	//prompt user to change a rating
	printf("\nEnter a song and new rating: ");
	scanf("%s%d", name, &newRating);

	//change the rating of a song
	int update = 0;

	while(update == 0){
		update = update_song(head, name, newRating);
		if (update == 0){
		printf("song not found\nEnter a song and new rating: ");
		scanf("%s%d", name, &newRating);
		}
	}

	//print playlist
	print_list(head);

	//delete songs with odd ratings
	head = delete_odd(head);

	//print playlist
	print_list(head);

	//delete songs with even ratings
	head = delete_even(head);
	
	//print playlist
	print_list(head);
	
	//free allocated memory
	free_node(head);


	//close the file before terminating program
	fclose(in);

return 0;
}//end of function main

//function to creade a new node for a playlist entry
Song* new_song(char* song, char* artist, char* cd, int rating)
{
	Song* new = (Song*)malloc(sizeof(Song));
	new->song = (char*)malloc(10 * sizeof(char));
	strcpy(new->song, song);
	new->artist = (char*)malloc(16 * sizeof(char));
	strcpy(new->artist, artist);
	new->cd = malloc(20 * sizeof(char));
	strcpy(new->cd, cd);
	new->rating = rating;
	new->next = NULL;
return new;
}

//function to inster new playlist entries in alphabetical order
Song* insert_by_song(Song* head, Song* node)
{
	Song* current = head;
	Song* prev = head;

	if (head == NULL){
		head = node;
		head->next = NULL;
	return head;
	}
		
	else if(strcmp(node->song, head->song) < 0){
		node->next = head;
		head = node;
	return head;
	}

	while (current->next != NULL){
		prev = current;
		current = current->next;

		if (strcmp(node->song, current->song) < 0){
			prev->next = node;
			node->next = current;
		return head;
		}

		else if (current->next == NULL){
			current->next = node;
		return head;
		}		
	}
}

//function to print the entries of a playlist
void print_list(Song* head)
{
 	Song* currentPtr;

        currentPtr = head;

        if(head == NULL){
		printf("\nThe playlist is empty!");
	}

	while(currentPtr != NULL)
        {
                printf("%10s%16s%20s%10d\n", currentPtr->song, currentPtr->artist, currentPtr->cd, currentPtr->rating);
                currentPtr = currentPtr->next;
        }
}

//function to change the rating of a song
int update_song(Song* head, char* name, int rating)
{
	Song* current = head;
	int i = 0;	

	while(current->next != NULL){
		if(strcmp(current->song, name) == 0){
			current->rating = rating;
			++i;
		return i;
		}
		current = current->next;
	}
return i;
}

//function fo free allocated memory
void free_node(Song* node){
	free(node);
}

//function to delete songs with an odd rating
Song* delete_odd(Song* head){
	Song* current = head;
	Song* prev = head;
	Song* temp = NULL;

	while ((head->rating % 2) == 1){
		temp = head;
		head = head->next;		
		free(temp);
		current = head;
		prev = head;
		if(head == NULL){
		return head;
		}
	}

	while (current != NULL){
		if ((current->rating % 2) == 1){
			Song* temp = current;
			prev->next = current->next;
			current = current->next;
			free(temp);
		}
		
		else{
			if (current == NULL){
				break;
			}
			prev = current;
			current = current->next;
		}
	}
return head;
}

//function to delete songs with an even rating
Song* delete_even(Song* head)
{
	Song* current = head;
        Song* prev = head;
        Song* temp = NULL;

        while ((head->rating % 2) == 0){
                temp = head;
                head = head->next;
                free(temp);
                current = head;
                prev = head;
		if (head == NULL){
		return head;
		}
        } 
         
        while (current != NULL){
                if ((current->rating % 2) == 0){
                        Song* temp = current;
                        prev->next = current->next;
                        current = current->next;
                        free(temp);
                }
                
                else{ 
			if (current == NULL){
				break;
			}
                        prev = current;
                        current = current->next;
                }
        }

return head;
}
