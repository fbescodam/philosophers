# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fbes <fbes@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2021/11/19 18:04:03 by fbes          #+#    #+#                  #
#    Updated: 2022/04/23 17:32:40 by fbes          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =		philo

SRCS =		src/main.c src/errors.c src/init.c src/useful.c src/list.c \
			src/philosopher.c src/forks.c src/printer.c src/sleep.c \
			src/monitor.c src/status.c

HEADERS =	includes/philo.h

INCLUDES =	-I includes

OBJS =		$(SRCS:.c=.o)

CFLAGS =	-Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

bonus:
	@echo I did not do the bonus

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(OBJS) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
