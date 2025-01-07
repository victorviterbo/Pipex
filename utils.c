/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:45:46 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/07 20:16:39 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_execpath(char *exec, char *env[]);
char	**ft_cmd_parser(char *cmd);
size_t	go_to_next(char *cmd, size_t i, char c);
char	*ft_coalesce_char(char *str, char c, bool esc, bool inplace);

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

char	**ft_cmd_parser(char *cmd)
{
	size_t	i;
	size_t	j;
	char	**spl_args;

	i = 0;
	j = 0;
	cmd = ft_coalesce_char(cmd, ' ', true, false);
	spl_args = ft_calloc(1, sizeof(char *));
	while (cmd[i])
	{
		if (cmd[i] == '\\')
			i++;
		else if (cmd[i] == '\'' || cmd[i] == '"')// || cmd[i] == '{'
			i = go_to_next(cmd, i, cmd[i]);
		else if (ft_iswhitespace_eq(cmd[i]))
		{
			spl_args = ft_array_append(spl_args, ft_substr(cmd, j, i - j),
					false);
			j = i + 1;
		}
		if (i < 0)
			return (NULL);
		i++;
	}
	if (i != j)
		spl_args = ft_array_append(spl_args, ft_substr(cmd, j, i - j), false);
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

