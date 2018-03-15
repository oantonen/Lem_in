NAME := lem-in

SRC := main.c validation.c list_functions.c room_check.c find_path.c \
list_functions2.c

LIBHEAD := libft/includes

OBJ := $(SRC:.c=.o)

CFLAGS := -Wall -Wextra -Werror -I $(HEADERS)

LIBFT := libft/libftprintf.a

all: $(NAME)

$(NAME): $(OBJ)
	@gcc -o $(NAME) $(OBJ) $(LIBFT)
	@echo "Here is lem-in :)"

%.o: %.c
	@$(CC) -c -I$(LIBHEAD) -o $@ $<

clean:
	rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)
	#@make fclean -C libft

re: fclean all