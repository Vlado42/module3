/* queue.c --- 
1;5202;0c1;5202;0c * 
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

typedef struct element // a struct for each queue node
{
	void* data;
	struct element *next;
	struct element *prev;
} Element;
	
typedef struct queue // a helper struct that stores the queue head and tail
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

	return (queue_t*)Myqueue; //give the user a queue to work with
	// note that we create a Queue object(has head and tail) but return a void
}

void qclose(queue_t *qp) // function that deallocates queue memory
{
	Element *element;
	while(((Queue*)qp)->size > 0) // we free the memory of each element
			{
				element = (Element*)qget(qp);
				free(element); 
			}
	free(qp); // we finally free the memory allocated for the queue itself
}

int32_t qput(queue_t *qp, void *elementp) // put a new element in
{
	Element *lastElement; // initialize
	lastElement = (Element*)malloc(sizeof(Element)); //allocate memory
	lastElement->data = elementp;
	// assign our object to the data field  of our Element
	if (((Queue*)qp)->size == 0) // if the queue is empty
		{
			((Queue*)qp)->head = lastElement; // have both the head and tail point to the new element
			((Queue*)qp)->tail = lastElement;
			lastElement->next = NULL; //of course it h as neither a next or a prev
			lastElement->prev = NULL;
		}
	else
		{
			((Queue*)qp)->head->prev = lastElement;
			// put the head element in second place
			lastElement->next = ((Queue*)qp)->head;
			// idit
			((Queue*)qp)->head = lastElement;
			// have the head point to our new first element
			lastElement->prev = NULL;
		}
	((Queue*)qp)->size+=1; 
	return 0;
}

void* qget(queue_t *qp)
{
	if(((Queue*)qp)->size>0)
		{
			Element *currElement = ((Queue*)qp)->head; // grab our element
			((Queue*)qp)->head = ((Queue*)qp)->head->next; // remove it
			((Queue*)qp)->size-=1;
			void* data = currElement->data; //grab the data
			free(currElement); // free the memory
			return data; //return the data
		}
}

void qapply(queue_t *qp, void(*fn)(void* elementp))
{
	Element *currElement = ((Queue*)qp)->head;
	// grab the first element	
	while (currElement->next != NULL) // cycle through n-1 elements
		{
			fn(currElement->data); // apply the function
			currElement = (Element*)(currElement->next);
		}
	fn(currElement->data); // apply the function to the last element
	// note that the while exits before applying to the last element
}


void* qsearch(queue_t *qp, bool(*searchfn)(void* elementp, const void*keyp),
						 const void* skeyp)
{
	Element *currElement = ((Queue*)qp)->head; 
	while(currElement->next != NULL)
		{
			if (searchfn(currElement->data, skeyp) == true)
			{
				return currElement->data; // if we find the data return it
 	 		}
			currElement = (Element*)(currElement->next);
		}
	if (searchfn(currElement->data, skeyp) == true)
		{
			return currElement->data;
			//note that the while doesn't handle the nth element
		}
	return NULL; // NULL if no matches are found
}


//same as search but we remove the element itself and free memory
void* qremove(queue_t *qp, bool(*searchfn)(void* elementp, const void* keyp),
							const void* skeyp)
{
	Element *currElement = ((Queue*)qp)->head;
	while(currElement->next != NULL)
		{
			if (searchfn(currElement->data, skeyp) == true)
			{
				void* data = currElement->data;
			((Element*)(currElement->prev))->next = currElement->next;
			free(currElement);
			((Queue*)qp)->size-=1;
			return data;
 	 		}
			currElement = (Element*)(currElement->next);
		}
	if (searchfn(currElement->data, skeyp) == true)
		{
			void* data = currElement->data;
			((Element*)(currElement->prev))->next = currElement->next;
			free(currElement);
			((Queue*)qp)->size-=1;
			return data; //currElement -> data  If we are accessing obj
		}
}

// queue concatenation of 2 queues
void qconcat(queue_t *q1p, queue_t *q2p)
{
	if (((Queue*)q2p)->size == 0) // if the size of the 2nd is zero
		{
			qclose(q2p); // close the 2nd and do nothing else
		}	
	if (((Queue*)q1p)->size > 0) // if they are both bigger than 0
		{
			if (((Queue*)q2p)->size > 0)
				{					
					((Element*)(((Queue*)q1p)->tail))->next = ((Queue*)q2p)->head;
					((Queue*)q1p)->tail = ((Queue*)q2p)->tail;
					// have Queue 1's tail next point to the q2p head
					// have queue 1's tail pointer poin to the new tail
					((Queue*)q1p)->size+=((Queue*)q2p)->size;
					// add their sizes
					qclose(q2p);
					//close our now empty queue
				}
		}
}
