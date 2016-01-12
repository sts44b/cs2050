//Seanmichael Stanley
//sts44b
//08375210
//Lab5

//function libraries
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define MAX 1000001

//function prototypes
void mergeSort(int array[], int low, int high);
void merge(int array[], int low, int middle, int high);
int linearSearch(int array[], int length, int key);
int binarySearch(int array[], int low, int high, int key);

//function main to sort and search arrays
int main(int argc, char** argv)
{
	//declare variables
	int size;	
	int high;
	int array[MAX];
	int i, j, L, B;
	clock_t start, end;
	double time1, time2, time3, time4;

	//check the number of command line args
	if (argc < 3){
		printf("\nInsufficient arguments");
		return 0;
	}
	//get the key to search for
	int key = atoi(argv[1]);
	
	//point to file
	FILE* in; 
	
	printf("%-16s%-16s%-16s%-16s","L search 1", "Sort", "L search 2", "B Search");

	//for each file listed in the command line
	for(j = 2; j < argc; j++){

		in = fopen(argv[j], "r");

		if (in == NULL){
			printf("\nUnable to open file");
		break;
		}
		//get the number of inputs
		fscanf(in, "%d", &size);
		//fill the array
		for (i = 0; i < size; i++){
			fscanf(in, "%d", &(array[i]));	
		}
		//time linear search
		start = clock();
		L = linearSearch(array, size, key);
		end = clock();
		time1 = (double)(end - start)/CLOCKS_PER_SEC;
		//time merge sort
		start = clock();
		mergeSort(array, 0, size - 1);
		end = clock();
		time2 = (double)(end - start)/CLOCKS_PER_SEC;
		//time linear search of sorted array
		start = clock();
		L = linearSearch(array, size, key);
		end = clock();
		time3 = (double)(end - start)/CLOCKS_PER_SEC;
		//time binary search
		start = clock(); 
		B = binarySearch(array, 0, size, key);
		end = clock();
		time4 = (double)(end - start)/CLOCKS_PER_SEC;
		//print times
		printf("\n%-16.7f%-16.7f%-16.7f%-16.7f", time1, time2, time3, time4);
		//close file
		fclose(in);
	}

return 0;
}
//function to split arrays in half
void mergeSort(int array[], int low, int high)
{
	int middle;

	if (low < high){
		middle = (low + high) / 2;
		mergeSort(array, low, middle);
		mergeSort(array, middle + 1, high);
		merge(array, low, middle, high);
	}

}
//function to join two arrays in sorted order
void merge(int array[], int low, int middle, int high)
{
	int i, m, k, l, temp[MAX];

	l = low;
    	i = low;
	m = middle+1;

	while((l <= middle) && (m <= high)){
		if(array[l] <= array[m]){
			temp[i] = array[l];
			l++;
		}

		else{
			temp[i] = array[m];
			m++;
		}	
		i++;
	}

	if(l > middle){
		for(k = m; k <= high; k++){
			temp[i] = array[k];
			i++;

         	}
	}

	else{
		for(k = l; k <= middle; k++){
			temp[i] = array[k];
             		i++;
		}
	}	

    	for(k = low; k <= high; k++){
		 array[k] = temp[k];
	}
}
//function to perform a linear search
int linearSearch(int array[], int length, int key)
{
	int i;
	
	for (i = 0; i < length; i++)
	{
		if (array[i] == key)
			return 1;
	}
return 0;
}
//function to perform a binary search
int binarySearch(int array[], int low, int high, int key)
{
	int middle;

	while (low <=high){
		middle = (low + high) / 2;

		if (key == array[middle]){
			return 1;
		}
	
		else if (key < array[middle]){
			high = (middle - 1);
		}
	
		else{
			low = middle + 1;
		}
	}
return 0;
}
