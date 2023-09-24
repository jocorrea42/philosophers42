# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jocorrea <jocorrea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/24 14:24:49 by jocorrea          #+#    #+#              #
#    Updated: 2023/09/24 14:31:05 by jocorrea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	actions.c check.c main.c monitor.c threads.c utils.c

OBJS = $(SRCS:.c=.o)

CC = gcc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror -MMD

INCLUDE = -Iphilo.h

NAME = philo

DEPS= $(OBJS:.o=.d)

# Metodo implicito
%.o: %.c $(INCLUDE)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@


# Mis metodos
all: $(NAME)

-include $(DEPS)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $(NAME)

clean:
	@$(RM) $(OBJS) $(DEPS)

fclean: clean
	@$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
