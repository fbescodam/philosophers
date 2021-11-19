# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fbes <fbes@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2021/11/19 18:04:03 by fbes          #+#    #+#                  #
#    Updated: 2021/11/19 18:11:06 by fbes          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =		philo

SRC =		src/main.c

HEADERS =	includes/philo.h

OBJS =		$(SRCS:.c=.o)

CFLAGS =	-Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

bonus:
	@echo I did not do the bonus

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(OBJS) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
