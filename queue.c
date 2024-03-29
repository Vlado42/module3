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

typedef struct element // a struct for each queue node with data, next and prev
{
	void* data;
	struct element *next;
	struct element *prev;
} Element;
	
typedef struct queue // a helper struct that stores the queue head and tail
{
  int size; // the size is not used in our implementation but may be useful for other developers
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
	Element* currElement = ((Queue*)qp)->head;
	
	// we separately check the first element and then loop over all other elements
	if (currElement!=NULL)
		{
			Element* nextElement = currElement->next;
			free(currElement);
			while(nextElement != NULL) // we free the memory of each element
				{
					currElement = nextElement;
					nextElement = currElement->next;
					free(currElement);
				}
		}
	free(qp); // we finally free the memory allocated for the queue itself
}

int32_t qput(queue_t *qp, void *elementp) // put a new element in
{
	Element *lastElement; // initialize the element
	if(!(lastElement = (Element*)malloc(sizeof(Element))))
		{
			return 1; //return 1 if memory allocation fails
		}
		
	lastElement->data = elementp;
	// assign our object to the data field  of our Element
	if (((Queue*)qp)->size == 0) // if the queue is empty
		{
			((Queue*)qp)->head = lastElement; // have both the head and tail point to the new element
			((Queue*)qp)->tail = lastElement;
			lastElement->next = NULL; //the first element has neither a next or a prev
			lastElement->prev = NULL;
		}
	else // if the queue is not empty
		{
			((Queue*)qp)->tail->next = lastElement; 
			lastElement->prev = ((Queue*)qp)->tail;
			
			// put the head element in second place
		 	((Queue*)qp)->tail = lastElement;
			lastElement->next = NULL; // our new element has a null next pointer
		}
	((Queue*)qp)->size+=1; 
	return 0;
}

void* qget(queue_t *qp)
{
	Element* currElement = ((Queue*)qp)->head; // grab our element
	if(currElement != NULL)
		{
			((Queue*)qp)->head = ((Queue*)qp)->head->next; // remove it
			((Queue*)qp)->size-=1;
			void* data = currElement->data; //grab the data
			free(currElement); // free the memory
			return data; //return the data
		}
	return NULL;
}

void qapply(queue_t *qp, void(*fn)(void* elementp))
{
	Element *currElement = ((Queue*)qp)->head;
	// grab the first element
	if(currElement != NULL)
		{
			while (currElement->next != NULL) // cycle through n-1 elements
				{
					fn(currElement->data); // apply the function
					currElement = (Element*)(currElement->next);
				}
			// note that the while exits before applying to the last element
			fn(currElement->data); // apply the function to the last element			
		}
}


void* qsearch(queue_t *qp, bool(*searchfn)(void* elementp, const void*keyp),
						 const void* skeyp)
{
	Element *currElement = ((Queue*)qp)->head; 
	if (currElement != NULL)
		{
			while(currElement->next != NULL)
				{
					if (searchfn(currElement->data, skeyp) == true)
						{
							return currElement->data; // if we find the data return it
						}
					currElement = (Element*)(currElement->next);
				}
		        //note that the while doesn't handle the nth element
			if (searchfn(currElement->data, skeyp) == true)
				{
					return currElement->data;	
				}
		}
	return NULL; // NULL if no matches are found
}


//same as search but we remove the element itself and free memory
void* qremove(queue_t *qp, bool(*searchfn)(void* elementp, const void* keyp),const void* skeyp)
{
  Element *currElement = ((Queue*)qp)->head;
  if (currElement != NULL)
		{
			if (searchfn(currElement->data, skeyp) == true)
				{
					((Queue*)qp)->head = ((Queue*)qp)->head->next;
					void* data = currElement->data;
					free(currElement);
					((Queue*)qp)->size-=1;
					return data;
				}
			if(currElement->next!=NULL){
				currElement = (Element*)(currElement->next);
					while(currElement->next != NULL)
						{
							if (searchfn(currElement->data, skeyp) == true)
								{
									void* data = currElement->data;
									currElement->prev->next = currElement->next;
									free(currElement);
									((Queue*)qp)->size-=1;
									return data;
								}
							currElement = (Element*)(currElement->next);
						}
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
	return NULL;
}

// queue concatenation of 2 queues
void qconcat(queue_t *q1p, queue_t *q2p)
{
	if (((Queue*)q2p)->size == 0) // if the size of the 2nd is zero
		{	
			qclose(q2p); // close the 2nd and do nothing else
		}	
	if (((Queue*)q2p)->size > 0)
				{
					if (((Queue*)q1p)->size > 0) // if they are both bigger than 0
						{
							// have Queue 1's tail next point to the q2p head
							// have queue 1's tail pointer poin to the new tail
							((((Queue*)q1p)->tail)->next) = ((Queue*)q2p)->head;
							(((Queue*)q1p)->tail) = ((Queue*)q2p)->tail;
							((Queue*)q1p)->size+=((Queue*)q2p)->size;
							
							((Queue*)q2p)->size = 0;
							((Queue*)q2p)->head=NULL;
							((Queue*)q2p)->tail=NULL;
							// add their sizes
							qclose(q2p);
							//close our now empty queue
						}
					if (((Queue*)q1p)->size == 0)
						{
							Element *newHead = ((Queue*)q2p)->head;
							Element *newTail = ((Queue*)q2p)->tail;
						  ((Queue*)q1p)->size+=((Queue*)q2p)->size;

							((Queue*)q1p)->head = newHead;
							((Queue*)q1p)->tail = newTail;
							
							((Queue*)q2p)->size = 0;
							((Queue*)q2p)->head=NULL;
							((Queue*)q2p)->tail=NULL;
							// add their sizes
							qclose(q2p);
						}
				}
}
