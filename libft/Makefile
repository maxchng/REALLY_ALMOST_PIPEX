# Makefile for libft

# Static library name
NAME := libft.a

# Source files
SRCS := ft_strlen.c \
		ft_strchr.c \
		ft_strtok.c \
		ft_strdup.c \
		ft_strjoin.c \
		ft_strcmp.c \
		ft_strncmp.c \
		ft_split.c

# Object files
OBJS := $(SRCS:.c=.o)

# Compiler and flags
CC := cc
CFLAGS := -Wall -Werror -Wextra

# Paths to different directory
SYS_HEADERS_PATH := ../
OBJS_PATH := objs/

# Include path to header files
INCLUDE_SYS_HEADERS := -I$(SYS_HEADERS_PATH)

# Remove command and flags
RM := rm
RMFLAGS := -rf

# Archive command
AR := ar
ARFLAGS := -rcs

# Default target
all: $(NAME)

# Rule to build static library
$(NAME): $(OBJS)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJS_PATH)*.o

# Pattern rule to compile .c files into .o files
%.o: %.c
	@$(CC) $(INCLUDE_SYS_HEADERS) -c $< -o $(OBJS_PATH)$@

# Remove all object files
clean:
	@$(RM) $(RMFLAGS) $(OBJS_PATH)*.o

# Remove all generated files
fclean: clean
	@$(RM) $(RMFLAGS) $(NAME)

# Rebuild the static library
re: fclean all

# Phony targets
.PHONY: all clean fclean re