#include <malloc.h>

int main(void)
{
	char 	*a;
	char 	*b;
	char 	*c;

	a = malloc(500000);
	b = malloc(500000);
	c = malloc(500000);
	// malloc(10);
	// malloc(10);
	// show_alloc_mem();
	// a = realloc(a, 5000);
	show_alloc_mem();
	free(a);
	show_alloc_mem();
	malloc(444444);
	show_alloc_mem();
	a[0] = '3';

	return 0;
}
