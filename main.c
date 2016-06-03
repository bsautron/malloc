#include <malloc.h>
#include <stdio.h>

int main(void)
{
	malloc(100000000);
	malloc(1000);
	malloc(1000);
	malloc(1000);
	malloc(100000000);
	malloc(1000);
	malloc(1000);
	malloc(1000);
	malloc(10);
	malloc(10);
	malloc(10);
	malloc(10);
	malloc(100000000);
	malloc(100000000);
	malloc(100000000);
	malloc(1000);
	malloc(1000);
	malloc(1000);

	show_alloc_mem();
	return (0);
}
