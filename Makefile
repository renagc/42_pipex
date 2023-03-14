NAME = pipex.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
SOURCES = main.c errors.c

all: $(NAME)
$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)
	make -C ft_printf/
	$(CC) $(CFLAGS) $(SOURCES) ft_printf/libftprintf.a -o pipex

sanita:
	make -C ft_printf/
	$(CC) $(SOURCES) ft_printf/libftprintf.a -fsanitize=address -g -o pipex

clean:
	$(RM) $(OBJECTS)

fclean: clean
	rm -rf pipex.a pipex

make re: fclean all
