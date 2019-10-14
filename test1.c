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

int main(void){
	hashtable_t *hash = hopen(2);
	hclose(hash);
	printf("work");
	return 0;
}
