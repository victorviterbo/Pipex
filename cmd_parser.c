/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:45:46 by vviterbo          #+#    #+#             */
/*   Updated: 2024/12/18 20:53:38 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**cmd_parser(char *cmd);
char	**ft_array_append(char **array, char *str);

char	**cmd_parser(char	*cmd)
{
	size_t	i;
	size_t	j;
	bool	esc_char;
	char	**spl_args;

	i = 0;
	j = 0;
	spl_args = ft_calloc(1, sizeof(char *));
	esc_char = false;
	while (cmd[i])
	{
		if (cmd[i] == '\\')
			esc_char = true;
		else if (cmd[i] == "'" && !esc_char)
			i = go_to_next(cmd, i, "'");
		else if (cmd[i] == '"' && !esc_char)
			i = go_to_next(cmd, i, '"');
		else if (cmd[i] == ' ' && !esc_char)
		{
			spl_args = ft_array_append(spl_args, ft_substr(cmd, j, i - j));
			j = i + 1;
		}
		i++;
	}
}

size_t	go_to_next(char *cmd, size_t i, char c)
{
	bool	esc_char;

	esc_char = false;
	while (cmd[i] && cmd[i] != c && (i || cmd[i - 1] != '\\'))
		i++;
	return (i);
}

char	**ft_array_append(char **array, char *str)
{
	size_t	i;
	size_t	size;
	char	**concatenated;

	size = ft_arrlen(array);
	concatenated = ft_calloc(size + 1, sizeof(char *));
	i = 0;
	while (i < size)
	{
		*(concatenated + i) = *(array + i);
	}
	*(concatenated + size) = str;
	*(concatenated + size + 1) = ft_strdup("");
	free(array);
	return (concatenated);
}
