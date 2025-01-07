/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sender_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:01:14 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/07 11:49:25 by vviterbo         ###   ########.fr       */
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
	executable = ft_strjoin("/bin/", args[0]);//ft_strdup(args[0]);
	// TODO add /bin/
	if (!args)
		return ;
	fd = open(infname, O_RDONLY);
	if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) == -1)
		perror("Sender dup2 failed on pipe");
	if (dup2(fd, STDIN_FILENO) == -1)
		perror("Sender dup2 failed input redirection");
	if (execve(executable, args, envp) == -1)
		perror("Sender execve failed");
}
