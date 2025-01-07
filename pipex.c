/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:42:05 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/07 17:48:09 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"



#include <stdio.h>





int		*ft_init_pipe(int fds[]);
pid_t	ft_fork(void);

int	main(int argc, char *argv[], char *envp[])
{
	int		pipe_fd[2];
	pid_t	pid[2];
	int		exit_status[2];

	if (argc != 5)
		return (1);
	ft_init_pipe(pipe_fd);
	pid[0] = ft_fork();
	if (pid[0] == 0)
	{
		close(pipe_fd[READ_END]);
		sender_process(argv[1], pipe_fd, argv[2], envp);
	}
	else
	{
		pid[1] = ft_fork();
		if (pid[1] == 0)
		{
			close(pipe_fd[WRITE_END]);
			receiver_process(argv[4], pipe_fd, argv[3], envp);
		}
	}
	close(pipe_fd[READ_END]);
	close(pipe_fd[WRITE_END]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	while (!waitpid(pid[0], &(exit_status[0]), WCONTINUED)
		&& !waitpid(pid[1], &(exit_status[1]), WCONTINUED))
		WIFEXITED(exit_status[1]);
	fprintf(stderr, "FINISHED !\n");
	fprintf(stderr, "exit status sender : %i, receiver : %i\n", exit_status[0], exit_status[1]);
	return (exit_status[1]);
}

int	*ft_init_pipe(int fds[])
{
	if (pipe(fds))
	{
		perror("Could not initialize pipe");
		exit(EXIT_FAILURE);
	}
	return (fds);
}

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Could not initialize child process");
		exit(EXIT_FAILURE);
	}
	return (pid);
}
