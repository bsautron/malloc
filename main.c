#include <malloc.h>

int		main(void)
{
	// printf("sizeof(BLOCK_SIZE) = %ld\n", BLOCK_SIZE);
	// printf("sizeof(struct s_block) = %ld\n", sizeof(struct s_block));
	// printf("sizeof(struct s_block *) = %lu\n", sizeof(struct s_block *));
	// printf("sizeof(size_t) = %lu\n", sizeof(size_t));
	// printf("sizeof(t_flag) = %lu\n", sizeof(t_flag));
	// printf("sizeof(char [1]) = %ld\n", sizeof(char [1]) );
	// printf("malloc return %p\n", malloc(3504));
	// printf("malloc return %p\n", malloc(34));
	// printf("malloc return %p\n", malloc(2));
	// printf("malloc return %p\n", malloc(4));

	show_alloc_mem();
	return (0);
}
