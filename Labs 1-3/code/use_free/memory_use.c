#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define SLEEP_SEC    60

int main(){
	int *ptr;
	unsigned long i,n;
	printf("Enter number of int(4 byte) you want to allocate:");
	scanf("%lu",&n);
 
	printf("Step 1:   Allocating %lu bytes......\n",n*sizeof(int));
	ptr=(int*)malloc(n*sizeof(int));
	if (ptr==NULL){
		printf("ERROR!Memory not allocated!");
		exit(0);
	}
        printf(" Enter CHAR to continue .....\n");
        getchar();   getchar();
 
	printf("Step 2: Filling int into memory.....\n");
	for (i = 0; i < n; i++){
		ptr[i] = 1;
	}

/*
	printf("Sleep %d seconds......\n", SLEEP_SEC);
	sleep(SLEEP_SEC);
*/
        printf("Enter CHAR to continue .....\n");
        getchar();
 
	printf("Step 3: Free memory.\n");
	free(ptr);
	return 0;
}

