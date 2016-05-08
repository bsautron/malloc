#ifndef MALLOC_HELPERS_H
# define MALLOC_HELPERS_H

# include <libft.h>
# include <sys/mman.h>

// # define ALIGN(X)		(((((X) - 1)) >> 2) << 2) + 4)) // try X-1 and (X)-1
# define BLOCK_SIZE		(sizeof(struct s_block) - sizeof(char))

typedef struct	s_block
{
	struct s_block	*next;
	size_t			size;
	int				free;
	// int				start_heap;
	char			data[1];
}				t_block;

typedef struct	s_mmap
{
	t_block		*tiny;
	t_block		*small;
	t_block		*large;
}				t_mmap;

extern t_block	*g_base;

t_block			*find_block(t_block **last, size_t size);
t_block			*extend_heap(t_block *last, size_t size);
void			split_block(t_block *b, size_t size);

#endif
