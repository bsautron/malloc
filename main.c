#include <malloc.h>

int main(void)
{
	int		*a = NULL;

	a = malloc(234);
	malloc(10);
	malloc(10);
	show_alloc_mem();
	a = realloc(a, 100);
	show_alloc_mem();
	// free(a);
	// free(&a);

	return 0;
}
