COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

#Targets
NAME = pipex

#Compiler flags
CC = @gcc
CFLAGS = -Wall -Wextra -Werror

RM = @rm -rf

#Source files
SRC=src/main.c \
	src/utils.c \
	src/split.c
OBJ = $(SRC:.c=.o)

#Phony targets
.PHONY: all clean fclean re

all: $(NAME)
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(SRC) lib/libftprintf.a -o pipex
	@echo "$(COLOUR_GREEN)Compiled$(COLOUR_END)"

sanitize:
	$(CC) $(SRC) lib/libftprintf.a -fsanitize=address -g -o pipex
	@echo "$(COLOUR_GREEN)Make Sanitize Done$(COLOUR_END)"

clean:
	$(RM) $(OBJ)
	@echo "$(COLOUR_GREEN)$(OBJ) Removed$(COLOUR_END)"

fclean: clean
	$(RM) pipex
	@echo "$(COLOUR_GREEN)$(NAME) removed$(COLOUR_END)"

run:
	make sanita && ./$(NAME) infile "grep ola" "wc -l" outfile
make re: fclean all
