/*CS261 Assignment 3*/
/*Name: Sean Solberg*/
/*Date: 7/23/2017*/
/*Descritpion: Implementation of the linked list deque ADT*/

#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list) {
	/*allocate and check front and back sentinels*/
	list->frontSentinel = malloc(sizeof(struct Link));
	assert(list->frontSentinel != 0);
	list->backSentinel = malloc(sizeof(struct Link));
	assert(list->backSentinel != 0);
	
	/*set pointers for sentinels*/
	list->size = 0;
	list->frontSentinel->next = list->backSentinel;
	list->backSentinel->prev = list->frontSentinel;
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	assert(list != 0);
	/*create new link*/
	struct Link *newLink = malloc(sizeof(struct Link));

	/*update pointers to links*/
	link->prev->next = newLink;
	newLink->prev = link->prev;
	newLink->next = link;
	link->prev = newLink;

	/*set value and increment list size*/
	newLink->value = value;
	list->size++;

}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
	// FIXME: you must write this
	assert(list != 0);
	
	/*for link to be removed, updates its previous link next point to its next*/
	link->prev->next = link->next;
	/*also update next's prev pointer to link's previous*/
	link->next->prev = link->prev;

	/*free memory*/
	free(link);

	/*decrement size*/
	list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{

	addLinkBefore(list, list->frontSentinel->next, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	struct Link *newLink = malloc(sizeof(struct Link));
	newLink->next = list->backSentinel;
	newLink->prev = list->backSentinel->prev;
	list->backSentinel->prev->next = newLink;
	list->backSentinel->prev = newLink;
	
	newLink->value = value;
	list->size++;
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
	assert(list != 0);
	if (!linkedListIsEmpty(list)) {
		return list->frontSentinel->next->value;
	}
	else return 0;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
	assert(list != 0);
	if (!linkedListIsEmpty(list)) {
		return list->backSentinel->prev->value;
	}
	else return 0;
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
	assert(list != 0);
	/*Must contain at least one node*/
	if (list->size > 0)
	{
	struct Link *tempLink; 
	tempLink = list->frontSentinel->next;

	/*set new pointers*/
	list->frontSentinel->next = tempLink->next;
	tempLink->next->prev = list->frontSentinel;

	list->size--;

	/*Deallocate first link*/
	free(tempLink);
	}

	/*else no action*/
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
	assert(list != 0);
	
	/*Must contain at least one node*/
	if (list->size > 0)
	{
		/*Temp pointer to link to remove*/
		struct Link *tempLink;
		tempLink = list->backSentinel->prev;

		/*set new pointers*/
		list->backSentinel->prev = tempLink->prev;
		tempLink->prev->next = list->backSentinel;

		list->size--;

		/*Deallocate first link*/
		free(tempLink);
	}
	/*else no action*/
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
	assert(list != 0);
	if (list->size == 0) 
	{
		return 1;
	}
	else return 0;
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
	assert(list != 0);
	/*create temp pointer to iterate through list*/
	struct Link *tempLink;

	if (!linkedListIsEmpty(list))
	{
		tempLink = list->frontSentinel->next;

		int i;
		for (i = 0; i < list->size; i++)
		{
			printf("%d \n", tempLink->value);
			tempLink = tempLink->next;
		}
	}
	else printf("Empty list \n");
}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	assert(list != 0);

	linkedListAddFront(list, value);

}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
	/*create temp pointer to iterate through list*/
	struct Link *tempLink;
	tempLink = list->frontSentinel->next;
	int i;

	for (i = 0; i < list->size; i++)
	{
		if (tempLink->value == value) 
		{
			/*match found, return 1*/
			return 1;
		}
		tempLink = tempLink->next;
	}

	/*no match found*/
	return 0;
	
}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	assert(list != 0);
	/*create temp pointer to iterate through list*/
	struct Link *tempLink;
	tempLink = list->frontSentinel->next;
	int i;

	for (i = 0; i < list->size; i++)
	{
		if (tempLink->value == value)
		{
			/*match found, remove link*/
			removeLink(list, tempLink);
			return;
		}
		tempLink = tempLink->next;
	}
	/*no match found*/

}
