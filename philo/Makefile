# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jecarval <jecarval@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/03 14:35:26 by jecarval          #+#    #+#              #
#    Updated: 2023/11/29 17:45:07 by jecarval         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Werror -Wextra -pthread -g

NAME = philo

SRCS =	main.c cleanup.c grim_reaper.c init.c midwife.c philosopher.c eating.c


OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

vg: override CFLAGS := -Wall -Werror -Wextra -pthread  -g -fsanitize=thread
vg: $(NAME)

# .SILENT:
