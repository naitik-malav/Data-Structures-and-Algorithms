#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct node {
    char numPlate[7];
    struct node *left;
    struct node *right;
    struct node *parent;
};

char Path[999];

int compare(char *x, char *y) {
	if( (*x) < (*y) )
    return 1;
   
    else if( (*x) > (*y) )
    return 0;
   
    else {
		x++;
		y++;
		
		if( *x != '\0' && *y!='\0')
			return compare(x,y);
    }
    return 0;
}

struct node *create(struct node *root, char arr[]) {
    root = (struct node *)malloc(sizeof(struct node));
    char *temp = root->numPlate;
    temp = strcpy(temp, arr);
    root->left = NULL;
    root->right = NULL;
    return root;
}

struct node *insert(struct node *root, char arr[]) {
    if (root == NULL)
        root = create(root, arr);

    else {
        if (compare(root->numPlate, arr) == 1) {
            struct node *rightChild = insert(root->right, arr);
            root->right = rightChild;
            rightChild->parent = root;
        }

        else if (compare(root->numPlate, arr) == 0) {
            struct node *leftChild = insert(root->left, arr);
            root->left = leftChild;
            leftChild->parent = root;
        }
    }
    return root;
}

int Search(struct node *root, char arr[])
{
    if(root != NULL) {
        if(strcmp(root->numPlate, arr) == 0)
            return 1;

        else if(compare(root->numPlate, arr) == 0 ) {
            Path[strlen(Path)] = 'L';
            Search(root->left, arr);
        }

        else if(compare(root->numPlate, arr) == 1 ) {
            Path[strlen(Path)] = 'R';
            Search(root->right, arr);
        }
        else if(strcmp(root->numPlate, arr) != 0) {

        }
    }
}


int main(){
  char* firstLine=NULL;
  char* inputLine=NULL;
  size_t length=0, counter=0, plateLength=6;
  char choice, numberPlate[7];

  // Fetching only the first line of input.
  length = getline(&firstLine,&length,stdin);
  struct node *ROOT = NULL;

  // Parsing the string word by word. 
  while(counter<length){
    strncpy(numberPlate,&firstLine[counter],plateLength);
    numberPlate[plateLength] = '\0';
    counter += plateLength+1; // The +1 takes care of the space between words.
    // Call your BST Insert function here with argument: numberPlate
    ROOT = insert(ROOT, numberPlate);
  }

  // Main input handler to serve requests.
  while(getline(&inputLine, &length, stdin) != -1){
    sscanf(inputLine,"%c %s",&choice, numberPlate);
    if(choice=='S') {
      // Call your BST Search function here with argument: numberPlate
      int temp = Search(ROOT, numberPlate);
      if(temp == 1)
        printf("1 %s\n", Path);

        else 
        printf("0\n");
        int max = strlen(Path);
        for(int i=0; i<max; i++)
        Path[i] = '\0';
    }
    free(inputLine); inputLine=NULL;
    length=0;
  }
  return 0;
  
}
