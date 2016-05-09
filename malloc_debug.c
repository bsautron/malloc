#include <malloc_helpers.h>

void malloc_debug(int line, char *file, char *str)
{
	char	*malloc_debug_var_env;

	malloc_debug_var_env = getenv("MALLOC_DEBUG");
	if (malloc_debug_var_env && !ft_strcmp(malloc_debug_var_env, "true"))
	{
		ft_putstr("Line ");
		ft_putnbr(line);
		ft_putstr(" on file ");
		ft_putstr(file);
		ft_putstr(": ");
		ft_putstr(str);
		ft_putchar('\n');
	}
}
