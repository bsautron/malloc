#include <malloc.h>

int main(void)
{
	void 	*p1;
	void 	*p2;
	void 	*p3;
	void 	*p4;

	p1 = malloc(99);
	p2 = malloc(97);
	p3 = malloc(98);
	p4 = malloc(99);
	show_alloc_mem();

	free(p2);
	printf("%s\n", "after free p2");
	show_alloc_mem();

	p2 = malloc(101);
	printf("%s\n", "Remaloc p2");
	show_alloc_mem();

	return 0;
}
