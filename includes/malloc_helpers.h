#ifndef MALLOC_HELPERS_H
# define MALLOC_HELPERS_H

# include <libft.h>
# include <sys/mman.h>
# include <sys/resource.h>
#include <stdio.h>//

# define TINY_ALLOC_SIZE	992
# define TINY_ZONE_SIZE		2097152

# define SMALL_ALLOC_SIZE	127000
# define SMALL_ZONE_SIZE	16777216

# define ALIGN(X)			(((((X) - 1)) >> 2) << 2) + 4))
# define BLOCK_SIZE			(sizeof(struct s_block) - sizeof(char))
# define MALLOC_DEBUG(X)	malloc_debug(__LINE__, __FILE__, X)

enum e_zone
{
	TINY,
	SMALL,
	LARGE
};

typedef union	u_flag
{
	int		all_flags;
	char	start_heap;
	char	type_zone;
	char	free;
}				t_flag;

typedef struct	s_block
{
	struct s_block	*next;
	struct s_block	*prev;
	size_t			size;
	t_flag			flag;
	char			data[1];
}				t_block;

typedef struct	s_mmap
{
	t_block		*tiny;
	t_block		*small;
	t_block		*large;
}				t_mmap;

extern t_block	*g_base[3];

t_block			*find_block(t_block **last, size_t size);
t_block			*extend_heap(t_block *last, size_t size, int type_zone);
void			split_block(t_block *b, size_t size);

void			malloc_debug(int line, char *file, char *str);

#endif
