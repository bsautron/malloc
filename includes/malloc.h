#ifndef MALLOC_H
# define MALLOC_H

# include <libft.h>

# define SIZE_MAX_TINY		0
# define SIZE_MAX_SMALL		0

typedef struct	s_alloc_area
{
	// size_t		size_page; // getpagesize();
	size_t		size_max_tiny; // n;
	size_t		size_max_small; // m;
	size_t		size_area_tiny; // N = size_page * n * x1;
	size_t		size_area_small; // M = size_page * m * x2;
	size_t		nb_tiny; // * size_max_tiny = n * size_page;
	size_t		nb_small; // * size_max_small = m * size_page;
}				t_alloc_area;

typedef struct s_block	t_block;

struct	s_block
{
	t_block		*next;
	size_t		size;
	int			free;
};

/*
 * 1. Choose n and m size;
 * 2. Create minimun [nm] * 100;
 * 3. Keep creating until size_page * x % [nm] * 100 == 0;
 */

void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void show_alloc_mem();

#endif
