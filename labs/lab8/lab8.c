/*Seanmichael Stanley*/
/*sts44b*/
/*08375210*/
/*lab 8*/
/*labcode: 240713*/ 

//reference the function libraries with useful functions for this program
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 50

//declare the structure variables for this program
typedef struct{
   int id;
   char name[MAX];
   int grade;
} data;

data students[MAX];//define the size of the structure array

//function prototypes to be utilized in the program
int loadArray(char* filename);
int findHighestgrade(int size);
int findLowestgrade(int size);
float averageClassgrade(int size);
int searchArray(int size, int id);
void printArray(int size);
int writeContent(char* fname, int size, int i, int j, float avg);
int updateArray(char*,int);
void swap(data* x, data* y);
void sortArray(int size);

//call function main and gather inputs from the command line
int main (int argc, char* argv[])
{
   //declare the variables to be used in this program
   int size, size2;
   int highest;
   int lowest;
   float avg;
   int findID;
   int id;
   int write;

   if (argc != 4)//check to make sure there are the appropriate number of parameters
   {
      printf("\nInsufficient arguments\n");
      return 0;
   }
   
   size = loadArray(argv[1]);//call function to load data from input file ints struct array

   if (size == 0)//if the input file cannout be opened quit program
      return 0;

   highest = findHighestgrade(size);//call a function to find the highest grade in the class

   lowest = findLowestgrade(size);//call a function to find the lowest grade in the class

   avg = averageClassgrade(size);//call a funciton to calculate the average grade of the class
   
   printf("\n\nStudent record");
   printArray(size);//display the array of data gathered from the input file

   //display the results of the previous functions
   printf("\nThe student with the highest grade is %s with the grade %d", students[highest].name, students[highest].grade);
   printf("\nThe student with the lowest grade is %s with the grade %d\n", students[lowest].name, students[lowest].grade);
   printf("\nThe average grade for the class %.2f\n", avg);

   printf("\nEnter the ID of the student to search: ");
   scanf("%d", &id);//prompt user to enter an id number to search for

   findID = searchArray(size, id);//call function to find what student the id entered by the user pionts to 

   if (findID == -1)
      printf("Student with the ID %d is not present in the class\n", id);//check to see if correct student number entered
   else
      printf("Student with the id %d is %s\n", students[findID].id, students[findID].name);//display the student searched for by the user

   size2 = updateArray(argv[2], size);

   printf("\nUpdated student record");
   printArray(size + size2);

   sortArray(size + size2);

   printf("\nPrinting sorted student record");
   printArray(size + size2);

   write = writeContent(argv[3], (size + size2), highest, lowest, avg);//call the function to print data in the output file

   if (write == 0)
   {
      printf("\nUnable to open the output file\n");
   }
return 0; 
}//end function main


//function to load the data from the input file into the structure array
int loadArray(char* input)
{
   int i, size;
   FILE* in;

   in = fopen(input, "r");

   if (in == NULL)//check to see that file opened correctly
   {
      printf("Unable to open the input file\n");
      return 0;
   }

   fscanf(in, "%d", &size);//find the number of students in the class

   for(i = 0; i < size; i++)
   {
      fscanf(in, "%d%s%d", &students[i].id, students[i].name, &students[i].grade);//assign values to the structure array

   }
   fclose(in);

return size;//return the number of students in the class
} 

//function to add data to the structure array
int updateArray(char* update, int size)
{
   int i;
   int upSize;
   FILE*up;

   up = fopen(update, "r");//open file and point
   
   if (up == NULL)
   {
      printf("Unable to open the input file\n");
      return 0;
   }

   fscanf(up, "%d", &upSize);//get number of students

   for (i = size; i < (upSize + size); i++)//add data to the end of the previously populated structure array
   {
      fscanf(up, "%d%s%d", &students[i].id, students[i].name, &students[i].grade);
   }
   fclose(up);

return upSize;//return the size of the update file
}
//function to find the highest grade in the class
int findHighestgrade(int size)
{
   int i;
   int high = 0;
   int index;

   for (i = 0; i < size; i++)
   {
      if (students[i].grade > high)
      {   
         high = students[i].grade;//compare the grades to find the highest
         index = i;
      }
   }

return index;//return the index of the highest grade
}

//function to find the lowest grade in the class
int findLowestgrade(int size)
{
   int i;
   int low = 100;
   int index;

   for (i = 0; i < size; i++)
   {
      if (students[i].grade < low)
      {
         low = students[i].grade;//compare the grades to find the lowest
         index = i;
      }
   }
return index;//return the index of the lowest grade
}

//function to calculate the average of the class grades
float averageClassgrade(int size)
{
   int i;
   int total = 0;
   float average;

   for (i = 0; i < size; i++)
   {
      total += students[i].grade;//add up the total of the grades
   }
   
   average = (float) total / size;//calculate the average
return average;//return the average
}

//function to print the data recieved by the data structure array
void printArray(int size)
nt findHighestgrade(int size)
{
   int i;
   int high = 0;
   int index;

   for (i = 0; i < size; i++)
   {
      if (students[i].grade > high)
      {
         high = students[i].grade;//compare the grades to find the highest
         index = i;
      }
   }

return index;//return the index of the highest grade
}
{
   int i;

   printf("\n%-4s%-10s%6s\n", "ID", "Name", "Grade");//print coumn headings

   for(i = 0; i < size; i++)
   {
      printf("%-4d%-10s%6d\n", students[i].id, students[i].name, students[i].grade);//print the data of each student
   }
}

//function to search for an id entered by the user
int searchArray(int size, int id)
{
   int i;
   int match = -1;

   for (i = 0; i < size; i++)
   {
      if (students[i].id == id)
      {
         match = i;
      }
   }

return match;//return the idex of the student with matching id
}

//Function to write data to the output file
int writeContent(char* output, int size, int i, int j, float avg)
{
   int x;//variable for for loop

   FILE* out;//assign a pointer to the output file

   if ((out = fopen(output, "w")) == NULL)//check that file opened
      {
         printf("\nUnable to open output file\n");
         return 0;
      }
   else
   {
      for (x = 0; x < size; x++)//for loop to print output in file
      {
         fprintf(out, "%-4d%-10s%6d\n", students[x].id, students[x].name, students[x].grade);
      }
   
   //output calculations and other information in output file
  // fprintf(out, "\nStudent with the highest grade is %s with the id %d and the grade %d", students[i].name, students[i].id, students[i].grade);
  // fprintf(out, "\nStudent with the lowest grade is %s with the id %d and the grade %d", students[j].name, students[j].id, students[j].grade);
  // fprintf(out, "\nAverage class grade is %.2f", avg);

   close(out);//close the file
   }   
return 1;
}//end function

//function to sort the structure array data by student number
void sortArray(int size)
{
   int i, j;
   
   //loop for each necessary pass
   for (i = 1; i < size; i++)
   {
      //loop for each comparison
      for (j = 0; j < size - 1; j++)
      {
         if (students[j].id > students[j + 1].id)
            swap(&students[j], &students[j + 1]);//if not in correct order swap
      }
   }
}

//function to swap two adjacent elements in an array
void swap(data* x, data* y)
{
   data hold;

   //swap grades
   hold.grade = y->grade;
   y->grade = x->grade;
   x->grade = hold.grade;


   //swap id
   hold.id = y->id;
   y->id = x->id;
   x->id = hold.id;
   
   //swap name strings
   strcpy(hold.name, y->name);
   strcpy(y->name, x->name);
   strcpy(x->name, hold.name);  
}



