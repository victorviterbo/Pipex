# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/01 12:45:22 by vviterbo          #+#    #+#              #
#    Updated: 2025/01/05 16:26:48 by vviterbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = pipex.c sender_process.c receiver_process.c cmd_parser.c

OBJS = $(patsubst %.c, %.o, $(SRCS))

CFLAGS = #-Wall -Wextra -Werror

CC = cc

all: $(NAME)

clean :
	@rm -f $(OBJS)

fclean : clean
	@rm -f $(NAME)

re : fclean all

relibs : all
	@$(MAKE) -C libft/ fclean
	@$(MAKE) -C libft/ all
	

$(NAME):
	@$(MAKE) -C libft/ all
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME) -L libft/ -lft

.PHONY: all clean fclean re bonus
