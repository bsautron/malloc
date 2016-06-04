#include <malloc.h>
#include <stdio.h>

int main(void)
{
	char *str;
	str = (char *)malloc(sizeof(char) * 9223372000000);
	// str[0] = 54;
	// str = realloc(str, 9);
	show_alloc_mem();
	return (0);
}
