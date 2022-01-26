/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:43:11 by fle-blay          #+#    #+#             */
/*   Updated: 2022/01/26 12:52:58 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char *av[], char *env[])
{
	t_data	data;

	(void)av;
	(void)env;
	if (ac < 5)
		return (0);
	data = (t_data){0};
	get_cmds(&data, ac, av);
	print_cmds(&data);
	free_cmds(&data);
	return (0);
}
