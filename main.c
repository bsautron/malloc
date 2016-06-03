#include <malloc.h>
#include <stdio.h>

int main(void)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 97);
	str[0] = 'j';
	str[1] = 'e';
	str[2] = ' ';
	str[3] = 's';
	str[4] = 'u';
	str[5] = 'i';
	str[6] = 's';
	str[7] = 0;
	show_alloc_mem();

	printf("\n(%p = %s)\n\n", str, str);
	str = realloc(str, 10000000);
	show_alloc_mem();
	str = realloc(str, 30);
	show_alloc_mem();
	free(str);


	show_alloc_mem();
	printf("\n(%p = %s)\n\n", str, str);
	return (0);
}
