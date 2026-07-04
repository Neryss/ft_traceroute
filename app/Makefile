CC=gcc
CFLAGS=-Wall -Wextra -Werror -pedantic -g3
INCLUDE_PATH=-I./includes

NAME=ft_traceroute

INCLUDES= \
		  ./includes/params.h \
			./includes/error_exit.h \
			./includes/parser.h \
			./includes/error_exit.h \
			./includes/socket.h \
			./includes/traceroute.h \
			./includes/root.h \
			./includes/dns.h \

SRCS= \
	./src/main.c \
	./src/params.c \
	./src/parser.c \
	./src/error_exit.c \
	./src/socket.c \
	./src/root.c \
	./src/dns.c \
	./src/traceroute.c \

OBJS= $(SRCS:%.c=%.o)

all: $(NAME)

%.o: %.c Makefile $(INCLUDES)
	$(CC) $(CFLAGS) $(INCLUDE_PATH) -c $< -o $@

./libft/libft.a:
	$(MAKE) -C ./libft/

$(NAME): $(OBJS) ./libft/libft.a
	cp ./libft/libft.a ./
	$(CC) $(CFLAGS) $(OBJS) -lm $(INCLUDE_PATH) -o $(NAME) -L./ -lft


fclean:
	rm -rf $(OBJS)
	rm -rf $(NAME)
	$(MAKE) -C ./libft/ fclean

re: fclean
	$(MAKE)
	$(MAKE) -C ./libft/ re

run: all
	./$(NAME)

.PHONY: all clean fclean re ./libft/libft.a
