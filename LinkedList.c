/**
 * Implementation of the ADT Circular Doubly Linked List in C.
 * Written by Luca Deluigi, 2018.
 * 
 */
#include "LinkedList.h"

static void dump_error(char * message);

static char last_error[128] = "";
static int error = 0;

static node* makeNode(void* val)
{
	node *newNode = (node *) malloc(sizeof(node));
	if (newNode == NULL)
	{
		dump_error("malloc failed");
		return NULL;
	}
	newNode->value = val;
	newNode->previous = newNode;
	newNode->next = newNode;
	return newNode;
}

static void resetPointer(List * list)
{
	list->currentIndex = -1;
    list->current = NULL;
}

static int insertAtHead(void * value, List * list)
{
	node *newNode = makeNode(value);
	node * tail;
	
	if (newNode == NULL) {
		return 0;
	}

    if (list->head==NULL)
    {
        list->head = newNode;
        list->length = 1;
    }
    else
    {
		tail = list->head->previous;
        newNode->next = list->head;
        newNode->previous = tail;
        tail->next = newNode;
        list->head->previous = newNode;
        list->head = newNode;
        list->length++;
	}
	resetPointer(list);
	return 1;
}

static int insertAtTail(void * value, List * list)
{
    node *newNode = makeNode(value);
	node * tail;
	
	if (newNode == NULL) {
		return 0;
	}
	
    if (list->head==NULL)
    {
        list->head = newNode;
        list->length = 1;
        list->currentIndex = 0;
        list->current = newNode;
    }
    else
    {
		tail = list->head->previous;
        newNode->next = list->head;
        newNode->previous = tail;
        tail->next = newNode;
        list->head->previous = newNode;
        list->length++;
    }
    resetPointer(list);
    return 1;
}

static node * obtain(int index, List * list)
{
	int i;
	node *temp = list->head;
	index = index % list->length;
	if (index < list->length / 2)
	{
		for (i = 0; i < index; i++)
		{
			temp = temp->next;
		}
	}
	else
	{
		for (i = list->length - index; i > 0; i--)
		{
			temp = temp->previous;
		}
	}
	return temp;
}

/**
 * Returns the element at position index in the list.
 * Bounds are checked.
 * Returns NULL on error.
 */
void * get(int index, List * list)
{
	if (list == NULL)
	{
		dump_error("list was a NULL pointer");
		return NULL;
	}
	if (index < 0 || index >= list->length)
	{
		dump_error("index out of bounds");
		return NULL;
	}
	return obtain(index, list)->value;
}

/**
 * Returns 1 on success, 0 on failure.
 * Sets to value the given index.
 * The element at index must be already present.
 */
int set(int index, void * value, List * list)
{
	if (list == NULL)
	{
		dump_error("list was a NULL pointer");
		return 0;
	}
	if (index < 0 || index >= list->length)
	{
		dump_error("index out of bounds");
		return 0;
	}
	obtain(index, list)->value = value;
	return 1;
}

static int insertAt(void * value, List * list, int index)
{
	node *newNode = makeNode(value);
	if (newNode == NULL) {
		return 0;
	}
	
	if (index == 0)
    {
        return insertAtHead(value, list);
    }
    else if (index == list->length)
    {
		return insertAtTail(value, list);
	}
	else
    {
		node *place = obtain(index, list);
		place->previous->next = newNode;
		newNode->previous = place->previous;
		newNode->next = place;
		place->previous = newNode;
		list->length++;
    }
    resetPointer(list);
    return 1;
}

/**
 * Returns 1 on success, 0 on failure.
 * Adds the given item in the given position of the list.
 * If index = length(list) the item is added to the tail.
 */
int add(int index, void * value, List * list)
{
	if (list == NULL)
	{
		dump_error("list was a NULL pointer");
		return 0;
	}
	if (index < 0 || index > list->length)
	{
		dump_error("index out of bounds");
		return 0;
	}
	return insertAt(value, list, index);
}

/**
 * Returns the number of items contained in the list.
 */
int length(List * list)
{
	return list->length;
}

/**
 * Returns 1 on success, 0 on failure.
 * Adds the given item to the head of the list.
 */
int push(void * value, List * list)
{
	if (list == NULL)
	{
		dump_error("list was a NULL pointer");
		return 0;
	}
	return insertAtHead(value, list);
}

/**
 * Returns 1 on success, 0 on failure.
 * Adds the given item to the tail of the list.
 */
int enqueue(void * value, List * list)
{
	if (list == NULL)
	{
		dump_error("list was a NULL pointer");
		return 0;
	}
	return insertAtTail(value, list);
}

static void isolateNode(node * temp)
{
    temp->next = temp;
    temp->previous = temp;
}

static node* behead(List * list)
{
    node *temp = list->head;
    node *tail;

    if (list->head == NULL || list->length == 0)
    {
		list->length = 0;
		resetPointer(list);
		list->head = NULL;
		return NULL;
	}

	tail = list->head->previous;
	if (tail == list->head)
	{
		list->length = 0;
		list->head = NULL;
	}
	else
	{
		tail->next = list->head->next;
		list->head = list->head->next;
		list->head->previous = tail;
		list->length--;
	}
    resetPointer(list);
    isolateNode(temp);
    return temp;
}

/**
 * Returns NULL on failure. It removes and returns the first value as a
 * void*.
 */
void* pop(List * list)
{
	node *temp = behead(list);
	void *result;
	if (temp == NULL)
	{
		dump_error("list was already empty");
		return NULL;
	}
	result = temp->value;
	free(temp);
	return result;
}

/**
 * Returns NULL on failure.
 * See pop for the behavior.
 */
void* dequeue(List * list)
{
	return pop(list);
}

/**
 * Creates an empty list with malloc.
 * Returns NULL on error.
 */
List * newList()
{
	List *list = (List *) malloc(sizeof(List));
	if (list == NULL)
	{
		dump_error("malloc failed");
		return NULL;
	}
	list->head = NULL;
	list->length = 0;
	resetPointer(list);
	return list;
}


/**
 * Returns 1 if the list can be iterated further,
 * and if so sets the internal pointer at the next position.
 * Returns 0 if an error occurred or the list couldn't be iterated
 * further.
 */
int iterate(List * list)
{
	if (list->length == 0 || list->head == NULL)
	{
		list->length = 0;
		list->head = NULL;
		return 0;
	}
	
	if (list->currentIndex < -1)
	{
		dump_error("Unexpected value of currentIndex");
		return 0;
	}

	if (list->currentIndex == -1)
	{
		list->currentIndex = 0;
		list->current = list->head;
		return 1;
	}

	if (list->currentIndex < list->length)
	{
		list->currentIndex++;
		list->current = list->current->next;
		if (list->currentIndex == list->length)
		{
			return 0;
		}
		return 1;
	}

	if (list->currentIndex == list->length)
	{
		return 0;
	}

	dump_error("Unexpected value of currentIndex");
	return 0;
}

static void* del(int index, List * list)
{
	node * target;
	void * result;
	if (index == 0)
	{
		target = behead(list);
		result = target->value;
		free(target);
		return result;
	}
	target = obtain(index, list);
	target->previous->next = target->next;
	target->next->previous = target->previous;
	result = target->value;
	free(target);
	list->length--;
	resetPointer(list);
	return result;
}

/**
 * Returns NULL on failure.
 * Retrieves and removes the item at the given position.
 */
void* removeAt(int index, List * list)
{
	if (list == NULL)
	{
		dump_error("list was a NULL pointer");
		return NULL;
	}
	if (index < 0 || index >= list->length)
	{
		dump_error("index out of bounds");
		return NULL;
	}
	return del(index, list);
}

static void remcut(int startInclusive, int length, List * list)
{
	node * temp, *next;
	node *first = obtain(startInclusive, list)->previous;
	node *last = obtain(startInclusive + length, list);
	if (length == 0)
		return;
	for (temp = first->next; temp != last;)
	{
		next = temp->next;
		free(temp);
		temp = next;
	}
	first->next = last;
	last->previous = first;
	list->length -= length % list->length;
	resetPointer(list);
}

/**
 * Removes length elements from start, inclusive.
 */
void cut(int startInclusive, int length, List * list)
{
	if (list == NULL)
	{
		dump_error("list was a NULL pointer");
		return;
	}
	if (startInclusive < 0 || startInclusive >= list->length)
	{
		dump_error("start index out of bounds");
		return;
	}
	if (length < 0 || length > list->length)
	{
		dump_error("length out of bounds");
		return;
	}
	remcut(startInclusive, length, list);
}

/**
 * Deletes all the elements of a list.
 */
void empty(List * list)
{
	while (list->length > 0)
	{
		pop(list);
	}
	resetPointer(list);
}

/**
 * Calls empty(list) and then free(list).
 */
void freeList(List * list)
{
	empty(list);
	free(list);
}

/**
 * Resets the list internal pointer to the default value (-1).
 * This is usefult before calling the iterate method in order
 * to initialize the iteration.
 */
void reset(List * list)
{
	resetPointer(list);
}

/**
 * Returns the current value pointed by the list internal pointer
 * as a void*.
 */
void* getCurrent(List * list)
{
	return list->current->value;
}

/**
 * Returns the current index pointed by the list internal pointer.
 */
int getCurrentIndex(List * list)
{
	return list->currentIndex;
}

static void dump_error(char * message)
{
	error = 1;
	strcpy(last_error, message);
	#ifdef LLIST_EXIT_ON_ERROR
		exit(1);
	#endif
}

/**
 * Returns 1 if an error occurred.
 */
int failed()
{
	return error;
}

/**
 * Returns last error message, if present, and clears error buffer.
 */
char * get_last_error()
{
	if (!error)
	{
		return "No errors occurred yet";
	}
	error = 0;
	return last_error;
}

/**
 * Prints last error message, if present, and clears error buffer.
 */
void print_last_error()
{
	puts(get_last_error());
	puts("\n");
}

/* //////////////////////////////TESTS////////////////////////////// */
#ifdef DEBUG_LINKEDLIST

static void pl(List * list)
{
	reset(list);
	while(iterate(list))
	{
		printf("[%d] = %d\n", list->currentIndex, *((int *)getCurrent(list)));
	} 
}

int main()
{
	List* l = newList();
	int a = 1, b = 2, c = 3;
	push((void *) &a, l);
	push((void *) &b, l);
	push((void *) &c, l);
	pl(l);
	printf("%d\n", *(int *)pop(l));
	printf("Len: %d\n", l->length);
	pl(l);
	printf("%d\n", *(int *)pop(l));
	printf("Len: %d\n", l->length);
	pl(l);
	printf("%d\n", *(int *)pop(l));
	printf("Len: %d\n", l->length);
	pl(l);
	enqueue((void *) &a, l);
	enqueue((void *) &b, l);
	enqueue((void *) &c, l);
	pl(l);
	printf("%d\n", *(int *)dequeue(l));
	printf("Len: %d\n", l->length);
	pl(l);
	printf("%d\n", *(int *)dequeue(l));
	printf("Len: %d\n", l->length);
	pl(l);
	printf("%d\n", *(int *)dequeue(l));
	printf("Len: %d\n", l->length);
	pl(l);
	return 0;
}
#endif
