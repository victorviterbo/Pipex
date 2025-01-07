/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:42:05 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/07 20:18:49 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"



#include <stdio.h>

int		parent_process(int pid[], int pipe_fd[]);
int		*ft_init_pipe(int fds[]);
pid_t	ft_fork(void);
void	ft_perror_exit(const char *message);

int	main(int argc, char *argv[], char *envp[])
{
	int		pipe_fd[2];
	pid_t	pid[2];

	if (argc != 5)
		return (EXIT_FAILURE);
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
	return (parent_process(pid, pipe_fd));
}

int	parent_process(int pid[], int pipe_fd[])
{
	int	exit_status[2];
	int	waitpid_status[2];

	close(pipe_fd[READ_END]);
	close(pipe_fd[WRITE_END]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	waitpid_status[0] = 0;
	waitpid_status[1] = 0;
	while (waitpid_status[0] == 0 || waitpid_status[1] == 0)
	{
		waitpid_status[0] = waitpid(pid[0], &(exit_status[0]), 0);
		if (waitpid_status[0] == -1)
			ft_perror_exit("waitpid on sender exception in parent process");
		waitpid_status[1] = waitpid(pid[1], &(exit_status[1]), 0);//WUNTRACED
		if (waitpid_status[1] == -1)
			ft_perror_exit("waitpid on receiver exception in parent process");
	}
	if (exit_status[1] && exit_status[1] % 256 == 0)
		exit_status[1] = 1;
	return (exit_status[1]);
}


int	*ft_init_pipe(int fds[])
{
	if (pipe(fds) == -1)
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
	if (pid == -1)
	{
		perror("Could not initialize child process");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	ft_perror_exit(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}
