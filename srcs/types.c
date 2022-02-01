/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 10:48:28 by fle-blay          #+#    #+#             */
/*   Updated: 2022/02/01 15:01:16 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

void	set_types(t_data *data)
{
	int	i;

	i = 1;
	data->cmds_type[0] = -2;
	while (i < data->ac)
	{
		data->cmds_type[i] = -1;
		i++;
	}
}

void	print_types(t_data *data)
{
	int	i;

	if (!data->cmds_type)
		return ;
	i = 0;
	while (i < data->ac)
	{
		printf("cmds_type[%d] : >%d<\n", i, data->cmds_type[i]);
		i++;
	}
}

void	try_cmd(int i, t_data *data)
{
	int		j;
	char	*try;

	if (!data->av[i][0])
		error_cmd(data, "pipex: permission denied: ", data->av[i], 126);
	if (!data->cmds[i][0])
		return ;
	if (get_file_status(data->cmds[i][0], data, i, 0) >= 0)
		return ;
	j = -1;
	while (data->path && data->path[++j])
	{
		try = ft_strjoin2(data->path[j], "/", data->cmds[i][0]);
		if (!try)
			custom_exit(data, 1, "strjoin2 fail");
		if (get_file_status(try, data, i, 1) >= 0)
			break ;
		else
			free(try);
	}
}

int	get_file_status(char *try, t_data *data, int i, int swap)
{
	if (!ft_strchr(try, '/'))
		return (-1);
	if (!access(try, F_OK))
		data->cmds_type[i] = 0;
	if (!access(try, R_OK))
		data->cmds_type[i] += 4;
	if (!access(try, W_OK))
		data->cmds_type[i] += 2;
	if (!access(try, X_OK))
		data->cmds_type[i] += 1;
	if (data->cmds_type[i] >= 0 && swap)
	{
		free(data->cmds[i][0]);
		data->cmds[i][0] = try;
	}
	return (data->cmds_type[i]);
}

/*
void	get_status(t_data *data)
{
	int		i;

	i = 1;
	while (data->cmds[++i] && i < data->ac - 1)
	{
		printf("i : %d\n", i);
		try_cmd(i, data);
	}
}
*/
