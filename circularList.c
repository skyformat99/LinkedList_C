/*CS261 Assignment 3*/
/*Name: Sean Solberg*/
/*Date: 7/23/2017*/
/*Description: Implemenation of the circular linked list ADT*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
};

struct CircularList
{
	int size;
	struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
	list->sentinel = malloc(sizeof(struct Link));
	assert(list->sentinel != 0);
	list->size = 0;
	list->sentinel->next = list->sentinel;
	list->sentinel->prev = list->sentinel;
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
	struct Link *newLink = malloc(sizeof(struct Link));
	newLink->next = 0;
	newLink->prev = 0;
	newLink->value = value;
	return newLink;
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
	assert(list != 0);
	struct Link *newLink = createLink(value);
	
	link->next->prev = newLink;
	newLink->next = link->next;
	link->next = newLink;
	newLink->prev = link;
	
	list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
	assert(list != 0);

	link->prev->next = link->next;
	link->next->prev = link->prev;

	free(link);
	list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
	struct CircularList* list = malloc(sizeof(struct CircularList));
	init(list);
	return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
	while (!circularListIsEmpty(list))
	{
		circularListRemoveFront(list);
	}
	free(list->sentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
	assert(list != 0);
	
	/*Pass first node to add link after function*/
	addLinkAfter(list, list->sentinel, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
	assert(list != 0);
	/*allocate new link and intialize*/
	struct Link *newLink = createLink(value);

	/*make connetions*/
	newLink->next = list->sentinel;
	newLink->prev = list->sentinel->prev;
	list->sentinel->prev->next = newLink;
	list->sentinel->prev = newLink;

	list->size++;
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
	assert(list != 0);
	if (list->sentinel->next != list->sentinel->prev)
	{
		return list->sentinel->next->value;
	}
	else return 0;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
	assert(list!=0);
	return list->sentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
	assert(list != 0);
	struct Link *tempLink;
	tempLink = list->sentinel->next;

	/*call removelink function with front link*/
	removeLink(list, tempLink);
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
	assert(list != 0);
	struct Link *tempLink;
	tempLink = list->sentinel->prev;

	/*call remove link function with back link*/
	removeLink(list, tempLink);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
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
void circularListPrint(struct CircularList* list)
{
	assert(list != 0);
	struct Link *temp;
	int i;

	/*step through list and print each value*/
	temp = list->sentinel->next;
	if (list->size > 0)
	{
		for (i = 0; i < list->size; i++)
		{
			printf("%f \n", temp->value);
			temp = temp->next;
		}
	}
	else printf("Empty list \n");
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
	assert(list != 0);
	struct Link *temp;
	struct Link *swap;
	temp = list->sentinel;
	int i;

	/*if list contain links, then use typical swap algorithm to reverse link next and prev pointers*/
	if (list->size > 0)
	{
		for (i = 0; i <= list->size; i++)
		{
			swap = temp->prev;
			temp->prev = temp->next;
			temp->next = swap;

			temp = temp->prev;
		}
	}
}
