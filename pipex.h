/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:33:24 by vviterbo          #+#    #+#             */
/*   Updated: 2024/12/19 05:54:16 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# include "libft/libft.h"

# define READ_END 0
# define WRITE_END 1

char	**cmd_parser(char *cmd);
size_t	go_to_next(char *cmd, size_t i, char c);
char	**ft_array_append(char **array, char *str);
char	*ft_coalesce_char(char *str, char c, bool esc);

#endif