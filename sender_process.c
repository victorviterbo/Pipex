/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sender_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:01:14 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/05 16:25:08 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	sender_process(char *infname, int pipe_fd[], char *cmd, char **envp);

void	sender_process(char *infname, int pipe_fd[], char *cmd, char **envp)
{
	char	*executable;
	char	**args;
	int		fd;
	char	*buffer_tmp;

	args = ft_cmd_parser(cmd);
	executable = ft_strdup(args[0]);
	if (!args)
		return ;
	fd = open(infname, O_RDONLY);
	if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
		perror("Sender dup2 failed !");
	if (dup2(fd, STDIN_FILENO) == -1)
		perror("Sender dup2 failed !");
	if (execve(executable, args, envp) == -1)
		perror("Sender execve failed !");
}
