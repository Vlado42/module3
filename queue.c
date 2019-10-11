/* queue.c --- 
 * 
 * 
 * Author: Vlado Vojdanovski
 * Created: Wed Oct  9 16:21:59 2019 (-0400)
 * Version: 
 * 
 * Description: 
 * 
 */

typedef struct Element
{
	void* data;
	struct Element *next;
	struct Element *prev;
} element;
	
typedef void queue_t
{
	int size;
	void* head;
	void* tail;
}
	
queue_t* qopen(void)
{
	queue_t *queue = (queue_t*) malloc(sizeof(Queue)); // Initialize our queue
	// and allocate memory
	queue->size = 0; // set the queue size to 0
	queue->head = NULL; // set the head and tail pointers to null
	queue->tail = NULL;

	return queue;
}

void qclose(queue_t *qp)
{
	void *element
		while(!isEmpty(qp))
			{
				element = qget(qp);
				free(element); // free up the queue memory
			}
	free(qp);
}

int32_t qput(queue_t *qp, void *elementp)
{
	element *lastElement = (element*)malloc(sizeof(element));
	lastElement->data = elementp;
	if (qp->size == 0)
		{
			qp->head = lastElement;
			qp->tail = lastElement;
		}
	else
		{
			lastElement->next = qp->head;
			qp->head->prev = lastElement;
			qp->tail = lastElement;
		}
	qp->size+=1;
	return 0;
}

void *qget(queue_t *qp)
{
	void* element = qp->tail;
	return element;
}

void qapply(queue_t *qp, void(*fn)(void* elementp))
{
	currElement = qp->head;
	while (currElement->next != NULL)
		{
			currElement = fn(currElement);
			currElement = currElement->next;
		}
}


void* qsearch(queue *qp, bool(*searchfn)(void* elementp, const void*keyp),
						 const void* skeyp)
{
	currElement = qp->head;
	while(currElement->next != NULL)
		{
			if searchfn(currElement, skeyp)
									 {
										 return currElement;
									 }
		}
	return NULL;
}

void* qremove(queue_t *qp, bool(*searchfn)(void* elementp, const void* keyp),
							const void* skeyp)
{
	element = qsearch(qp, searchfn(elementp, keyp);
										element->prev  = element->next;
										return element;
}

void qconcat(queue_t *q1p, queue_t *q2p)
{
	if (q1p->size == 0)
		{
			if (q2p->size == 0)
				{
					return NULL;
				}
		}
	if (q1p->size > 0)
		{
			if (q2p->size >0)
				{
					q1->head = q2->head;
					q1->tail = q2->tail;
					q2->head = NULL;
					q2->tail = NULL;
					q2.close();
				}
			q2.close();
		}
}
