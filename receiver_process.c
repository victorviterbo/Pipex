/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receiver_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:01:26 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/07 18:33:57 by vviterbo         ###   ########.fr       */
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
	if (!args)
		ft_perror_exit("Receiver process command could not be parsed");
	executable = find_execpath(args[0], envp);
	if (!executable)
		ft_perror_exit("Receiver process cannot find executable");
	fd = open(outfname, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd < 0)
		ft_perror_exit("Sender open failed input file");
	if (dup2(pipe_fd[READ_END], STDIN_FILENO) == -1)
		ft_perror_exit("Receiver dup2 failed on pipe");
	if (dup2(fd, STDOUT_FILENO) == -1)
		ft_perror_exit("Receiver dup2 failed on output redirection");
	if (execve(executable, args, envp) == -1)
		ft_perror_exit("Receiver execve failed");
}
