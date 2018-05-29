NAME := lem-in

SRC := main.c validation.c list_functions.c room_check.c find_path.c \
list_functions2.c processing_ants.c free_ants.c other.c

LIBHEAD := libft/includes

OBJ := $(SRC:.c=.o)

CFLAGS := -Wall -Wextra -Werror -I $(HEADERS)

LIBFT := libft/libftprintf.a

all: create_lib $(NAME)

create_lib: 
	@make -C libft

$(NAME): $(OBJ)
	@gcc -o $(NAME) $(OBJ) $(LIBFT)
	@echo "\033[1;32mHere is lem-in :P"

%.o: %.c
	@$(CC) -c -I$(LIBHEAD) -o $@ $<

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C libft

re: fclean all