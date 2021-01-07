/* 
Assignment 5
Roll Number: CS19BTECH11026
Name: Naitik Malav

*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>

const int INF = 999;		//setting infinite to 999
int heapsize = 0;	//shows the current no. of nodes present in the binomial min heap tree or in an array

/* stores vertex number, weight(of type int) and pointer(of type struct node) */
struct node {
    int vertex;		//vertex index
	int weight;		//weight 
	struct node *next;		//pointer to the next node
};

/* creates node of a linked list */
struct node* CreateListNode(int v, int w) {
    struct node *temp = NULL;
    temp = (struct node*)malloc(sizeof(struct node));
    temp->vertex = v;
	temp->weight = w;
	temp->next = NULL;
    return temp;
}

/* by passing head(which is array[startVertex]->next) and data as a parameter we are adding data into the linked list */
struct node* InsertEdge(struct node *head, int vertex, int weight) {
    if (head == NULL)   
    	head = CreateListNode(vertex, weight);
    else 
        head->next = InsertEdge(head->next, vertex, weight);		//recursive call
	return head;
}

/* swap all the data stored at index1 and index2 in array PQ of type struct node */
void swap(struct node PQ[], int index1, int index2) {
	int temp = PQ[index1].weight;	//swapping weight
	PQ[index1].weight = PQ[index2].weight;
	PQ[index2].weight = temp;

	temp = PQ[index1].vertex;		//swapping vertex
	PQ[index1].vertex = PQ[index2].vertex;
	PQ[index2].vertex = temp;	
}

/* copy the data of passed Node and return an object of type struct node */
struct node copy(struct node Node) {
	struct node temp;
	temp.vertex = Node.vertex;
	temp.weight = Node.weight;
	return temp;
}

/* returns index of  right child of passed index which is at 2*(i+1) */
int getRCI(struct node PQ[], int N, int index) {
	if((2*(index+1) < heapsize) && index >= 0)
		return 2*(index+1);
	return -1;
}

/* returns index of left child of passed index which is at 2*i+1 */
int getLCI(struct node PQ[], int N, int index) {
    if((2*index+1 < heapsize) && index >= 0)
        return 2*index + 1;
    return -1;
}

/* returns index no. of array PQ whose vertex equals to passed vertex (i.e. PQ[index].vertex == vertex) */
int getIndex(struct node PQ[], int N, int vertex) {
  	for(int i=0; i<N; i++) {
		if(PQ[i].vertex == vertex)
			return i;
	}
}

/* returns parent of passed index which is at floor(i/2)-1 if index is even, otherwise at floor(i/2)*/
int getParent(int index) {
	if (index > 0) {
		if(index%2 == 0)
			return index/2 - 1;
		else 
			return index/2;
	}
	return -1;
}

/*sorts the passed array PQ according to the min heap rule */
void heapify(struct node PQ[],int N, int index) {
	int lci = getLCI(PQ, N, index);	//getting index of left child
	int rci = getRCI(PQ, N, index);	//getting index of right child
	int smallest = index;	//passed index is the smallest, that's why we call heapify after extracting it from root

	if ((lci <= heapsize) && (lci>0)) {
		if (PQ[lci].weight < PQ[smallest].weight) {
			smallest = lci;
		}
		/* if both of them have same weight, then higher priority will be given to the node whose vertex is smaller (ATQ) */
		else if (PQ[lci].weight==PQ[smallest].weight && PQ[lci].vertex<PQ[smallest].vertex) {
			smallest = lci;
		}
	}

	if ((rci <= heapsize && (rci>0))) {
		if (PQ[rci].weight < PQ[smallest].weight) {
			smallest = rci;
		}
		/* if both of them have same weight, then higher priority will be given to the node whose vertex is smaller (ATQ) */
		else if (PQ[rci].weight==PQ[smallest].weight && PQ[rci].vertex<PQ[smallest].vertex) {
			smallest = rci;
		}
	}

	/* it's unequal if above if's executed */
	if (smallest != index) {
		swap(PQ, smallest, index);		//swapping the data stored at position 'smallest' and 'index' of array PQ
		heapify(PQ, N, smallest);		//calling heapify recursively for the node at position 'smallest' in array PQ
	}
	return;
}

/* returns minimum weightage node present in the array */
struct node extractMin(struct node PQ[], int N) {
	/* minimum is at the 0th position */
	struct node minimum = copy(PQ[0]);
	PQ[0] = copy(PQ[heapsize-1]);		//copying heapsize-1 data to the 0th position		
	PQ[heapsize-1] = copy(minimum);		//moving 0th datas to the position heapsize-1 instead of deleting the	
	
	/*by decreasing heapsize means that we restrict our priority queue(PQ) to 0 to heapsize-1 */
	heapsize--;
	heapify(PQ, N, 0);	//heapify it
	return minimum;		//returning object minimum
}

/* inserting node with node.vertex = vertex and node.weight = weight in array according to binomial min heaps rule */
void insertHeap(struct node PQ[], int vertex, int weight) {
	PQ[heapsize].vertex = vertex;	//adding it to the position heapsize
	PQ[heapsize].weight = weight;

	int index = heapsize;
	while(index > 0) {
		int parent = getParent(index);
		if(PQ[parent].weight > PQ[index].weight) {	//comparing with parent
			swap(PQ, parent, index);
			index = parent;
		}
		/* priority given to the smaller index if their weight is */
		else if((PQ[parent].weight==PQ[index].weight) && (parent>index)) { 
			swap(PQ, parent, index);
			index = parent;
		}

		else {
			heapsize++;	//incrementing no. of heapsize as the no. of nodes are increased
			return;
		}
	}
	heapsize++;	//incrementing no. of heapsize as the no. of nodes are increased
}

/* decreasing the weightage of a node at position 'index' by setting it to 'weight' */
void decreaseKey(struct node PQ[], int N, int index, int weight) {
	PQ[index].weight = weight;	//setting the new weightage
	while((index>0) && (PQ[getParent(index)].weight > PQ[index].weight)) { //if parent's weight is morte then swap it
		swap(PQ, index, getParent(index));
		index = getParent(index);
	}
}

/* prints the path */
void printPath(int Parent[], int vertex)
{
    //If j is source
    if (Parent[vertex]==-1)
        return;

	printPath(Parent, Parent[vertex]);
	printf("%d ", vertex);
    
}

/* algorithm to calculate the shortest path from 's' to 't' 
prints the weight from 's' to 't' and then prints the vertexes visited to reach at 't'(in order)*/
void Dijkstra(struct node *array[], int N, int s, int t) {
	struct node PQ[N];		//array of type struct node which stores vertex as well as it's weight
	int distance[N];	//stores the final distance of each vertex
	int Parent[N];
	Parent[s] = -1;

	for(int i=0; i<N; i++) {
		if(i == s) {
			insertHeap(PQ, array[i]->vertex, 0);	//setting weightage of start point 's' as 0
			distance[i] = 0;
		}	
		else {
			insertHeap(PQ, array[i]->vertex, INF);	//setting weightage for the rest of vertices to infinity(or large value)
			distance[i] = INF;
		}	
	}

	/* this heapsize>0 basically means that while loop exectue until priority queue is not empty */
	while(heapsize>0) {
		struct node U = extractMin(PQ, N);	//getting minimum node from PQ 
		/* declaring pointer to the next of adjacency list whose head is same as U.vertex,
		this is basically because w(u,v) [i.e weight from u to v] is stored at V->weight */
		struct node *V = array[U.vertex]->next;	 

		/* traversing through all the nodes of the adjacency list */
		while(V != NULL) {
			if(PQ[getIndex(PQ, N, V->vertex)].weight > U.weight + V->weight) {
				decreaseKey(PQ, N, getIndex(PQ, N, V->vertex), U.weight+V->weight);
				distance[PQ[getIndex(PQ, N, V->vertex)].vertex] = U.weight + V->weight;

				if(PQ[getIndex(PQ, N, V->vertex)].vertex != s)
				Parent[PQ[getIndex(PQ, N, V->vertex)].vertex] = U.vertex;
			}
			V = V->next;
		}
	}
	if(distance[t] == INF)		//means suppose if they have no link, then in this case dist b/w them set to INF
		printf("-1\n");

	else{
		printf("%d %d ", distance[t], s);
		printPath(Parent, t);
		printf("\n");
	}
}

int main(){
	char choice;
	int numberOfVertices, startVertex, endVertex, weight;

	// Fetching number of vertices
	scanf("%d",&numberOfVertices);
	// Create your adjacency list's array of head vertices here.
	struct node* array[numberOfVertices];       //array of head vertices of adjacency list
	
	for(int i=0; i<numberOfVertices; i++)
		array[i] = CreateListNode(i,INF);	//declaring memory for each node
	
	while(scanf(" %c",&choice)!=-1) {
		if(choice == 'N'){
			char delimiter;
			scanf("%d", &startVertex);
			while(scanf("%d%d%c", &endVertex, &weight, &delimiter)) {
				// Add the edge (startVertex, endVertex) to your graph here
				array[startVertex]->next = InsertEdge(array[startVertex]->next, endVertex, weight);
				if(delimiter == '\n') 
					break; // Detecting end of line.
			}
		}
		else if(choice == 'D') {
			scanf("%d%d", &startVertex, &endVertex);
			Dijkstra(array, numberOfVertices, startVertex, endVertex);
		}

		else if(choice == 'G') {	//printing graph
			for(int i=0; i<numberOfVertices; i++){
				struct node *temp = array[i];
				while(temp!=NULL) {
				//	printf("%d(%d)",temp->vertex, temp->weight);
					temp = temp->next;
				}
				//printf("\n");
			}
		}
	}
	return(0); 
}