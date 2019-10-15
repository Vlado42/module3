#include "queue.h"

#include <stdio.h>

#include <stdlib.h>





int main(void){



	queue_t *qp;

	qp = qopen();

	qclose(qp);

	exit(EXIT_SUCCESS);

}
