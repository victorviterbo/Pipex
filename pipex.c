/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:42:05 by vviterbo          #+#    #+#             */
/*   Updated: 2024/12/10 17:54:52 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		*ft_init_pipe(int fds[]);
pid_t	ft_fork(void);

int	main(int argc, char *argv[])
{
	int		pipe_fd[2];
	pid_t	pid;
	char	buf;

	ft_init_pipe(pipe_fd);
	pid = ft_fork();
	if (pid > 0)
	{
		close(pipe_fd[READ_END]);
		while (read(pipe_fd[0], &buf, 1) > 0)
		{
			write(STDOUT_FILENO, &buf, 1);
		}
		close(pipe_fd[0]);
		exit(EXIT_SUCCESS);
	}
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
