# =========================================
# libft/Makefile — libft + ft_printf → libft.a
# =========================================

NAME            := libft.a

# Compiler & Flags (42)
CC              := cc
CFLAGS          := -Wall -Wextra -Werror

# Libft-Header
HEADER          := libft.h

# ft_printf (eigener Ordner mit eigener Makefile)
FT_PRINTF_DIR   := ft_printf
FT_PRINTF_A     := $(FT_PRINTF_DIR)/printf.a

# Temp-Ordner zum Entpacken der printf-Objekte
TMP_DIR         := .printf_objs

# Werkzeuge
AR              := ar rcs
RM              := rm -f
RMDIR           := rm -rf
MKDIR           := mkdir -p

# -----------------------------------------
# Libft-Quellen (deine Liste unverändert)
# -----------------------------------------
SRC := \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_split.c \
	ft_strlen.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_strncmp.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strnstr.c \
	ft_strdup.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_substr.c \
	ft_memset.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_atoi.c \
	ft_itoa.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_isspace.c \
	ft_wordcount.c \
	ft_putnbr_fd.c \
	ft_lstnew_bonus.c \
	ft_lstadd_front_bonus.c \
	ft_lstadd_back_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstiter_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstmap_bonus.c \
	ft_lstsize_bonus.c

OBJ := $(SRC:.c=.o)

# -----------------------------------------
# Targets
# -----------------------------------------

all: $(NAME)

# 1) Baue libft-Objekte → libft.a
# 2) Baue ft_printf (eigene Makefile)
# 3) Extrahiere alle .o aus libftprintf.a und füge sie in libft.a ein
$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@$(MAKE) -C $(FT_PRINTF_DIR)
	@$(MKDIR) $(TMP_DIR)
	@cd $(TMP_DIR) && ar -x ../$(FT_PRINTF_A)
	@$(AR) $(NAME) $(TMP_DIR)/*.o
	@$(RMDIR) $(TMP_DIR)

# Generische Regel für .c → .o
%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@$(MAKE) -C $(FT_PRINTF_DIR) clean
	@$(RMDIR) $(TMP_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(FT_PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
