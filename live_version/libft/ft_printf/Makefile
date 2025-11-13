NAME := printf.a
HEADER := ft_printf.h

CC := cc
CFLAGS := -Wall -Wextra -Werror

SRC := \
	1ft_printf.c \
	2ft_va_start.c \
	3find_arg.c \
	4print_base.c \
	5print_str.c


OBJ := $(SRC:.c=.o)
RM := rm -f

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

all: $(NAME)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

