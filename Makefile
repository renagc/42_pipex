COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m


NAME = pipex

CC = @gcc

CFLAGS = -Wall -Wextra -Werror
RM = @rm -rf
SOURCES = main.c utils.c split.c
OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)
$(NAME): $(OBJECTS)
	@make -C ft_printf/
	@echo "$(COLOUR_GREEN)OLA$(COLOUR_END)"
	$(CC) $(CFLAGS) $(SOURCES) ft_printf/libftprintf.a -o pipex

sanita:
	@make -C ft_printf/
	$(CC) $(SOURCES) ft_printf/libftprintf.a -fsanitize=address -g -o pipex
	@echo "$(COLOUR_GREEN)Make Sanita Done$(COLOUR_END)"

clean:
	$(RM) $(OBJECTS)

fclean: clean
	make fclean -C ft_printf/
	rm -rf pipex.a pipex

run:
	make sanita && ./$(NAME) infile "grep ola" "wc -l" outfile
make re: fclean all
