/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:45:46 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/07 23:46:20 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_execpath(char *exec, char *env[]);
char	**ft_cmd_parser(char *cmd, bool esc);
size_t	go_to_next(char *cmd, size_t i, char c);

char	*find_execpath(char *exec, char *envp[])
{
	char	**path_list;
	char	*path_exec;
	int		i;

	i = 0;
	if (access(exec, X_OK) == 0)
		return (exec);
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	path_list = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path_list[i])
	{
		path_list[i] = ft_strjoin_ip(path_list[i], "/", 1);
		path_exec = ft_strjoin(path_list[i], exec);
		if (access(path_exec, X_OK) == 0)
			return (ft_free_array((void **)path_list, ft_arrlen(path_list)),
				path_exec);
		free(path_exec);
		i++;
	}
	return (NULL);
}

char	**ft_cmd_parser(char *cmd, bool esc)
{
	size_t	i;
	size_t	j;
	char	**spl_args;

	i = 0;
	j = 0;
	cmd = ft_coalesce_char(cmd, ' ', true);
	spl_args = ft_calloc(1, sizeof(char *));
	while (0 < i && cmd[i])
	{
		i += 2 * (cmd[i] == '\\' && esc);
		if (cmd[i] == '\'' || cmd[i] == '"')
			i = go_to_next(cmd, i, cmd[i]);
		else if (ft_iswhitespace_eq(cmd[i]))
		{
			spl_args = ft_array_append(spl_args, ft_substr(cmd, j, i - j),
					false);
			j = i + 1;
		}
		i++;
	}
	spl_args = ft_array_append(spl_args, ft_substr(cmd, j, i - j), false);
	if (i < 0)
		return (ft_free_array((void **)spl_args, ft_arrlen(spl_args)), NULL);
	return (spl_args);
}

size_t	go_to_next(char *cmd, size_t i, char c)
{
	i++;
	while (cmd[i] && cmd[i] != c && (!i || cmd[i - 1] != '\\'))
		i++;
	if (!cmd[i])
		return (-1);
	return (i);
}
