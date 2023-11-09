# Makefile for pipex

# Program name
NAME := pipex

# Source files
SRCS :=	pipex.c \
		process_cmd.c \
		setup_functions.c \
		tokenize_cmd.c \
		execute_cmd_1.c \
		execute_cmd_2.c

BONUS_SRCS := pipex_bonus.c \
			  process_cmd_bonus.c \
			  setup_functions_bonus.c \
			  tokenize_cmd_bonus.c \
			  execute_cmd_bonus_1.c \
			  execute_cmd_bonus_2.c

GNL_SRCS :=	get_next_line.c \
			get_next_line_utils.c

# Paths to different directory
SYS_HEADERS_PATH := ../
LIBFT_PATH := ../libft/
OBJS_PATH := ./objs/
BONUS_PATH := ./bonus/
GNL_PATH := ../gnl/
GNL_OBJS_PATH := ../gnl/objs/

# Object files
OBJS := $(addprefix $(OBJS_PATH), $(SRCS:.c=.o))
BONUS_OBJS := $(addprefix $(OBJS_PATH), $(BONUS_SRCS:.c=.o))
GNL_OBJS := $(addprefix $(GNL_OBJS_PATH), $(GNL_SRCS:.c=.o))

# Compiler and flags
CC := cc
CFLAGS := -Wall -Werror -Wextra

# Include path to header files
INCLUDE_SYS_HEADERS := -I$(SYS_HEADERS_PATH)
INCLUDE_LIBFT := -I$(LIBFT_PATH)includes/
INCLUDE_GNL := -I$(GNL_PATH)includes/

# Locate and link static library
LDFLAGS := -L$(LIBFT_PATH)
LDLIBS := -lft

# Run make tool in different directory
LIBFT_MAKE := $(MAKE) -C$(LIBFT_PATH)

# Remove command and flags
RM := rm
RMFLAGS := -rf

# Default target
all: $(NAME)

# Rule to build program
$(NAME): $(OBJS)
	@$(RM) $(RMFLAGS) $(BONUS_OBJS) $(GNL_OBJS)
	@$(LIBFT_MAKE) re
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

bonus: $(BONUS_OBJS) $(GNL_OBJS)
	@$(RM) $(RMFLAGS) $(OBJS)
	@$(LIBFT_MAKE) re
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(GNL_OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

# Pattern rule to compile .c files into .o files
$(OBJS_PATH)%.o: %.c
	@$(CC) $(INCLUDE_SYS_HEADERS) $(INCLUDE_LIBFT) -c $< -o $@

$(OBJS_PATH)%.o: $(BONUS_PATH)%.c
	@$(CC) $(INCLUDE_SYS_HEADERS) $(INCLUDE_LIBFT) $(INCLUDE_GNL) -c $< -o $@

$(GNL_OBJS_PATH)%.o: $(GNL_PATH)%.c
	@$(CC) $(INCLUDE_SYS_HEADERS) $(INCLUDE_GNL) -c $< -o $@

# Remove object files
clean:
	@$(LIBFT_MAKE) clean
	@$(RM) $(RMFLAGS) $(OBJS) $(BONUS_OBJS) $(GNL_OBJS)

# Remove generated files
fclean: clean
	@$(LIBFT_MAKE) fclean
	@$(RM) $(RMFLAGS) $(NAME)

# Rebuild the program
re: fclean all

# Phony targets
.PHONY: all bonus clean fclean re