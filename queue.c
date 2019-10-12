/* queue.c --- 
 * 
 * Author: Vlado Vojdanovski
 * Created: Wed Oct  9 16:21:59 2019 (-0400)
 * Version: 
 * 
 * Description: 
 * 
 */



#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <malloc.h>
#include "queue.h"

typedef struct element
{
	void* data;
	struct Element *next;
	struct Element *prev;
} Element;
	
typedef struct queue
{
	int size;
	Element* head;
  Element* tail;
} Queue;
	
queue_t* qopen(void)
{
	Queue  *Myqueue = (Queue*) malloc(sizeof(Queue)); // Initialize our queue
	// and allocate memory
	Myqueue->size = 0; // set the queue size to 0
	Myqueue->head = NULL; // set the head and tail pointers to null
	Myqueue->tail = NULL;

	return (queue_t*)Myqueue;
}

void qclose(queue_t *qp)
{
	Element *element;
	while(((Queue*)qp)->size > 0)
			{
				element = (Element*)qget(qp);
				free(element); // free up the queue memory
			}
	free(qp);
}

int32_t qput(queue_t *qp, void *elementp)
{
	Element *lastElement = (Element*)malloc(sizeof(Element));
	lastElement->data = elementp;
	if (((Queue*)qp)->size == 0)
		{
			((Queue*)qp)->head = lastElement;
			((Queue*)qp)->tail = lastElement;
		}
	else
		{
			lastElement->next = ((void*)((Queue*)qp)->head);
			((Queue*)qp)->head->prev = (void*)lastElement;
			((Queue*)qp)->tail = lastElement;
		}
	((Queue*)qp)->size+=1;
	return 0;
}

void *qget(queue_t *qp)
{
	Element *currElement = ((Queue*)qp)->tail;
	return currElement->data;
}

void qapply(queue_t *qp, void(*fn)(void* elementp))
{
	Element *currElement = ((Queue*)qp)->head;
	while (currElement->next != NULL)
		{
			fn(currElement);
			currElement = (Element*)((Element*)currElement->next);
		}
}


void* qsearch(queue_t *qp, bool(*searchfn)(void* elementp, const void*keyp),
						 const void* skeyp)
{
	Element *currElement = ((Queue*)qp)->head;
	while(currElement->next != NULL)
		{
			if (searchfn(currElement, skeyp) == 1)
				{
					return (void*)currElement;
				}
		}
	return NULL;
}

void* qremove(queue_t *qp, bool(*searchfn)(void* elementp, const void* keyp),
							const void* skeyp)
{
	Element *currElement = ((Queue*)qp)->head;
	Element *foundElement = (Element*)(qsearch(qp, searchfn, skeyp));
	foundElement->prev  = foundElement->next;
	return (void*)currElement;
}

void qconcat(queue_t *q1p, queue_t *q2p)
{
	if (((Queue*)q1p)->size > 0)
		{
			if (((Queue*)q2p)->size >0)
				{
					((Queue*)q1p)->head = ((Queue*)q2p)->head;
					((Queue*)q1p)->tail = ((Queue*)q2p)->tail;
					((Queue*)q2p)->head = NULL;
					((Queue*)q2p)->tail = NULL;
					qclose(q2p);
				}
			qclose(q2p);
		}
}
