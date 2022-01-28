/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:27:28 by fle-blay          #+#    #+#             */
/*   Updated: 2022/01/28 09:10:56 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include "libft.h"
#include <unistd.h>

void	init_data(t_data *data)
{
	data->cmds_type = (int *)malloc((data->ac) * sizeof(int));
	if (!data->cmds_type)
		custom_exit(data, 1);
	set_types(data);
	get_cmds(data);
	if (data->error)
		custom_exit(data, 1);
	get_path(data);
	if (data->error)
		custom_exit(data, 1);
	get_status(data);
	if (data->error)
		custom_exit(data, 1);
	data->pipefd = (int **)malloc((data->ac - 4) * sizeof(int *));
	if (!data->pipefd)
		custom_exit(data, 1);
	create_pipes(data);
	if (data->error)
		custom_exit(data, 1);
	data->child = (pid_t *)malloc((data->ac - 4) * sizeof(pid_t));
	if (!data->child)
		custom_exit(data, 1);
	print_cmds(data);
	print_types(data);
}

void	custom_exit(t_data *data, int error)
{
	if (data->error || error)
		ft_putstr_fd("Error\n", 2);
	free(data->cmds_type);
	free_cmds(data);
	free_path(data);
	free_pipes(data);
	free(data->child);
	exit(0);
}
