#include <malloc.h>

int main(void)
{
	int		*a = NULL;

	a = malloc(500000);
	a = malloc(500000);
	a = malloc(500000);
	// malloc(10);
	// malloc(10);
	// show_alloc_mem();
	// a = realloc(a, 5000);
	show_alloc_mem();
	free(a);
	show_alloc_mem();
	// free(&a);

	return 0;
}
