CC=gcc
CFLAGS=-Wall -Wextra -Werror -pedantic -g3
INCLUDE_PATH=-I./includes

NAME=ft_traceroute

INCLUDES= \
		  ./includes/params.h \
			./includes/error_exit.h \
			./includes/parser.h \
			./includes/error_exit.h \

SRCS= \
	  ./src/main.c \
	  ./src/params.c \
		./src/parser.c \
		./src/error_exit.c

OBJS= $(SRCS:%.c=%.o)

%.o: %.c Makefile $(INCLUDES)
	$(CC) $(CFLAGS) $(INCLUDE_PATH) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lm $(INCLUDE_PATH) -o $(NAME)

all: $(NAME)

fclean:
	rm -rf $(OBJS)
	rm -rf $(NAME)

re: fclean
	$(MAKE)

run: all
	./$(NAME)

.PHONY: all clean fclean re
