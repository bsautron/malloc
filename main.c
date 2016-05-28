#include <malloc.h>

int main(void)
{
	// char 	*a;
	// char 	*b;
	// char 	*c;
  size_t  size = 10 * 4096;

	for (int i = 0; i < 1000; i++) {
    free(malloc(size));
	}

	// b = malloc(500000);
	// c = malloc(500000);
	// malloc(10);
	// malloc(10);
	// show_alloc_mem();
	// a = realloc(a, 5000);
	// show_alloc_mem();
	// free(a);
	// show_alloc_mem();
	// malloc(444444);
	// show_alloc_mem();
	// a[0] = '3';

	return (0);
}
