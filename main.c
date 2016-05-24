#include <malloc.h>

int main(void)
{
	int		*a;

	a = (int*)malloc(sizeof(int) * 1);
	a[0] = 935;
	printf("%d\n", a[0]);
	show_alloc_mem();
	free(a);
	show_alloc_mem();
	// free(&a);

	return 0;
}
