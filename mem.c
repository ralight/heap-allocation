#include <stdio.h>
#include <stdlib.h>

#define COUNT 100000
#define BLOCKSIZE 1000

int main(int argc, char *argv[])
{
	char **ptr;

	printf("This program demonstrates how it is possible for a program to\n"
			"correctly allocate and free heap memory without any leaks, but\n"
			"still appear to be leaking memory.\n\n");
	printf("No heap memory has been allocated yet. Check the process memory usage\n");
	printf("Press enter to continue.\n\n");
	getchar();

	ptr = malloc(COUNT*sizeof(char *));
	if(!ptr){
		printf("Out of memory.\n");
		return 1;
	}

	/* Allocate a load of memory. */
	for(int i=0; i<COUNT; i++){
		ptr[i] = calloc(BLOCKSIZE, 1);
		if(!ptr[i]){
			printf("Out of memory.\n");
			return 1;
		}
	}

	printf("There has now been %ld bytes of heap memory allocated.\n"
			"Check the process memory usage again.\n",
			COUNT*sizeof(char *) + COUNT*BLOCKSIZE);
	printf("Press enter to continue.\n\n");
	getchar();

	/* Free up all of those blocks apart from the last one. */
	for(int i=0; i<COUNT-1; i++){
		free(ptr[i]);
	}


	printf("All but %ld bytes of the heap memory has now been freed. Memory yet\n"
			"to be freed includes the most recently allocated memory, i.e. that\n"
			"which is the furthest into the heap allocation.\n"
			"Check the process memory usage again - it will not have\n"
			"decreased dramatically.\n",
			COUNT*sizeof(char *) + BLOCKSIZE);
	printf("Press enter to continue.\n\n");
	getchar();

	free(ptr[COUNT-1]);
	free(ptr);

	printf("There should now be no heap memory allocated.\n"
			"Check the process memory usage again. It will\n"
			"now have dropped back to the first value you saw.\n");
	printf("Press enter to continue.\n\n");
	getchar();

	return 0;
}

