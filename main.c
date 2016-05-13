#include <malloc.h>

int main(void)
{
	char	*str;
	int		len = 100;

	str = (char *)malloc(sizeof(char) * 2);
	for (int i = 0; i < len; i++) {
		str[i] = '*';
	}
	str[len] = 0;
	printf("%s\n", str);
	str = (char *)malloc(sizeof(char) * 2);
	str = (char *)malloc(sizeof(char) * 2);
	str = (char *)malloc(sizeof(char) * 2);
	str = (char *)malloc(sizeof(char) * 2);
	// printf("%s\n", str);

	// show_alloc_mem();
	return 0;
}
