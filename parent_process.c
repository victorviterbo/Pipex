/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:01:14 by vviterbo          #+#    #+#             */
/*   Updated: 2024/12/13 15:00:23 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_process(int fd);
char	*parse_file(int fd);

void	parent_process(int fd)
{
	char	*fcontent;

	fcontent = parse_file(fd);
	execve();
}

char	*parse_file(int fd)
{
	int		byte_read;
	char	*buffer;
	char	*fcontent;

	byte_read = 1;
	buffer = ft_calloc(1, sizeof(char));
	fcontent = ft_calloc(1, sizeof(char));
	while (byte_read)
	{
		byte_read = read(fd, buffer, 1);
		fcontent = ft_strjoin_ip(fcontent, buffer, 1);
	}
	return (fcontent);
}