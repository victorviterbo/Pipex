/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:45:46 by vviterbo          #+#    #+#             */
/*   Updated: 2024/12/15 20:05:05 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**cmd_parser(char	*cmd);

char	**cmd_parser(char	*cmd)
{
	size_t	i;
	size_t	j;
	bool	esc_char;
	bool	parse_as_bloc;

	i = 0;
	esc_char = false;
	parse_as_bloc = false;
	while (cmd[i])
	{
		if (cmd[i] == '\\')
			esc_char = true;
		else if (cmd[i] == '"' || cmd[i] == "'")
			parse_as_bloc = !parse_as_bloc;
		else 
	}
}

size_t	go_to_next_space(char *cmd, size_t i)
{
	while (cmd[i] && cmd[i] != '"' &&w)
}