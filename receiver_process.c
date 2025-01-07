/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receiver_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:01:26 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/07 11:49:26 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	receiver_process(char *outfname, int pipe_fd[], char *cmd, char **envp);

void	receiver_process(char *outfname, int pipe_fd[], char *cmd, char **envp)
{
	char	**args;
	char	*executable;
	int		fd;

	args = ft_cmd_parser(cmd);
	executable = ft_strjoin("/bin/", args[0]);//ft_strdup(args[0]);
	// TODO add /bin/
	if (!args)
		return ;
	fd = open(outfname, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (dup2(pipe_fd[READ_END], STDIN_FILENO) == -1)
		perror("Receiver dup2 failed on pipe");
	if (dup2(fd, STDOUT_FILENO) == -1)
		perror("Receiver dup2 failed on output redirection");
	if (execve(executable, args, envp) == -1)
		perror("Receiver execve failed");
}
