#include <malloc_helpers.h>

void malloc_debug(int line, char *file, char *str)
{
	(void)line;
	(void)file;
	(void)str;
	if (getenv("MALLOC_DEBUG"))
	{
		ft_putstr("[malloc_debug] Line ");
		ft_putnbr(line);
		ft_putstr(" on file ");
		ft_putstr(file);
		ft_putstr(": ");
		ft_putstr(str);
		ft_putchar('\n');
	}
}
