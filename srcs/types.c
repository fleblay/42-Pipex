/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 10:48:28 by fle-blay          #+#    #+#             */
/*   Updated: 2022/01/27 14:26:37 by fle-blay         ###   ########.fr       */
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

void	get_status(t_data *data)
{
	int		i;
	int		j;
	char	*try;

	i = -1;
	while (data->cmds[++i])
	{
		if (get_file_status(data->cmds[i][0], data, i, 0) >= 0)
			continue ;
		j = -1;
		while (data->path[++j])
		{
			try = ft_strjoin2(data->path[j], "/", data->cmds[i][0]);
			if (!try)
			{
				data->error = 1;
				return ;
			}
			if (get_file_status(try, data, i, 1) >= 0)
				break ;
			else
				free(try);
		}
	}
}

int	get_file_status(char *try, t_data *data, int i, int swap)
{
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
