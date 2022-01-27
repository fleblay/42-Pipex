/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:43:11 by fle-blay          #+#    #+#             */
/*   Updated: 2022/01/27 12:02:51 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char *av[], char *env[])
{
	t_data	data;

	if (ac < 5)
		return (0);
	data = (t_data){.ac = ac, .av = av, .env = env};
	data.cmds_type = (int *)malloc((ac) * sizeof(int));
	if (!data.cmds_type)
		return (0);
	set_types(&data);
	print_types(&data);

	get_cmds(&data);
	print_cmds(&data);

	print_types(&data);

	get_path(&data);
	print_path(&data);

	get_status(&data);
	print_cmds(&data);
	print_types(&data);

	free(data.cmds_type);
	free_cmds(&data);
	free_path(&data);
	return (0);
}
