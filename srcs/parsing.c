/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 10:11:21 by fle-blay          #+#    #+#             */
/*   Updated: 2022/01/26 15:12:35 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void	get_cmds(t_data *data, int ac, char *av[])
{
	int	i;

	data->cmds = (char ***)malloc((ac) * sizeof(char **));
	if (!data->cmds)
	{
		data->error = 1;
		return ;
	}
	i = 0;
	while (i < ac - 1)
	{
		data->cmds[i] = ft_split(av[i + 1], ' ');
		if (!data->cmds[i])
		{
			data->error = 1;
			free_partial_tab(data, i);
			return ;
		}

		i++;
	}
	data->cmds[i] = NULL;
}

void	print_cmds(t_data *data)
{
	int	i;
	int	j;

	if (data->error)
		return ;
	i = 0;
	while (data->cmds[i])
	{
		j = 0;
		while (data->cmds[i][j])
		{
			printf("cmds[%d][%d] : >%s<\n", i, j, data->cmds[i][j]);
			j++;
		}
		i++;
	}
}

void	free_cmds(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	if (data->error)
		return ;
	while (data->cmds[i])
	{
		j = 0;
		while (data->cmds[i][j])
		{
			free(data->cmds[i][j]);
			j++;
		}
		free(data->cmds[i]);
		i++;
	}
	free(data->cmds);
}

void	free_partial_tab(t_data *data,  int i)
{
	int	index;
	int index2;
	
	index = 0;
	while (index < i)
	{
		index2 = 0;
		while (data->cmds[index][index2])
		{
			free(data->cmds[index][index2]);
			index2++;
		}
		free(data->cmds[index]);
		index++;
	}
	free(data->cmds);
}

