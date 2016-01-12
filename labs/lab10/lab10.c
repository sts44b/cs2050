//Seanmichael Stanley
//sts44b
//08375210
//Lab 10


#include<stdio.h>
#include<stdlib.h>

void quick_sort (int arr[], int start, int end, int(*compare)(int,int));
int partition (int arr[], int start, int end, int(*compare)(int,int));
int compareSmallerOnLeft(int num1, int num2);
int compareSmallerOnRight(int num1, int num2);
int b_search(int arr[], int data, int(*compare)(int, int), int start, int end);
void print(int arr[], int length);

#define MAX 25

int main(int argc, char** argv){
	
	int value;
	int array[MAX];
	int count = 0;
	int srchNum;
	int result;
	int(*compare)(int, int);
	int sort_order;
	
	if (argc != 3){
		printf("\nInsufficient arguments.\n");
		return 0;
	}
	
	FILE* in, *search = NULL;
	
	in = fopen(argv[1], "r");
	
	search = fopen(argv[2], "r");
	
	if (in == NULL || search == NULL){
		printf("File cannot be opened.\n");
		return 0;
	}

while (!feof(in)){
	fscanf(in, "%d", &value);
	array[count] = value;
	
	if (feof(in))
		break;
	
	++count;
}
if ( sort_order == 1 ){
	compare = compareSmallerOnRight;
}
else {
	compare = compareSmallerOnLeft;
}
print(array, count);

quick_sort(array, 0, (count - 1), compare);

printf("\n\nSorted array is:  ");

print(array, count);

while (!feof(search)){
	fscanf(search, "%d", &srchNum);
	result = b_search(array, srchNum , compare, 0, count);
	
	if (result == 1)
		printf("\n%d was found in the array", srchNum);
		else
			printf("\n%d was not found in the array", srchNum);
			
			if (feof(search))
				break;
}

fclose(in);
fclose(search);
return 0;
}

void quick_sort (int arr[], int start, int end, int (*compare)(int, int)){
	
	int j;
	
	if( start < end ){
		
		j = partition( arr, start, end, compare);
		quick_sort( arr, start, j-1, compare);
		quick_sort( arr, j+1, end, compare);
	}
}

int partition (int arr[], int start, int end, int (*compare)(int, int)){
	
	int pivot, i, j, t;
	pivot = arr[start];
	i = start;
	j = end;
	
	while( 1)
	{
		while( arr[i] <= pivot && i <= end )
			++i;
		while( arr[j] > pivot )
			--j;
		
		if( i >= j )
			break;
		
		t = arr[i];
		arr[i] = arr[j];
		arr[j] = t;
	}
	
	t = arr[start];
	arr[start] = arr[j];
	arr[j] = t;
	return j;
}

int compareSmallerOnLeft(int num1, int num2){
	if (num1 == num2){
		return 0;
	}
	else if (num1 > num2){
		return -1;
	}
	else {
		return 1;
	}
}

int compareSmallerOnRight(int num1, int num2){
	if (num1 == num2){
		return 0;
	}
	else if ( num1 > num2 ){
		return 1;
	}
	else {
		return -1;
	}
}

int b_search(int arr[], int data, int (*compare)(int, int), int start, int end){
	int middle;
	
	if (end < start)
		return -1;
	
	middle = (start + end)/2;
	
	if (data < arr[middle])
		return b_search(arr, data, compare,  start, middle-1);
	
	else if (data > arr[middle])
		return b_search(arr, data, compare, middle+1, end);
	
	else if (data == arr[middle])
		return 1;
	else
		return 0;
}

void print(int arr[], int length){
	
	int i;
	for(i = 0; i < length; ++i)
		printf(" %d ", arr[i]);
}