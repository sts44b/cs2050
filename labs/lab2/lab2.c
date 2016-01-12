//Seanmichael Stanley
//sts44b
//08375210
//Lab 2

//function libraries
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//struct to store data from car file
typedef struct{
	char* name;
	int model_year;
	int max_speed;
	int mileage;
}Car;

//funciton prototypes for this program
void Print_Garage (const int num_cars, Car* garage);
void Drive_Car (Car* car);
void Free_Array (const int num_cars, Car* garage);
Car* Fill_Array (FILE*in, const int num_cars);

//begin function main
int main(int argc, char** argv)
{
	//declare variables for function name
	int num_cars;	
	Car* carPtr = NULL;        
	int i;

	//check to see that there are enough arguments in command line
	if (argc != 2)
	{
		printf("\nInsufficient arguments\n");
	return 0;
	}

	FILE*in;

	in = fopen(argv[1],"r");//open file

	if (in == NULL)//make sure able to open file
	{
		printf("Unable to open input file\n");
	return 0;
	}	

	fscanf(in, "%d", &num_cars);//get the number of cars listed in the file

	carPtr = Fill_Array(in, num_cars);//gather data from file

	fclose(in);//close file
	
	printf("Garage information:\n");	

	Print_Garage(num_cars, carPtr);//print info in file
	
	for (i = 0; i < num_cars; i++){
		Drive_Car((carPtr + i));//loop to add drive miles to original miles
	}

	printf("\n\nAfter Driving\n");

	Print_Garage(num_cars, carPtr);//print info after driving

	Free_Array(num_cars, carPtr);//free memory

return 0;
}//end functoin main

//function to print the contents of the data struct
void Print_Garage(const int num_cars, Car* garage)
{
   
   int j;

	for (j = 0; j < num_cars; j++)
	{
           printf("The %d %s has %d miles and a top speed of %d miles per hour.\n", (garage + j)->model_year, (garage + j)->name, (garage + j)->mileage, (garage + j)->max_speed);
	}


}

//function to fill struct with data from a file
Car* Fill_Array (FILE* in, const int num_cars)
{
   int i, x;
   Car* ptr;

   ptr = malloc(num_cars * sizeof(Car));

   for (i = 0; i < num_cars; i++)
   {
      (ptr + i)->name = malloc(20 * sizeof(char));
   } 

   for (x = 0; x < num_cars; x++)
   {
      fscanf(in, "%s%d%d%d", (ptr + x)->name, &((ptr + x)->model_year), &((ptr + x)->max_speed), &((ptr + x)->mileage));
   }

return ptr;
}

//function to add a random number of miles to each car
void Drive_Car(Car* car)
{
	int drive;

	srand(time(NULL));

	drive = ((rand() % 100) + 1);

	(car->mileage) = ((car->mileage) + drive);

}

//function to clear the memory used by the struct
void Free_Array(const int num_cars, Car* garage)
{
	int i;

	for (i = 0; i < num_cars; i++)
	{
		free((garage + i)->name);
	}

	free(garage);
}
