# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/01 12:45:22 by vviterbo          #+#    #+#              #
#    Updated: 2025/01/07 18:10:48 by vviterbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = pipex.c sender_process.c receiver_process.c utils.c

OBJS = $(patsubst %.c, %.o, $(SRCS))

CFLAGS = #TODO bring this back -Wall -Wextra -Werror

CC = cc

all : $(NAME)

$(NAME):
	@$(MAKE) -C libft/ all
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME) -L libft/ -lft

clean :
	@rm -f $(OBJS)

fclean : clean
	@rm -f $(NAME)

re : fclean all

relibs : re #todo include in make all
	@$(MAKE) -C libft/ fclean
	@$(MAKE) -C libft/ all

.PHONY: all clean fclean re bonus
