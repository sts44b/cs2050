//Seanmichael Stanley
//08375210
//sts44b
//Lab 9


#include<stdio.h>
#include<stdlib.h>

typedef struct bt_{
	int value;
	struct bt_ *right;
	struct bt_ *left;
}BST; 

BST* insert(BST* root, int value);
void printTree(BST* root);
void padding(char toPrint, int numTimes);
void displayBST(BST* root, int depth);
int search(BST* root, int value);
BST* findMin(BST*root);
BST* delete(BST* root, int value);

int main(int argc, char** argv)
{
	BST* root = NULL;
	BST* min = NULL;
	int value;
	int num;
	int srchResult;
	if (argc != 2){
		printf("\nInsufficient arguments.\n");
                return 0;
        }

        FILE* in = NULL;

        in = fopen(argv[1], "r");

        if (in == NULL){
                printf("File cannot be opened.\n");
                return 0;
        }

        while (!feof(in)){
		fscanf(in, "%d", &value);
		root = insert(root, value);
		
		if (feof(in))
			break;
	}

	printTree(root);
	printf("\nEnter a number to search: ");
	scanf("%d", &num);
	srchResult = search(root, num);
	
	if (srchResult == 1){
		printf("\n%d was found.\n", num);
	}
	else {
		printf("\n%d was not found.\n", num);
	}

	printf("\nEnter a number to remove from the tree: ");
	scanf("%d", &num);

	root = delete(root, num);
	
	printTree(root);

	fclose(in);

return 0;
}

BST* insert(BST* root, int value)
{
	if (root == NULL){
		root = (BST*)malloc(sizeof(BST*));
		root->value = value;
		root->left = NULL;
		root->right = NULL;
	}

	else if (value > root->value)
		root->left = insert(root->left, value);
	
	else if (value < root->value)
		root->right = insert(root->right, value);
	
return root;
}

int search(BST* root, int value)
{
	int num;
	
	if (root == NULL)
		return 0;
	else if	(value == root->value)
		return 1;
	else if (value > root->value)
		num = search(root->left, value);
	else if (value < root->value)
		num = search(root->right, value);
}

BST* delete(BST* root, int value)
{
	BST* tmp = NULL;
	BST* ptrMin = NULL;

	if (root == NULL)
		return root;
	
	else if (value > root->value){
		root->left = delete(root->left, value);	
	}

	else if (value < root->value){
		root->right = delete(root->right, value);
	}

	else if (value == root->value){
		ptrMin = (BST*)malloc(sizeof(BST));

		if (root->right == NULL && root->left == NULL){
			free(root);
			return NULL;
		}

		else if (root->right != NULL && root->left != NULL){
			ptrMin = findMin(root->left);
			root->value = ptrMin->value;
			free(ptrMin);
			return root;
		}

		else if (root->right == NULL){
			return root->left;
		}

		else if (root->left == NULL){
			return root->right;
		}
	}
}

BST* findMin(BST* root){
	BST* min = NULL;

	while (root->right != NULL)
		min = findMin(root->right);
return min;
}

void printTree(BST* root)
{
	displayBST(root, 0);
}

void displayBST(BST* root, int depth)
{
	if (root == NULL)
	{
		padding(' ', depth);
		printf("-\n");
		return;
	}

	displayBST(root->left, depth+4);
	padding(' ', depth);
	printf("%d\n", root->value);
	displayBST(root->right, depth+4);
}

void padding(char toPrint, int numTimes)
{
	int i;
	for (i = 0; i < numTimes; i++)
		printf("%c", toPrint);
}

