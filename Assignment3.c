/* 
Assignment 3
Roll Number: CS19BTECH11026
Name: Naitik Malav

*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct node {
    char numPlate[7];
    struct node *left;
    struct node *right;
    struct node *parent;
};

/* this time I have modified compare function..it is not same as Assignment0 and Assignment1
compare(x,y): 1.now it returns -1 if x>y
            2. returns 1 if x<y
           3. returns 0 if x=52y */
int compare(char *x, char *y) {
	if( (*x) < (*y) )
    return 1;
   
    else if( (*x) > (*y) )
    return -1;
   
    else {
		x++;
		y++;
		
		if( *x != '\0' && *y!='\0')
			return compare(x,y);
    }
    return 0;
}

//creates a node
struct node *create(struct node *root, char arr[]) {
    root = (struct node *)malloc(sizeof(struct node));
    char *temp = root->numPlate;
    temp = strcpy(temp, arr);
    root->left = NULL;
    root->right = NULL;
    return root;
}

// inserting numberPlate recursively in BST and also linking parent pointer 
struct node *insert(struct node *root, char arr[]) {
    if (root == NULL)
        root = create(root, arr);

    else {
        if (compare(root->numPlate, arr) == 1) {       //arr > root->numPlate
            struct node *rightChild = insert(root->right, arr);
            root->right = rightChild;
            rightChild->parent = root;      //linking parent pointer
        }

        else if (compare(root->numPlate, arr) == -1) {      //arr < root->numPlate
            struct node *leftChild = insert(root->left, arr);
            root->left = leftChild;
            leftChild->parent = root;       //linking parent pointer
        }
    }
    return root;
}

/* prints path of the arr if it is present in BST */
void Path(struct node *root, char arr[])
{
    if(root != NULL) {
        if(compare(root->numPlate, arr) == 0)
            return;     //breaking recursion on successful completion

        else if(compare(root->numPlate, arr) == -1 ){
            printf("L");
            Path(root->left, arr);
        }

        else if(compare(root->numPlate, arr) == 1 ){
            printf("R");
            Path(root->right, arr);
        }
    }
}

/*search the passed arr in BST and returns 1 for successful search.*/
int Search(struct node *root, char arr[])
{
    if(root != NULL) {
        if(compare(root->numPlate, arr) == 0)
            return 1;       //search successful

        else if(compare(root->numPlate, arr) == -1 )
            Search(root->left, arr);   

        else if(compare(root->numPlate, arr) == 1 )
            Search(root->right, arr);
    }
    else    //if not present in BST
    return 0;
}

/*returns address of the node which is just smaller than passed numberPlate 
1. I want to point out one info that I found out here - This below function is also an predecessor but in a diff style
2. it returns NULL only in 1 case if your entered arr is less than the minimum of tree*/ 
struct node *GetImmediateSmall(struct node *root, char arr[]) {
    if(root == NULL)
        return NULL;
    
    else if(compare(root->numPlate, arr) == 1) {
        struct node *temp = GetImmediateSmall(root->right, arr);

        if(temp == NULL)
            return root;
        else 
            return temp; 
    }

    else if(compare(root->numPlate, arr) == -1)
        return GetImmediateSmall(root->left, arr);
}

/* return the address of node whose numPlate is same as arr */
struct node *GetAddress(struct node *root, char arr[]) {
    struct node *temp = NULL;
    if(root != NULL) {
        if(compare(root->numPlate, arr) == -1 && root->left!=NULL){    //arr is less than root->numPlate
            temp = GetAddress(root->left, arr);
            return temp;
        }
            
        else if(compare(root->numPlate, arr) == 1 && root->right!=NULL){    //arr is greater than root->numPlate
            temp = GetAddress(root->right, arr);
            return temp;
        }
        return root; 
    }
}

/* return the address of node whose value is minimum i.e. left most node */
struct node* minimum(struct node *root) {
  while(root->left != NULL)
    root = root->left;
  return root;
}

/* return the address of node whose value is maximum i.e. right most node */ 
struct node* maximum(struct node *root) {
  while(root->right != NULL)
    root = root->right;
  return root;
}

/* return the char ptr to the numPlate which is successor of passed arr */
char *successor(struct node *root, char arr[]) {
    //if arr is present in BST
    if(Search(root, arr) == 1) {
        struct node *NODE = GetAddress(root, arr);      //getting address of the node where arr is located in BST
        struct node *MAX = maximum(root);   //getting address of the node which has numberPlate with max ASCII value

        if(compare(MAX->numPlate, NODE->numPlate) == 0)   //in this case successor doesn't not exist
            return "0";

        else if(NODE->right != NULL)    //here successor is minimum of right subtree of NODE
            return minimum(NODE->right)->numPlate;

        else if(NODE->right == NULL) {      //case 2
            struct node *Child = NODE;
            struct node *Parent = NODE->parent;
            
            while(1) {
                //if Parent->left is same as child then in this case Child will be x and and Parent is its parent.
                if(Parent->left != NULL && compare(Parent->left->numPlate, Child->numPlate) == 0)
                    return Parent->numPlate; //x is left child of Parent, so Parent is successor

                //if Parent->left and child both are different then set Child to Parent, and Parent to Parent->parent 
                else {
                    Child = Parent;
                    Parent = Parent->parent;
                }
            }
        }
    }
    
    /* if arr is not present in BST then lets find out the immediate smaller numberPlate than the arr, and here 
    successor of immediate smaller plate is also the successor of arr */
    else if(Search(root, arr) == 0) {
        struct node *NODE = GetImmediateSmall(root, arr);
        successor(root, NODE->numPlate);    //calling successor func recursively for immediate smaller numberPlate
    }
}

/* prints the value of predecessor of passed numberPlate */
void predecessor(struct node *root, char arr[]) {
    //if arr is present in BST
    if(Search(root, arr) == 1) {
        struct node *NODE = GetAddress(root, arr);  //getting its address
        struct node *MIN = minimum(root);   //getting address of smallest element which is left most

        if(compare(MIN->numPlate, NODE->numPlate) == 0) {   
            /*if smallest element and passed numberPlate both are same then its predecessor cannot exist */
            printf("0\n");
            return;
        }

        else if(NODE->left != NULL) //largest element in its left subtree is successor
            printf("%s\n", maximum(NODE->left)->numPlate);

        /* In this case I'm finding out the immediate smaller numberPlate than arr which is it's predecessor
        with the help of previously wrote func GetImmediateSmall */
        else if(NODE->left == NULL)
            printf("%s\n", GetImmediateSmall(root, arr)->numPlate);            
    }

    //if it is not present in BST
    else if(Search(root, arr) == 0) {
        /*again just find immediate smaller number plate and that will be it's predecessor by definition
        according to slides */
        struct node *NODE = GetImmediateSmall(root, arr); 
        if(NODE != NULL)    
            printf("%s\n", NODE->numPlate);

        else    //NULL if passed arr is smaller than smallest numberPlate
            printf("0\n");    
    }
} 

/*return the no. of children in passed BST */
int childCTR(struct node *root) {
    if(root->left==NULL && root->right==NULL)
        return 0;
    else if(root->left==NULL && root->right!=NULL)
        return 1;
    else if(root->left!=NULL && root->right==NULL)
        return 1;
    else if(root->left!=NULL && root->right!=NULL)
        return 2;
}

/*deletes the node */
struct node *delete(struct node *root, char arr[]) {
    if(root == NULL)    //base case
        return root;

    if (compare(root->numPlate, arr) == -1) {     //if arr is smaller than root->numPlate
        root->left = delete(root->left, arr);
        if(root->left != NULL)      //linking back parent pointer
            root->left->parent = root;
    }
  
    else if (compare(root->numPlate, arr) == 1) {    //if arr is greater
        root->right = delete(root->right, arr); 
        if(root->right != NULL) //linking back parent pointer 
            root->right->parent = root;
    }
  
    else
    { 
        /*node with one child or no child*/
        if(root->right==NULL) {
            struct node *Temp = root->left;
            free(root);
            return Temp;
        }

        else if (root->left==NULL) {
            struct node *Temp = root->right;
            free(root);
            return Temp;
        }
        /*node with 2 child*/
        char *Splate = successor(root, arr);        //successor's numPlate 
            struct node *S = GetAddress(root, Splate);      //sucessor's address
            // Copying successor's content to this node 
            for(int i=0; i<6; i++, Splate++)
                root->numPlate[i] = (*Splate);
            root->numPlate[6] = '\0'; 
            root->right = delete(root->right, root->numPlate); //call delete function for successor
            if(root->right != NULL) //linking parent pointer back
                root->right->parent = root;
    } 
    return root; 
}

/*prints inorder of BST */
void Inorder(struct node* root) 
{ 
    if (root == NULL) 
        return; 
    Inorder(root->left); 
    printf("%s ", root->numPlate); 
    Inorder(root->right); 
} 

/*prints Postorder of BST */
void Postorder(struct node *root) 
{ 
    if (root == NULL) 
        return; 
    Postorder(root->left); 
    Postorder(root->right); 
    printf("%s ", root->numPlate); 
} 

int main(){
  char choice, numberPlate[7];
  _Bool requests = 0;
  struct node *ROOT = NULL;   //root of the tree
  // Fetching till we hit the first request
   while(scanf("%s",numberPlate)!=-1){
    if(!requests){
      if(strlen(numberPlate) == 1){ // Detecting start of request lines.
	choice = numberPlate[0];
	requests = 1;
      }
      else{
        ROOT = insert(ROOT, numberPlate);
	// *** Call your insert function here with argument numberPlate ***
      }
    }
    else break; // choice and numberPlate have values to be processed!!
   }
      
   do{ // Ugly do-while to process first request line before first scanf.
    if(choice == 'S'){
    //*** Call your search function here with argument numberPlate ***
        if(Search(ROOT, numberPlate) == 1){  //if numberPlate present in tree
            if(compare(ROOT->numPlate, numberPlate) == 0)   //if it is ROOT then no need to print path
                printf("1");

            else {
                printf("1 ");
                Path(ROOT, numberPlate);        //otherwise print path
            }      
        }
        else if(Search(ROOT, numberPlate) == 0)  //if not present in BST
        printf("0");    //print 0 for unsuccesful search
        printf("\n");
    }
    
    else if(choice == '<'){
    //*** Call your predecessor function here with argument numberPlate ***
    predecessor(ROOT, numberPlate);
    }
    
    else if(choice == '>'){
    //*** Call your successor function here with argument numberPlate ***
    printf("%s\n", successor(ROOT, numberPlate));
    }
    
    else if(choice == '+'){
        if(Search(ROOT, numberPlate) == 0)
        ROOT = insert(ROOT, numberPlate);
    }
    
    else if(choice == '-'){
        if (Search(ROOT, numberPlate) == 0) //if not present in BST
            printf("-1\n");

        else {
            if(childCTR(GetAddress(ROOT, numberPlate)) > 0) {   //if children are greater than 0
                if(childCTR(GetAddress(ROOT, numberPlate)) == 1) {  //in this case it's child is going to replace node
                    if(GetAddress(ROOT, numberPlate)->left == NULL) {
                        printf("%d ", childCTR(GetAddress(ROOT, numberPlate)));  //printing no. of children
                        printf("%s\n", GetAddress(ROOT, numberPlate)->right->numPlate); //right child going to replace it
                        ROOT = delete(ROOT, numberPlate);    
                    }
                    else if(GetAddress(ROOT, numberPlate)->right == NULL) {
                        printf("%d ", childCTR(GetAddress(ROOT, numberPlate)));  //printing no. of children
                        printf("%s\n", GetAddress(ROOT, numberPlate)->left->numPlate); //left child going to replace it
                        ROOT = delete(ROOT, numberPlate);    
                    }
                }

                else {  //if it has 2 child then inorder successor is going to replace it
                    char *Splate = successor(ROOT, numberPlate);    //copying successor's plate
                    struct node *S = GetAddress(ROOT, Splate);  //getting successor's address
                    printf("%d ", childCTR(GetAddress(ROOT, numberPlate)));  //printing no. of children
                    printf("%s\n", Splate);     //printing successor
                    ROOT = delete(ROOT, numberPlate);       //deleting numberPlate
                }
            }

            else {      //if it has 0 children
            printf("0\n");
            ROOT = delete(ROOT, numberPlate);   //simply delete the node as it has no successor
            }
        }
    }  
    else if(choice == 'I'){     //printing inorder
        Inorder(ROOT);
        printf("\n");
    }
    else if(choice == 'P'){     //printing postorder
        Postorder(ROOT);
        printf("\n");
    } 
   }while(scanf("%*[\n]%c %6s",&choice, numberPlate)!=-1); 
   return(0);  
}
