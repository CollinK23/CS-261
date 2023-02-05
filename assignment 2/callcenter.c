#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "stack.h"


/*
 * Define your call struct here.
 */

struct caller{
	int callerId;
	char name[100];
	char reason[100];
};

/*
 * This function aks the user to input a number to determine the option they want to choose
 */
int userOptions(){
	int option;
	printf("1. Receive a New Call\n");
	printf("2. Answer a Call\n");
	printf("3. Current State of The Stack - Answered Calls\n");
	printf("4. Current State of The Queue - Calls to be Answered\n");
	printf("5. Quit\n");
	printf("Choose an Option: ");
	scanf("%d", &option); //Stores user input
	printf("\n");

	return option; //Returns selected option
}

/*
 * This function stores the callers information inside of a struct
 * The struct will then be added to the queue
 *
 * Params:
 *   queue - the queue that the struct will be added to
 *   callerNum - Caller ID that will be added to caller struct
 */
void receiveCall(struct queue* queue,int callerNum){
	//Create Char arrays for user inputs
	char newName[100]; 
	char newReason[100];

	printf("Enter Caller's Name: ");
	scanf("%s", newName); //Take in user input
	printf("\n");
	printf("Enter Call Reason: ");
	scanf("%s", newReason); //Take in user input

	struct caller* newCaller = malloc(sizeof(struct caller)); //Allocates memory for new caller struct

	//Sets values inside of the new caller struct
	newCaller->callerId = callerNum;
	strcpy(newCaller->name, newName); //Copies the Char array into the struct
	strcpy(newCaller->reason, newReason); //Copies the Char array into the struct
	printf("\n\n");
	queue_enqueue(queue, newCaller); //Adds new struct to the queue
	return;
}

/*
 * This function removes values from the queue and adds them to the stack
 * Information about the call will be displayed
 * Returns 1 if a new call is being answered, returns 0 if the queue is emtpy
 *
 * Params:
 *   queue - the queue that the struct will be removed from
 *   stack - the stack that the struct will be added to
 */
int answerQueue(struct queue* queue, struct stack* stack){

	//Check if any calls still need to be answered
	if (queue_isempty(queue) == 0){
		struct caller* newCaller = queue_dequeue(queue); //Removes value from queue and saves the struct
		if (stack_isempty(stack) == 0){
			free(stack_pop(stack)); //removes the last value that was previously in the stack
		}
		stack_push(stack, newCaller); //Adds the saved struct into the stack

		//Output information about the new call
		printf("Answering a Call\nCaller ID: %d\n", newCaller->callerId);
		printf("Name: %s\n", newCaller->name);
		printf("Reason: %s\n\n", newCaller->reason);

		return 1;
	}else {
		printf("The Queue is Empty\n\n");
		return 0;
	}
}

/*
 * This function shows how many calls have been answered
 * Information about the call will be displayed
 *
 * Params:
 *   stack - the stack that contains the information of the most recent call
 */
void printStack(struct stack* stack, int callsAnswered){
	//Checks if stack is empty
	if (callsAnswered > 0){
		struct caller* newCaller = stack_top(stack); //Copies value from stack into a struct for outputting info
		printf("Number of Calls Answered: %d\n", callsAnswered);
		printf("Last Call Answered\nCaller ID: %d\n", newCaller->callerId);
		printf("Name: %s\n", newCaller->name);
		printf("Reason: %s\n\n", newCaller->reason);
	}else {
		printf("No Calls Have Been Answered\n\n");
	}
	return;
}

/*
 * This function shows how many calls need to be answered
 * Information about the next call in the queue will be displayed
 *
 * Params:
 *   queue - The queue that contains the unanswered calls
 */
void printQueue(struct queue* queue){
	int callsLeft = queue_length(queue); //Check how many calls remaining in queue
	if (callsLeft > 0){
		struct caller* newCaller = queue_front(queue); //Copies struct at front of queue into new struct for outputting info

		printf("Number of Call's To Be Answered: %d\n", callsLeft);
		printf("Next Call in Queue\nCaller ID: %d\n", newCaller->callerId);
		printf("Name: %s\n", newCaller->name);
		printf("Reason: %s\n\n", newCaller->reason);
	} else {
		printf("No Calls In The Queue\n\n");
	}
	return;
}

/*
 * This function runs different functions based on the users input
 * Allocates and frees memory for stack and queue
 *
 */
int main(int argc, char const *argv[]) {
	struct queue* newQueue = queue_create(); //Creates new Queue
	struct stack* newStack = stack_create(); //Creates new Stack

	int callerNum = 0; //Caller ID number
	int callsAnswered = 0; //Number of calls answered

	while(1){
		int option = userOptions(); //User selects option from menu
		if (option == 1){
			callerNum++;
			receiveCall(newQueue, callerNum); //Add call to queue
		}
		else if (option == 2){
			int addCall = answerQueue(newQueue, newStack); //Remove call from queue and add to stack
			callsAnswered+= addCall; //Only increases if there was a call in the queue
		}
		else if (option == 3){
			printStack(newStack, callsAnswered); //Outputs latest call answered
		}
		else if (option == 4){
			printQueue(newQueue); //Outputs next call to be answered
		}
		else if (option == 5){
			//Frees all structs stored in the stack until it is empty
			while(stack_isempty(newStack) == 0){
				free(stack_pop(newStack));
			}
			//Frees all structs stored in the queue until it is empty
			while (queue_isempty(newQueue) == 0){
				free(queue_dequeue(newQueue));
			}
			queue_free(newQueue); //Frees queue
			stack_free(newStack); //Frees stack
			break;
		}
	}

  
	return 0;
}
