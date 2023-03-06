/*
 * In this file, you'll implement Dijkstra's algorithm to find the least
 * expensive paths in the graph defined in `airports.dat`.  Don't forget to
 * include your name and @oregonstate.edu email address below.
 *
 * Name:
 * Email:
 */

#include <stdio.h>
#include <stdlib.h>
#include "dynarray.h"
#include <limits.h>

#define DATA_FILE "airports.dat"
#define START_NODE 0


/*
 * This is the structure that represents the priority queue nodes.
 * They contain the cost, previous location, and current location for the nodes
 */
struct pq_node{
	int prevLoc;
	int cost;
	int currLoc;
};

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq{
	struct dynarray* dynarray;
};

/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
	/*
	 * FIXME: 
	 */
	struct pq* newPq = malloc(sizeof(struct pq)); //Allocate memory for new pq struct
	newPq->dynarray = dynarray_create(); //Allocate memory for new dynamic array
	return newPq;
}

/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
	/*
	 * FIXME: 
	 */
	dynarray_free(pq->dynarray); //Frees memory from dynamic array
	free(pq); //Frees memory from priority queue
	return;
}

/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
	/*
	 * FIXME: 
	 */
	if (dynarray_size(pq->dynarray) == 0){
		return 1;
	}
	return 0;
}

/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   cost - The cost between the airports
 *   prevLoc - previous airport number
 *   currLoc - current airport number
 */
void pq_insert(struct pq* pq, int cost, int prevLoc, int currLoc) {
	/*
	 * FIXME: 
	 */
	struct pq_node* node = malloc(sizeof(struct pq_node)); //Allocates memory for new pq node
	node->cost = cost; //Sets priority of node
	node->currLoc = currLoc;
	node->prevLoc = prevLoc;

	dynarray_insert(pq->dynarray, node); //Inserts the node into the dynamic array
	int idx = dynarray_size(pq->dynarray) - 1; //Index of inserted node
	int parentIdx = ((idx) / 2); //Index of parent node
	struct pq_node* parent = dynarray_get(pq->dynarray, parentIdx); //parent node

	//Swaps the inserted node with its parent until the parent priority is smaller
	while (parent->cost > cost){
		dynarray_swap(pq->dynarray, idx, parentIdx); //Swaps parent and inserted node
		idx = parentIdx; //Updates inserted node index
		parentIdx = ((idx) / 2); //Updates parent index
		parent = dynarray_get(pq->dynarray, parentIdx); //Updates parent node
	}

	return;
}

/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
int pq_first(struct pq* pq) {
	/*
	 * FIXME: 
	 */
	struct pq_node* node = dynarray_get(pq->dynarray, 0);
	return node->cost;
}

/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {
	/*
	 * FIXME: 
	 */
	struct pq_node* temp = dynarray_get(pq->dynarray, 0); //Stores value being removed

	dynarray_swap(pq->dynarray, 0, dynarray_size(pq->dynarray) - 1); //Swaps node being removed with last node in pq
	dynarray_remove_tail(pq->dynarray); //Removes last node
	int size = dynarray_size(pq->dynarray); //Resizes the dynamic array

	int curr = 0;
	int min = curr; //min is node that the current node will be swapped with
	//Sorts the new root into correct position
	while(curr < size){
		int left = 2 * curr + 1;
		int right = 2 * curr + 2;
		if (left < size && 
		((struct pq_node*)dynarray_get(pq->dynarray, left))->cost < 
		((struct pq_node*)dynarray_get(pq->dynarray, min))->cost){
			min = left; //Sets min equal to left child if it has lower cost than current node
		}
		if (right < size && 
		((struct pq_node*)dynarray_get(pq->dynarray, right))->cost < 
		((struct pq_node*)dynarray_get(pq->dynarray, min))->cost){
			min = right; //Sets min equal to right child if it has lower cost than left child or current node
		}
		if (min != curr){
			dynarray_swap(pq->dynarray, min, curr); //Swaps current node with child node
			curr = min;
		}else{
			break; //If no swaps need to be done, the node is in correct position
		}
	}

	return temp;
}

/*
 * This function recursively prints the airport path
 *
 * Params:
 *   prev[] - the array that contains the previous location of each node
 */
void printPath(int prev[], int i) {
    //Start of the path
	if (prev[i] == -1)
        return;

    printPath(prev, prev[i]);
    printf("->%d", i);
}

/*
 * This function prints the cost and path to each node
 */
void printTotal(int cost[], int prev[], int n_nodes) {
    for (int i = 0; i < n_nodes; i++) {
        printf("\nEdge From: 0 -> %-8dCost: %-8dPath: 0", i, cost[i]);
        printPath(prev, i);
    }
	printf("\n");
}


int main(int argc, char const *argv[]) {
	/*
	 * Open file and read the first two int: num of nodes, num of edges
	 */
	int n_nodes, n_edges;
	FILE* file = fopen(DATA_FILE, "r");
	fscanf(file, " %d %d", &n_nodes, &n_edges);



	
	/*
	 * Write your code here to find the
	 * least-cost paths from node 0 to all other nodes in the graph.  Make sure
	 * to print out the least-cost paths you find at the end.
	 *
	 * FIXME: 
 	 */
	int source, destination, price; //Intialize the source, destination, and price of each flight
	int matrix[n_nodes][n_nodes]; //Intialize adjacency matrix
	int cost[n_nodes]; //Intializes cost array
	int prev[n_nodes]; //Intializes previous node array

	//Zero-intialize matrix
	for (int i = 0; i < n_nodes; i++){
		for (int j = 0; j < n_nodes; j++){
			matrix[i][j] = 0;
		}
	}
	
	//Reads values from airports.dat into the matrix
	for (int i = 0; i < n_edges; i++){
		fscanf(file, " %d %d %d", &source, &destination, &price);
		matrix[source][destination] = price;
	}

	//Intializes values of cost and prev array
	for (int i = 0; i < n_nodes; i++){
		cost[i] = INT_MAX; //infinity
		prev[i] = -1; //Node hasn't been visited
	}

	struct pq* newPq = pq_create(); //Initializes new priority queue
	pq_insert(newPq, 0, -1, START_NODE); //Inserts starting node into the priority queue

	int n = START_NODE; //Intialize current location

	while(pq_isempty(newPq) == 0){
		int c = pq_first(newPq); //Cost of cheapest flight in priority queue
		struct pq_node* newNode = pq_remove_first(newPq); //Removes the cheapest flight from priority queue
		n = newNode->currLoc; //Updates current location
		int prevN = newNode->prevLoc; //sets the previous node location
		free(newNode); //Frees memory allocated to the node that was removed

		if (c < cost[n]){
			cost[n] = c; //If cost is lower than current cost[n], update with new cost
			prev[n] = prevN; //Updates the previous node to the new previous node

			//For loop iterates through the matrix to find neighbor nodes
			for (int i = 0; i < n_nodes; i++){
				//Path exists if cost is grater than 0
				if (matrix[n][i] > 0){
					pq_insert(newPq, matrix[n][i] + c, n, i); //Inserts neighbor nodes into the priority queue
				}
			}
		}
	}

	printTotal(cost, prev, n_nodes);
	pq_free(newPq); //Frees memory allocated to the priority queue

	fclose(file);

	 
  return 0;
}
