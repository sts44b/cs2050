//lab1
/*Seanmichael Stanley*/
//sts44b
/*08375210*/
/*LABCODE: Week1*/

//reference function libray
#include<stdio.h>


//define array sizes
#define MAX 15
#define MAX_LENGTH 30

//define a struct
typedef struct{
	char name[MAX_LENGTH];
	int birth;
	int death;
	int reign;
} data;

//create global data array
data emperors[MAX];

//define pointers for files
FILE *in, *out;

//function prototypes
int openFiles(char* input, char* output);
int readContent();
int empror_to_live_longest(int size);
int youngest_emporor_to_die(int size);
int longest_lifetime_reign(int size);
int emporor_to_rule_longest(int size);
void writeFile(int oldest, int youngest, int longest, int successful, int size);
void closeFiles();

//begin function mail
int main(int argc, char** argv)
{
	//declare variables for this function
	int checkOpen;
	int size;	
	int longestLife;
	int youngest;
	int reignLife;
	int longestRule;
		
	//open files 
	checkOpen = openFiles(argv[1], argv[2]);

	//end program if files cannot be opened
	if (checkOpen == -1)
		return 0;

	//get the number of emperors listed
	size = readContent();

	//call function to find the oldest emperor
	longestLife = emperor_to_live_longest(size);

	//call function to find the youngest emperor
	youngest = youngest_emperor_to_die(size);
	
	//call function to find the emperor who spent most of life in rule
	reignLife = longest_lifetime_reign(size);

	//find emperor with the longest rule
	longestRule = emperor_to_rule_longest(size);
	
	//call function to witre into summery file
	writeFile(longestLife, youngest, longestRule, reignLife, size);
	
	//close files
	closeFiles();

return 0;
}//end function main

//function to open files and point to them
int openFiles(char* input, char* output)
{
	in = fopen(input, "r");

	if (in==NULL)
	{
		printf("Unable to open the input file");
		return -1;
	}

	out = fopen(output, "w");

	if (out==NULL)
	{
		printf("Unable to open the output file");
		return -1;	
	}
return 0;
}

//function to read the condent of the input file and assign the values to the data structure
int readContent()
{
	int size;
	int i;

	fscanf(in, "%d", &size);

	for (i = 0; i < size; i++)
	{
		fscanf(in, "%s%d%d%d", emperors[i].name, &emperors[i].birth, &emperors[i].death, &emperors[i].reign);
	}
return size;
}

//function to find the oldest emperor
int emperor_to_live_longest(int size)
{
	int age = 0;
	int oldest;
	int i; 

	for (i = 0; i < size; i++)
	{
		if ((emperors[i].death - emperors[i].birth) > age){
			oldest = i;
			
			age = (emperors[i].death - emperors[i].birth);
		}
	}
return oldest;
}

//function to find the youngest emperor
int youngest_emperor_to_die(int size)
{
	int age = 500;
	int youngest = 0;
	int i;

	for (i = 0; i < size; i++)
	{
		if ((emperors[i].death - emperors[i].birth) < age){
			youngest = i;

			age = (emperors[i].death - emperors[i].birth);
		}
	}
return youngest;
}

//function to find the emperor who spent most of life in rule
int longest_lifetime_reign(int size)
{
	int longest = 0;
	int diff = 100;
	int i;

	for (i = 0; i < size; i++)
	{
		if (((emperors[i].death - emperors[i].birth) - emperors[i].reign) < diff)
		{ 
			longest = i;

			diff = ((emperors[i].death - emperors[i].birth) - emperors[i].reign);

		}

	}

return longest;
}

//emperor who had the longest reign
int emperor_to_rule_longest(int size)
{
	int longest = 0;
	int i;
	int rule = 0;

	for (i = 0; i < size; i++)
	{
		if (emperors[i].reign > rule){
			longest = i;

			rule = emperors[i].reign;
		}
	}
return longest;
}

//function to write data into the summery file
void writeFile(int oldest, int youngest, int longest, int successful, int size)
{
	int i;
	int oldAge;
	int youngAge;
	int ageLifeReign;

	oldAge = (emperors[oldest].death - emperors[oldest].birth);

	youngAge = (emperors[youngest].death - emperors [youngest].birth);

	ageLifeReign = (emperors[successful].death - emperors[successful].birth);

	for (i = 0; i < size; i++)
	{
		fprintf(out, "%s Birth: %d, Death: %d, Reign: %d,\n", emperors[i].name, emperors[i].birth, emperors[i].death, emperors[i].reign);
 
	}

	fprintf(out, "\n-----------------");

	fprintf(out, "\nOldest emperor to die %s, Age: %d", emperors[oldest].name, oldAge);

	fprintf(out, "\nYoungest emperor to die %s, Age: %d", emperors[youngest].name, youngAge);

	fprintf(out, "\nEmperor to rule longest: %s, %d years", emperors[longest].name, emperors[longest].reign);

	fprintf(out, "\nEmperor to spend most lifetime in reign: %s, %d years in reign. Died at age of %d", emperors[successful].name, emperors[successful].reign, ageLifeReign);
}

//function to close the files
void closeFiles()
{
	fclose(in);

	fclose(out);
}
