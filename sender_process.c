/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sender_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:01:14 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/07 17:09:16 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	sender_process(char *infname, int pipe_fd[], char *cmd, char **envp);

void	sender_process(char *infname, int pipe_fd[], char *cmd, char **envp)
{
	char	*executable;
	char	**args;
	int		fd;

	args = ft_cmd_parser(cmd);
	executable = find_execpath(args[0], envp);
	if (!executable)
		ft_perror_exit("Sender cannot find executable");
	if (!args)
		return ;
	fd = open(infname, O_RDONLY);
	if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
		ft_perror_exit("Sender dup2 failed on pipe");
	if (dup2(fd, STDIN_FILENO) == -1)
		ft_perror_exit("Sender dup2 failed input redirection");
	if (execve(executable, args, envp) == -1)
		ft_perror_exit("Sender execve failed");
}
