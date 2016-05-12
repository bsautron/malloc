ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE)
DEPENDENCIES = libft
SOURCES = malloc.c \
			split_block.c \
			find_block.c \
			extend_heap.c \
			malloc_debug.c \
			show_alloc_mem.c \
			main.c

SOURCES_FOLDER = sources

LIBRARIES_FOLDER = .
CC = clang
LIB_NAME = $(NAME).so
CFLAGS = -Wextra -Wall -Werror
TEST_FORDER = test
INCLUDES_FOLDER = includes
OBJECTS_FOLDER = .objects/$(NAME)
INCLUDES = malloc.h \
			malloc_helpers.h

SOURCES_DEPENDENCIES = $(foreach dep,$(DEPENDENCIES), $(LIBRARIES_FOLDER)/$(dep)/$(dep).a)
LIBRARIES = $(foreach dep, $(DEPENDENCIES), -L$(LIBRARIES_FOLDER)/$(dep)/ -$(subst lib,l,$(dep)))
INCLUDES_LIBRARIES = $(foreach dep,$(DEPENDENCIES),-I $(LIBRARIES_FOLDER)/$(dep)/includes)
HEADERS_LIBRARIES = $(foreach dep,$(DEPENDENCIES),$(LIBRARIES_FOLDER)/$(dep)/includes/$(dep).h)
MAKE_LIBRARIES = $(foreach dep,$(DEPENDENCIES),make -C $(LIBRARIES_FOLDER)/$(dep);)
REBUILD_LIBRARIES = $(foreach dep,$(DEPENDENCIES),make re -C $(LIBRARIES_FOLDER)/$(dep);)

OBJECTS = $(SOURCES:%.c=%.o)

all: init $(LIB_NAME)

test:
	@echo $(addprefix $(OBJECTS_FOLDER)/$(SOURCES_FOLDER)/, $(OBJECTS))
	@echo $(OBJECTS_FOLDER)/$(SOURCES_FOLDER)/%.o

init:
	$(MAKE_LIBRARIES)
	@mkdir -p $(OBJECTS_FOLDER)/$(SOURCES_FOLDER)

$(OBJECTS_FOLDER)/$(SOURCES_FOLDER)/%.o: $(SOURCES_FOLDER)/%.c $(addprefix $(INCLUDES_FOLDER)/, $(INCLUDES))
	$(CC) $(CFLAGS) -I $(INCLUDES_FOLDER) $(INCLUDES_LIBRARIES) -o $@ -c $<

$(MAIN_OBJECT): $(MAIN)
	$(CC) $(CFLAGS) -I $(INCLUDES_LIBRARIES) -o $(MAIN_OBJECT) -c $(MAIN)

$(LIB_NAME): $(addprefix $(OBJECTS_FOLDER)/$(SOURCES_FOLDER)/, $(OBJECTS))
	$(CC) $(CFLAGS) -I $(INCLUDES_FOLDER) $(LIBRARIES) -o $@ $(addprefix $(OBJECTS_FOLDER)/$(SOURCES_FOLDER)/, $(OBJECTS))

clean:
	rm -f $(addprefix $(OBJECTS_FOLDER)/$(SOURCES_FOLDER)/, $(OBJECTS))
	rm -f $(MAIN_OBJECT)
	rm -rf $(OBJECTS_FOLDER)

fclean: clean
	rm -f $(NAME)

re: fclean all
