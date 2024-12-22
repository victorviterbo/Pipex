/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:45:46 by vviterbo          #+#    #+#             */
/*   Updated: 2024/12/22 09:21:43 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**cmd_parser(char *cmd);
size_t	go_to_next(char *cmd, size_t i, char c);
char	**ft_array_append(char **array, char *str);
char	*ft_coalesce_char(char *str, char c, bool esc, bool inplace);


void	print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_printf("%i : >%s<\n", i, array[i]);
		i++;
	}
}




char	**cmd_parser(char	*cmd)
{
	size_t	i;
	size_t	j;
	bool	esc_char;
	char	**spl_args;

	i = 0;
	j = 0;
	cmd = ft_coalesce_char(cmd, ' ', true, false);
	spl_args = ft_calloc(1, sizeof(char *));
	esc_char = false;
	while (cmd[i])
	{
		if (cmd[i] == '\\')
			esc_char = true;
		else if (cmd[i] == '\'' && !esc_char)
		{
			i = go_to_next(cmd, i, '\'');
		}
		else if (cmd[i] == '"' && !esc_char)
			i = go_to_next(cmd, i, '"');
		else if (cmd[i] == ' ' && !esc_char)
		{
			spl_args = ft_array_append(spl_args, ft_substr(cmd, j, i - j));
			j = i + 1;
		}
		i++;
	}
	if (i != j)
		spl_args = ft_array_append(spl_args, ft_substr(cmd, j, i - j));
	return (spl_args);
}

size_t	go_to_next(char *cmd, size_t i, char c)
{
	i++;
	while (cmd[i] && cmd[i] != c && (!i || cmd[i - 1] != '\\'))
		i++;
	return (i);
}

char	**ft_array_append(char **array, char *str)
{
	size_t	i;
	char	**concatenated;

	concatenated = ft_calloc(ft_arrlen(array) + 2, sizeof(char *));
	i = 0;
	while (array[i])
	{
		concatenated[i] = array[i];
		i++;
	}
	concatenated[i] = str;
	concatenated[i + 1] = NULL;
	free(array);
	return (concatenated);
}

char	*ft_coalesce_char(char *str, char c, bool esc, bool inplace)
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
		if (str[i] == '\\' && esc && str[i + 1] == c)
		{
			coalesced = ft_strjoin_ip(coalesced, ft_ctoa(c), 3);
			coalesced = ft_strjoin_ip(coalesced, "\\", 1);
			coalesced = ft_strjoin_ip(coalesced, ft_ctoa(c), 3);
			j = i;
		}
		else if (str[i] == c && (!i || (j + 1 >= i)))
			j = i;
		else if (str[i] == c)
		{
			coalesced = ft_strjoin_ip(coalesced, ft_substr(str, j, i - j), 3);
			j = i;
		}
		i++;
	}
	if (i && str[i - 1] != c)
		coalesced = ft_strjoin_ip(coalesced, ft_substr(str, j, i - j), 3);
	else if (i)
		coalesced = ft_strjoin_ip(coalesced, ft_substr(str, j, i - j), 3);
	if (inplace)
		free(str);
	return (coalesced);
}

