/* test1.c --- test has open and close
 * 
 * 
 * Author: Claire C. Collins
 * Created: Sun Oct 13 16:42:07 2019 (-0400)
 * Version: 
 * 
 * Description: 
 * 
 */
#include <hash.h>
#include <queue.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ppl{
	int year;
	//char name[10]; 
} ppl_t;

ppl_t *make(int year){
	ppl_t *p;
	if (!(p=(ppl_t*) malloc(sizeof(ppl_t)))) {
			printf("Problem allocating memory");
				return NULL;
		}
	p->year=year;
		return p;
}

bool findYear(void* elementp, const void* keyp){
	printf("%d", *(int *)keyp);
	printf("\n");
	printf("%d", ((ppl_t*)elementp)->year);
  printf("\n");
	fflush(stdout);
  if (((ppl_t*)elementp)->year == *(int *)keyp)
    {
      //      printf("found match at %d", ((car_t*)elementp)->year);
      return true;
    }
	else
		{
			return false;
		}
}
void mak(void* ele){
	((ppl_t*)ele)->year=80;
}

int main(void){
	hashtable_t *hash = hopen(2);
	hashtable_t *hash2 = hopen(7);
 	ppl_t *g=make(33);
	ppl_t *y=make(37);
	if(hput(hash,(void*) g, "whats", 5)!=0){
	exit(EXIT_FAILURE);
	}
	if(hput(hash, (void*) y, "whats", 5)!=0){
		exit(EXIT_FAILURE);
	}
	//ppl_t *result= (ppl_t*)
	hsearch(hash, findYear, "whats", 5);
	//printf("%d",result->year);
	//if (result->year!=33){
	//exit(EXIT_FAILURE);
	//}
	free(hremove(hash, findYear, "whats", 5));
	happly(hash, mak);
	if(y->year!=80){
		exit(EXIT_FAILURE);
	}
	
	
	hclose(hash);
	hclose(hash2);
	free(g);
	free(y);
	exit(EXIT_SUCCESS);
	return 0;
}
