/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receiver_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:01:26 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/05 16:25:00 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	receiver_process(char *outfname, int pipe_fd[], char *cmd, char **envp);

void	receiver_process(char *outfname, int pipe_fd[], char *cmd, char **envp)
{
	char	**args;
	int		bytes_read;
	int		fd;

	args = ft_cmd_parser(cmd);
	if (!args)
		return ;
	fd = open(outfname, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (dup2(pipe_fd[READ_END], STDIN_FILENO) == -1)
		perror("Receiver dup2 failed on pipe !");
	if (dup2(fd, STDOUT_FILENO) == -1)
		perror("Receiver dup2 failed on redirection");
	if (execve(args[0], args, envp) == -1)
		perror("Receiver execve failed !");
}
