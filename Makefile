# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/01 12:45:22 by vviterbo          #+#    #+#              #
#    Updated: 2025/01/08 20:53:02 by vviterbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = pipex.c sender_process.c receiver_process.c utils.c

CFLAGS =  -Wall -Wextra -Werror

CC = cc

all : $(NAME)

$(NAME) : $(SRCS)
	@$(MAKE) -C libft/ all
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME) -L libft/ -lft
	@echo "$(NAME) compiled successfully"

clean :
	@$(MAKE) -C libft/ clean

fclean : clean
	@$(MAKE) -C libft/ fclean
	@rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re bonus
