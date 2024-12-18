/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:01:14 by vviterbo          #+#    #+#             */
/*   Updated: 2024/12/18 15:56:44 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_process(int fd, char **cmds);
char	*parse_file(int fd);

void	parent_process(int fd, char **cmds)
{
	char	*fcontent;
	char	**args;

	fcontent = ft_readfile(fd);
	*cmds = ft_strjoin_ip("/bin/", *cmds, 2);
	args = ft_calloc(2, sizeof(char));
	//execve();
}
