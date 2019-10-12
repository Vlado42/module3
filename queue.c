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
#include <stdbool.h>
#include "queue.h"

typedef struct element
{
	void* data;
	struct element *next;
	struct element *prev;
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
			lastElement->next = NULL;
			lastElement->prev = NULL;
		}
	else
		{
			((Queue*)qp)->head->prev = lastElement;
			lastElement->next = ((Queue*)qp)->head;
			((Queue*)qp)->head = lastElement;
		}
	((Queue*)qp)->size+=1;
	return 0;
}

void* qget(queue_t *qp)
{
	if(((Queue*)qp)->size>0)
		{
			Element *currElement = ((Queue*)qp)->head;
			((Queue*)qp)->head = ((Queue*)qp)->head->next;
			((Queue*)qp)->size-=1;
	
			return currElement->data;
		}
}

void qapply(queue_t *qp, void(*fn)(void* elementp))
{
	Element *currElement = ((Queue*)qp)->head;
		
	while (currElement->next != NULL)
		{
			fn(currElement->data);
			currElement = (Element*)(currElement->next);
		}
	fn(currElement->data);
}


void* qsearch(queue_t *qp, bool(*searchfn)(void* elementp, const void*keyp),
						 const void* skeyp)
{
	Element *currElement = ((Queue*)qp)->head;
	while(currElement->next != NULL)
		{
			if (searchfn(currElement, skeyp) == true)
				{
					return (void*)currElement;
				}
			currElement = (Element*)(currElement->next);
		}
	if (searchfn(currElement, skeyp) == true)
		{
					return (void*)currElement;
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
