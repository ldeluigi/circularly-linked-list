#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * DEFINE LLIST_EXIT_ON_ERROR TO EXIT ON EVERY ERROR AFTER MESSAGE PRINT
 */

typedef struct _node
{
	void * value;
	struct _node *next;
	struct _node *previous;
} node;

typedef struct _List
{
	node *head;
	int length;
	node *current;
	int currentIndex;
} List;

/**
 * Prints last error message, if present, and clears error buffer.
 */
void print_last_error();

/**
 * Returns last error message, if present, and clears error buffer.
 */
char * get_last_error();

/**
 * Returns 1 if an error occurred.
 */
int failed();

/**
 * Creates an empty list with malloc.
 * Returns NULL on error.
 */
List * newList();

/**
 * Creates an empty list.
 * Returns NULL on error.
 */
List newListL();

/**
 * Returns 1 on success, 0 on failure.
 * Adds the given item to the head of the list.
 */
int push(void * value, List * list);

/**
 * Returns NULL on failure. It removes and returns the first value as a
 * void*.
 */
void* pop(List * list);

/**
 * Returns 1 on success, 0 on failure.
 * Adds the given item to the tail of the list.
 */
int enqueue(void * value, List * list);

/**
 * Returns NULL on failure.
 * See pop for the behavior.
 */
void* dequeue(List * list);

/**
 * Returns the current value pointed by the list internal pointer
 * as a void*.
 */
void* getCurrent(List * list);

/**
 * Resets the list internal pointer to the default value (-1).
 * This is usefult before calling the iterate method in order
 * to initialize the iteration.
 */
void reset(List * list);

/**
 * Returns 1 if the list can be iterated further (without looping),
 * and if so sets the internal pointer at the next position.
 * Returns 0 if an error occurred or the list couldn't be iterated
 * further.
 * 
 * Example of a function that prints a list of integers:
 * void pl(List * list)
 * {
 * 		reset(list);
 * 		while(iterate(list))
 * 		{
 * 			printf("[%d] = %d\n", list->currentIndex, *((int *)getCurrent(list)));
 * 		} 
 * }
 */
int iterate(List * list);

/**
 * Deletes all the elements of a list.
 */
void empty(List * list);

/**
 * Calls empty(list) and then free(list).
 */
void freeList(List * list);

/**
 * Returns the current inedx pointed by the list internal pointer.
 */
int getCurrentIndex(List * list);

/**
 * Returns the number of items contained in the list.
 */
int length(List * list);

/**
 * Returns 1 on success, 0 on failure.
 * Adds the given item in the given position of the list.
 * If index = length(list) the item is added to the tail.
 */
int add(int index, void * value, List * list);

/**
 * Returns the element at position index in the list.
 * Bounds are checked.
 * Returns NULL on error.
 */
void * get(int index, List * list);

/**
 * Returns 1 on success, 0 on failure.
 * Sets to value the given index.
 * The element at index must be already present.
 */
int set(int index, void * value, List * list);

/**
 * Returns NULL on failure.
 * Retrieves and removes the item at the given position.
 */
void* removeAt(int index, List * list);

/**
 * Removes length elements from start, inclusive.
 */
void cut(int startInclusive, int length, List * list);
