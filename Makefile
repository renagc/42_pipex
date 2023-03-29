NAME = pipex

CC = gcc

CFLAGS = -Wall -Wextra -Werror
RM = @rm -rf
SOURCES = main.c errors.c split.c utils.c
OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)
$(NAME): $(OBJECTS)
	make -C ft_printf/
	$(CC) $(CFLAGS) $(SOURCES) ft_printf/libftprintf.a -o pipex

sanita:
	make -C ft_printf/
	$(CC) $(SOURCES) ft_printf/libftprintf.a -fsanitize=address -g -o pipex

clean:
	$(RM) $(OBJECTS)

fclean: clean
	make fclean -C ft_printf/
	rm -rf pipex.a pipex

run:
	make re && valgrind ./$(NAME) infile "bla" "wc -l" outfile
make re: fclean all
