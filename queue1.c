/* queue1.c --- 
 * 
 * 
 * Author: Vlado Vojdanovski
 * Created: Sat Oct 12 15:51:47 2019 (-0400)
 * Version: 
 * 
 * Description: 
 * 
 */


#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>                                                           
#include <malloc.h>                                                            
#include "queue.h"                                                             


typedef struct car {
	char plate[10];
	double price;
	int year;
}	car_t;


car_t *make_car( char *plate, double price, int year){
	car_t *cp;
	if(!(cp = (car_t*)malloc(sizeof(car_t)))) {
		printf("[Error: malloc failed allocating car]\n");
		return NULL;
	}
	strcpy(cp->plate,plate);
	cp->price=price;
	cp->year=year;
	return cp;
}


int main(void)
{
	char plate[10];
	strcpy(plate,"123");
	car_t *c=make_car(plate, 19.0, 77);
	
	queue_t *queue1 = qopen();
	int32_t z = qput(queue1, (void*)c);

	car_t *c2 = (car_t*)qget(queue1);
	printf("%d", c2->year);

	//	qclose(queue1);
	exit(EXIT_SUCCESS);
}
