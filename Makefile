NAME = malloc
DEPENDENCIES = libft
SOURCES = malloc.c \
			split_block.c \
			find_block.c \

SOURCES_FOLDER = .

CC = gcc
CFLAGS = -Wextra -Wall -Werror
TEST_FORDER = test
INCLUDES_FOLDER = includes
OBJECTS_FOLDER = .objects
MAIN = main.c
MAIN_OBJECT = $(OBJECTS_FOLDER)/$(MAIN:.c=.o)
INCLUDES = $(NAME).h \
			malloc_helpers.h

SOURCES_DEPENDENCIES = $(foreach dep, $(DEPENDENCIES), libraries/$(dep)/$(dep).a)
INCLUDES_LIBRARIES = $(foreach dep,$(DEPENDENCIES),-I libraries/$(dep)/includes)
HEADERS_LIBRARIES = $(foreach dep,$(DEPENDENCIES),libraries/$(dep)/includes/$(dep).h)
MAKE_LIBRARIES = $(foreach dep,$(DEPENDENCIES),make -C libraries/$(dep);)
REBUILD_LIBRARIES = $(foreach dep,$(DEPENDENCIES),make re -C libraries/$(dep);)

OBJECTS = $(SOURCES:%.c=%.o)

all: init makelib $(NAME)

rebuild: fclean init rebuildlib $(NAME)

makelib:
	$(MAKE_LIBRARIES)

rebuildlib:
	$(REBUILD_LIBRARIES)

init:
	mkdir -p $(OBJECTS_FOLDER)/$(SOURCES_FOLDER)

$(NAME): $(MAIN_OBJECT) $(addprefix $(OBJECTS_FOLDER)/$(SOURCES_FOLDER)/, $(OBJECTS))
	$(CC) $(CFLAGS) -o $@ $(MAIN_OBJECT) $(addprefix $(OBJECTS_FOLDER)/$(SOURCES_FOLDER)/, $(OBJECTS)) $(SOURCES_DEPENDENCIES)

$(MAIN_OBJECT): $(MAIN)
	$(CC) $(CFLAGS) -I $(INCLUDES_FOLDER) -o $(MAIN_OBJECT) -c $(MAIN) $(INCLUDES_LIBRARIES)

$(addprefix $(OBJECTS_FOLDER)/$(SOURCES_FOLDER)/, %.o): $(SOURCES_FOLDER)/%.c $(addprefix $(INCLUDES_FOLDER)/, $(INCLUDES)) $(HEADERS_LIBRARIES)
	$(CC) $(CFLAGS) -I $(INCLUDES_FOLDER) -o $@ -c $< $(INCLUDES_LIBRARIES)

clean:
	rm -f $(addprefix $(OBJECTS_FOLDER)/$(SOURCES_FOLDER)/, $(OBJECTS))
	rm -f $(MAIN_OBJECT)
	rm -rf $(OBJECTS_FOLDER)

fclean: clean
	rm -f $(NAME)

re: fclean all
