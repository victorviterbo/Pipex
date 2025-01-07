/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:33:24 by vviterbo          #+#    #+#             */
/*   Updated: 2025/01/07 20:16:49 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# include "libft/libft.h"

# define READ_END 0
# define WRITE_END 1

int		parent_process(int pid[], int pipe_fd[]);
int		*ft_init_pipe(int fds[]);
pid_t	ft_fork(void);
void	ft_perror_exit(const char *message);

void	receiver_process(char *outfname, int pipe_fd[], char *cmd, char **envp);

void	sender_process(char *infname, int pipe_fd[], char *cmd, char **envp);

char	*find_execpath(char *exec, char *env[]);
char	**ft_cmd_parser(char *cmd);
size_t	go_to_next(char *cmd, size_t i, char c);
char	*ft_coalesce_char(char *str, char c, bool esc, bool inplace);

#endif