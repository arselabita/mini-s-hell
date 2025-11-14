# =========================
# Name
# =========================
NAME    	:= minishell
DEBUG_NAME	:= minishell_debug

# =========================
# Compiler & Flags (42-compliant)
# =========================
CC      	:= cc
CFLAGS  	:= -Wall -Wextra -Werror -MMD -MP
LDFLAGS 	:= -lreadline
DEBUG_FLAGS := -g -DVERBOSE=1

##VALGRIND := 
#valgrind --leak-check=full --show-leak-kinds=all --suppressions=../readline.supp

# =========================
# Libft
# =========================
LIBFT_DIR       := libft/
LIBFT_A         := $(LIBFT_DIR)libft.a


# =========================
# Sources
# =========================
# Separate main sources
MAIN_SOURCE_MAND  := main.c
MAIN_SOURCE_BONUS := main_bonus.c

# Mandatory sources
SOURCES_CORE    := \
	init_env.c \
	cleanup.c \
	verbose.c \
	utils.c \

# Bonus-only sources
SOURCES_BONUSONLY := \
	main_bonus.c

##BONUS FILES

# =========================
# Fixed object paths
# =========================
OBJ_DIR_MAND        := objects/
OBJ_DIR_BONUS       := objects_bonus/

# Build corresponding object paths from separate main sources
MAIN_OBJECT_MAND    := $(addprefix $(OBJ_DIR_MAND),$(MAIN_SOURCE_MAND:.c=.o))
MAIN_OBJECT_BONUS   := $(addprefix $(OBJ_DIR_BONUS),$(MAIN_SOURCE_BONUS:.c=.o))

OBJECTS_MAND_ALL    := $(addprefix $(OBJ_DIR_MAND),$(SOURCES_CORE:.c=.o))
OBJECTS_MAND_NOFORK := $(filter-out $(OBJ_DIR_MAND)pipe_and_fork.o,$(OBJECTS_MAND_ALL))
OBJECT_BONUS_ONLY   := $(addprefix $(OBJ_DIR_BONUS),$(SOURCES_BONUSONLY:.c=.o))

HEADERS             := minishell.h

# =========================
# Build mode (mandatory / bonus)
# =========================
MODE ?= mandatory

ifeq ($(MODE),bonus)
# Bonus mode: main_bonus.c in objects_bonus/ + mandatory (without pipe_and_fork.o) + bonus-only objects
MAIN_OBJECT := $(MAIN_OBJECT_BONUS)
OBJECTS     := $(OBJECTS_MAND_NOFORK) $(OBJECT_BONUS_ONLY)
else
# Mandatory mode: main.c in objects/ + all mandatory objects
MAIN_OBJECT := $(MAIN_OBJECT_MAND)
OBJECTS     := $(OBJECTS_MAND_ALL)
endif

DEPS := $(MAIN_OBJECT:.o=.d) $(OBJECTS:.o=.d)

# =========================
# Default target
# =========================
all: $(LIBFT_A) $(NAME)

debug: fclean
	$(MAKE) CFLAGS="$(CFLAGS) $(DEBUG_FLAGS)" $(DEBUG_NAME)

# =========================
# Libft build rule
# =========================
$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR) all

$(DEBUG_NAME): $(MAIN_OBJECT) $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LIBFT_A)

# =========================
# Link: program (no unnecessary relinking)
# =========================
$(NAME): $(MAIN_OBJECT) $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LIBFT_A)


# =========================
# Compile rules
# =========================
# Mandatory objects in objects/
$(OBJ_DIR_MAND)%.o: %.c $(HEADERS) | $(OBJ_DIR_MAND)
	$(CC) $(CFLAGS) -c $< -o $@

# Bonus objects in objects_bonus/
$(OBJ_DIR_BONUS)%.o: %.c $(HEADERS) | $(OBJ_DIR_BONUS)
	$(CC) $(CFLAGS) -c $< -o $@

# =========================
# Create object directories
# =========================
$(OBJ_DIR_MAND):
	mkdir -p $(OBJ_DIR_MAND)

$(OBJ_DIR_BONUS):
	mkdir -p $(OBJ_DIR_BONUS)

# =========================
# Bonus target (delegates to Make so it checks up-to-date status)
# =========================
bonus:
	$(MAKE) MODE=bonus all

# =========================
# Clean targets
# =========================
clean:
	rm -rf $(OBJ_DIR_MAND) $(OBJ_DIR_BONUS)

fclean: clean
	rm -f $(NAME) $(DEBUG_NAME)

re: fclean all

# Include automatically generated dependency files
-include $(DEPS)

# =========================
# Phony
# =========================
.PHONY: all clean fclean re bonus debug
# .SILENT:
