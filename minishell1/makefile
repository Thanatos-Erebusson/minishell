SRCS = main.c

OBJS = $(SRCS:.c=.o)

CC = gcc

LIBFT = -L libft -lft

RM = rm -rf

NAME = minishell

CFLAGS = -Wall -I ./ -I libft/

.c.o:
		$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS)
		@make -C libft/
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline
clean:
		$(RM) $(OBJS)
fclean:
		$(RM) $(OBJS) $(NAME)
re:		fclean all

.PHONY: all clean fclean re