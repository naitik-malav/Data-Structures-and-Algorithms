/* 
Assignment 4
Roll Number: CS19BTECH11026
Name: Naitik Malav

*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct node {
    int vertex;		//vertex index
	struct node *next;		//pointer to the next node
};

struct queue {
	struct node *rear;		//pointer to the last node of Queue
	struct node *front;		//pointer to the first node of Queue
};

/* creates node of a linked list */
struct node* CreateListNode(int data) {
    struct node *temp = NULL;
    temp = (struct node*)malloc(sizeof(struct node));
    temp->vertex = data;
	temp->next = NULL;
    return temp;
}

struct node *array[10000000];

/* by passing head(which is array[startVertex]->next) and data as a parameter we are adding data into the linked list 
in ascending order, i.e. adjacency list is in sorted order */
struct node* InsertEdge(struct node *head, int data) {
    if (head == NULL)   
    	head = CreateListNode(data);

    else {
        if(data > head->vertex)
            head->next = InsertEdge(head->next, data);		//recursive call

        else if(data < head->vertex) { 	//it should be added just before the head
            struct node *temp = NULL;
            temp = CreateListNode(data);
            temp->next = head;	//pointing it's next to head
            return temp;		//newly linked list
        }
    }
	return head;
}

/*adding vertex to the last of the passed Q */
struct queue* enQueue(struct queue *Q, int vertex) {
	struct node *temp = NULL;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->vertex = vertex;
    temp->next = NULL;
    
    if (Q->rear == NULL){
        Q->rear = temp;
        Q->front = Q->rear;
    }	

    else {
        Q->rear->next = temp; 
        Q->rear = temp;
    }
	return Q;
}

/*deleting the front of the Queue */
struct queue* deQueue(struct queue* Q) 
{  
    if (Q->front == NULL)   // If queue is empty return NULL.
        return NULL; 
  
	else {
		struct node *temp = Q->front; 
		Q->front = temp->next; 
		free(temp);
		
        if (Q->front == NULL) // If front becomes NULL, then change rear also as NULL 
			Q->rear = NULL; 
		return Q; 
	}
}

/* passing complete graph, numberOfVertices, startvertex */
void BreadthFirstSearch(int N, int vertex) {
    struct queue *Q = (struct queue *)malloc(sizeof(struct queue)); //Queue which stores vertices
    Q->front = NULL;
    Q->rear = NULL;

    bool color[N];   //represents the visited status of the vertex(false if not visited, true if visited)        
    for(int i=0; i<N; i++)
        color[i] = false;     //false for not visited
			
	struct node *temp = array[vertex];  //getting address of the head of adjacency list started with vertex 
	while(temp != NULL) {
        if(color[temp->vertex] == false){   //enqueue the particular node of adjacency list only if it is not visited
            Q = enQueue(Q, temp->vertex);
            color[temp->vertex] = true; //then changes it to true(means now it's visited)
        }
		temp = temp->next;      //traversing to the other nodes of adjacency list 
	}
	printf("%d ", Q->front->vertex);        //printing head
	Q = deQueue(Q);     //dequeing head

    /*doing above procedure for the rest of the vertices present in the queuue */
	while(Q->front != NULL) {
		struct node *temp = array[Q->front->vertex];  //getting address of the head of adjacency list started with Q->front->vertex
		while(temp != NULL) {
			if(color[temp->vertex] == false){   //enqueue particular node only if it is not visited
                Q = enQueue(Q, temp->vertex);
                color[temp->vertex] = true;     //then changes it to true(means now it's visited)
            }
            temp = temp->next;
		}
		printf("%d ", Q->front->vertex);
		Q = deQueue(Q); //dequeing head of queue
	}
}

int main(){
	char choice;
	int numberOfVertices, startVertex, endVertex;

	// Fetching number of vertices
	scanf("%d",&numberOfVertices);
	// Create your adjacency list's array of head vertices here.
	
	for(int i=0; i<numberOfVertices; i++)
		array[i] = CreateListNode(i);	//declaring memory for each node
	
	while(scanf(" %c",&choice)!=-1) {
		if(choice == 'N'){
			char delimiter;
			
			scanf("%d", &startVertex);
			while(scanf("%d%c", &endVertex, &delimiter)) {
				// Add the edge (startVertex, endVertex) to your graph here
				
				/* as graph is undirected so two calls, one for u,v and another one for v,u */
				array[startVertex]->next = InsertEdge(array[startVertex]->next, endVertex);
				array[endVertex]->next = InsertEdge(array[endVertex]->next, startVertex);
				if(delimiter == '\n') 
					break; // Detecting end of line.
			}
		}
		else if(choice == 'B') {
			scanf("%d",&startVertex);
			// Call BFS on your graph starting from startVertex here.
			BreadthFirstSearch(numberOfVertices, startVertex);
			printf("\n");
		}
	}
	return(0); 
}