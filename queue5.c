/* queue5.c --- 
 * 
 * 
 * Author: Vlado Vojdanovski
 * Created: Mon Oct 14 17:26:14 2019 (-0400)
 * Version: 
 * 
 * Description: 
 * 
 */

#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
int main(void){
	//create and fill two queues 
	queue_t *qt;
	qt = qopen();
	queue_t *qt2;
	qt2 = qopen();

	int x = 1;
	int y = 2;
	int a = 3;
	int b = 4;
	
	//	qput(qt,(void*)&x);
	//	qput(qt, (void*)&y);
	qput(qt2, (void*)&a);
	qput(qt2, (void*)&b);


	// For both nonempty
	
	// call qconcat
	qconcat(qt, qt2);
	// Now grab the elements from qt and make sure they come out in the expected order
	if ((*((int*)qget(qt)) != 3) || (*((int*)qget(qt)) !=4)){
	  printf("failure: concat did no attach the queues in the right order");
	}

	qclose(qt);
	printf("testCat succeeded!\n");
	exit(EXIT_SUCCESS);
}
