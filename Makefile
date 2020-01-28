CC = gcc
CFLAGS = -Wall -Wextra -Werror -c
SANITIZE = -g3 -fsanitize=address
LIBFT_FOLDER = src/libft
LIBFT = -L. $(LIBFT_FOLDER) -lft
LIBFT_A = $(LIBFT_FOLDER)/libft.a
EXEC = ft_ls
SRC = src/main.c		\
	src/init.c			\
	src/parse_func.c	\
	src/pile.c			\
	src/device.c		\
	src/sort.c			\
	src/merge_sort.c	\
	src/clean.c			\
	src/size.c			\
	src/patern.c		\
	src/run.c			\
	src/print_ls.c
OBJ = $(SRC:.c=.o)
RM = rm -f

%.o: %.c includes/ft_ls.h
	$(CC) -o $@ -c $< $(CFLAGS) -g3

.PHONY: all fclean re

all : $(EXEC)

$(LIBFT_A):
	@make -sC $(LIBFT_FOLDER)

$(EXEC): $(OBJ) $(LIBFT_A) $(LIBPILE_A)
	@echo		"\033[0;34m [OK] \033[0m       \033[0;33m Compiling:\033[0m" $<
	@$(CC) -g3 -o $(EXEC) -L./src/libft $(LIBFT_A) $(OBJ)
	@echo		"\033[0;34m [LS][SUCCESS] \033[0m"

clean :
	@$(RM) $(OBJ)
	@make -sC $(LIBFT_FOLDER) clean
	@echo		"\033[0;34m [CLEAN][SUCCESS] \033[0m"

fclean : clean
	@$(RM) $(EXEC)
	@make -sC $(LIBFT_FOLDER) fclean
	@echo		"\033[0;34m [FCLEAN][SUCCESS] \033[0m"

re : fclean all
