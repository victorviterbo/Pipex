/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vviterbo <vviterbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:54:01 by vviterbo          #+#    #+#             */
/*   Updated: 2024/12/22 08:37:43 by vviterbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[])
{
	int		i;
	char	**parsed;

	i = 0;
	//if (argc != 2)
	//	return (1);
	(void)argc;
	//ft_printf(">%s< -> >%s<\n", argv[2], ft_coalesce_char(argv[2], '_', true));
	//ft_printf(">%s< -> >%s<\n", argv[3], ft_coalesce_char(argv[3], '_', true));
	//ft_printf(">%s< -> >%s<\n", argv[2], ft_coalesce_char(argv[2], '_', false));
	//ft_printf(">%s< -> >%s<\n\n\n", argv[3], ft_coalesce_char(argv[3], '_', false));
	parsed = cmd_parser(argv[1]);
	while (parsed[i])
	{
		ft_printf("%i : >%s<\n", i, parsed[i]);
		i++;
	}
	return (1);
}
