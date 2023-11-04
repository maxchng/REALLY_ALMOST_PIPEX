# Makefile for pipex

# Program name
NAME := pipex

# Source files
SRCS :=	pipex.c \ 
		process_cmd.c

# Object files
OBJS := $(SRCS:.c=.o)

# Compiler and flags
CC := cc
CFLAGS := -Wall -Werror -Wextra

# Paths to different directory
SYS_HEADERS_PATH := ../
LIBFT_PATH := ../libft/
OBJS_PATH := objs/

# Include path to header files
INCLUDE_SYS_HEADERS := -I$(SYS_HEADERS_PATH)
INCLUDE_LIBFT := -I$(LIBFT_PATH)includes/

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
	@$(LIBFT_MAKE) re
	@$(CC) $(CFLAGS) $(OBJS_PATH)*.o $(LDFLAGS) $(LDLIBS) -o $(NAME)

# Pattern rule to compile .c files into .o files
%.o: %.c
	@$(CC) $(INCLUDE_SYS_HEADERS) $(INCLUDE_LIBFT) -c $< -o $(OBJS_PATH)$@

# Remove all object files
clean:
	@$(LIBFT_MAKE) clean
	@$(RM) $(RMFLAGS) $(OBJS_PATH)*.o

# Remove all generated files
fclean: clean
	@$(LIBFT_MAKE) fclean
	@$(RM) $(RMFLAGS) $(NAME)

# Rebuild the program
re: fclean all

# Phony targets
.PHONY: all clean fclean re