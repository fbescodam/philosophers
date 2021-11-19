# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fbes <fbes@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2021/11/19 18:04:03 by fbes          #+#    #+#                  #
#    Updated: 2021/11/19 18:07:12 by fbes          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =		philo

SRC =		src/main.c

HEADERS =	includes/philo.h

INCLUDES =	-I lib/libft

OBJS =		$(SRCS:.c=.o)

CFLAGS =	-Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS) lib/libft/libft.a
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) lib/libft/libft.a -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

lib/libft/libft.a
	make -C lib/libft

bonus:
	@echo I did not do the bonus

clean:
	rm -f $(OBJS)
	make -C lib/libft clean

fclean:
	rm -f $(OBJS) $(NAME)
	make -C lib/libft fclean

re: fclean all

.PHONY: all clean fclean re bonus
