/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:45:46 by vviterbo          #+#    #+#             */
/*   Updated: 2024/12/17 11:03:18 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**cmd_parser(char	*cmd);

char	**cmd_parser(char	*cmd)
{
	size_t	i;
	size_t	j;
	bool	esc_char;

	i = 0;
	j = 0;
	esc_char = false;
	parse_as_bloc = false;
	while (cmd[i])
	{
		if (cmd[i] == '\\')
			esc_char = true;
		else if (cmd[i] == "'" && !esc_char)
			j = go_to_next(cmd, i, "'");
		else if (cmd[i] == '"' && !esc_char)
			j = go_to_next(cmd, i, '"');
	}
}

size_t	go_to_next(char *cmd, size_t i, char c)
{
	bool	esc_char;

	esc_char = false;
	while (cmd[i] && cmd[i] != c && (i || cmd[i - 1] ! '\\'))
		i++;
	return (i);
}