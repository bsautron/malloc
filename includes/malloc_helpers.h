#ifndef MALLOC_HELPERS_H
# define MALLOC_HELPERS_H

# include <libft.h>
# include <sys/mman.h>
# include <sys/resource.h>
#include <stdio.h>//
// use getlimit, getpagesize

# define TINY_ALLOC_SIZE	992
# define TINY_ZONE_SIZE		(512 * getpagesize())

# define SMALL_ALLOC_SIZE	127000
# define SMALL_ZONE_SIZE	(4096 * getpagesize())

# define FLAG_FREE			001000
# define FLAG_START_HEAP	010000
# define IS_FREE(B)			(((B)->flag & FLAG_FREE) != 0)
# define IS_START_HEAP(B)	(((B)->flag & FLAG_START_HEAP) != 0)

# define ALIGN4(X)			(((((((X) - 1)) >> 2) << 2) + 4))
# define ALIGNPAGE(X, P)	(((X - 1) / P) * P + P)
# define BLOCK_SIZE			(3 * sizeof(void *) + sizeof(size_t) + 2 * sizeof(int))
# define MALLOC_DEBUG(X)	malloc_debug(__LINE__, __FILE__, X)

typedef struct s_block		t_block;

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
	t_block	*next;
	t_block	*prev;
	size_t	size;
	void	*ptr;
	int		rest;
	int		flag;
	char	data[1];
}				t_block;

typedef struct	s_mmap
{
	t_block		*tiny;
	t_block		*small;
	t_block		*large;
}				t_mmap;

extern t_block	*g_base[3];

t_block			*find_block(t_block **last, size_t size, int type_zone);
t_block			*extend_heap(t_block **last, size_t size, int type_zone);
void			split_block(t_block *b, size_t size);
t_block			*fusion(t_block *b);
int				valid_addr(void *p);

void			malloc_debug(int line, char *file, char *str);

#endif
