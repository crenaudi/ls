CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFTFOLDER = src/libft
LIBFT = -L. $(LIBFTFOLDER) -lft
LIBFTA = $(LIBFT_FOLDER)/libft.a
EXEC = ft_ls
SRC = src/main.c		\
	src/pile.c		\
	src/device.c	\
	src/mode.c		\
	src/print_all.c	\
	src/manage.c
OBJ = $(SRC:.c=.o)
RM = rm -f

%.o: %.c include/ft_ls.h
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: all fclean re

all : $(EXEC)

$(LIBFT):
	@make -sC $(LIBFT_FOLDER)

$(EXEC): $(OBJ) $(LIBFT)
	@echo		"\033[0;32m [OK] \033[0m       \033[0;33m Compiling:\033[0m" $<
	@$(CC) -o $(EXEC) $(LIB) $(LIBFT) $(OBJ)
	@echo		"\033[0;33m [LS][SUCCESS] \033[0m"

clean :
	@$(RM) $(OBJ)
	@make -sC $(LIBFT_FOLDER) clean
	@make -sC $(LIBGFX_FOLDER) clean
	@echo		"\033[0;34m [CLEAN][SUCCESS] \033[0m"

fclean : clean
	@$(RM) $(NAME)
	@make -sC $(LIBFT_FOLDER) fclean
	@make -sC $(LIBGFX_FOLDER) fclean
	@echo		"\033[0;34m [FCLEAN][SUCCESS] \033[0m"

re : fclean all
