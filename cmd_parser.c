/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:45:46 by vviterbo          #+#    #+#             */
/*   Updated: 2024/12/19 15:38:01 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**cmd_parser(char *cmd);
size_t	go_to_next(char *cmd, size_t i, char c);
char	**ft_array_append(char **array, char *str);
char	*ft_coalesce_char(char *str, char c, bool esc);

char	**cmd_parser(char	*cmd)
{
	size_t	i;
	size_t	j;
	bool	esc_char;
	char	**spl_args;

	i = 0;
	j = 0;
	cmd = ft_coalesce_char(cmd, ' ', true);
	spl_args = ft_calloc(1, sizeof(char *));
	esc_char = false;
	while (cmd[i])
	{
		ft_printf("%i\n", i);
		if (cmd[i] == '\\')
			esc_char = true;
		else if (cmd[i] == '\'' && !esc_char)
			i = go_to_next(cmd, i, '\'');
		else if (cmd[i] == '"' && !esc_char)
			i = go_to_next(cmd, i, '"');
		else if (cmd[i] == ' ' && (!i || cmd[i + 1] != ' ' || cmd[i - 1] != ' ') && !esc_char)
		{
			spl_args = ft_array_append(spl_args, ft_substr(cmd, j, i - j));
			ft_printf("appending >%s<, %i, %i\n", ft_substr(cmd, j, i - j), i, j);
			j = i + 1;
		}
		i++;
	}
	ft_printf("-- %i, >%c< - >%c<\n", i, cmd[i], cmd[j]);
	if (i != j)
		spl_args = ft_array_append(spl_args, ft_substr(cmd, j, i - j));
	ft_printf("coucou\n");
	ft_printf("2 -- %i, >%c< - >%c<\n", i, cmd[i], cmd[j]);
	return (spl_args);
}

size_t	go_to_next(char *cmd, size_t i, char c)
{
	while (cmd[i] && cmd[i] != c && (!i || cmd[i - 1] != '\\'))
		i++;
	return (i);
}

char	**ft_array_append(char **array, char *str)
{
	size_t	i;
	char	**concatenated;

	concatenated = ft_calloc(ft_arrlen(array) + 1, sizeof(char *));
	i = 0;
	while (*(array + i))
	{
		*(concatenated + i) = *(array + i);
		i++;
	}
	*(concatenated + i) = str;
	*(concatenated + i + 1) = NULL;
	free(array);
	return (concatenated);
}

char	*ft_coalesce_char(char *str, char c, bool esc)
{
	char	*coalesced;
	size_t	i;
	size_t	j;

	coalesced = ft_calloc(1, sizeof(char *));
	i = 0;
	while (str[i] && str[i] == c && str[i + 1] == c)
		i++;
	j = i;
	while (str[i])
	{
		ft_printf("%i %i\n", i, j);
		if (str[i] == c && (!i || (j >= i + 1)))
			j = i;
		else if (str[i] == c && (str[i - 1] != '\\' || !esc))
		{
			ft_printf("-> %i %i\n", i, j);
			coalesced = ft_strjoin_ip(coalesced, ft_substr(str, j, i - j), 3);
			j = i;
		}
		i++;
	}
	if (i && str[i - 1] != c)
		coalesced = ft_strjoin_ip(coalesced, ft_substr(str, j, i - j), 3);
	return (coalesced);
}
