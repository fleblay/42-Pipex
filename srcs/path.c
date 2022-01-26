/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:41:07 by fle-blay          #+#    #+#             */
/*   Updated: 2022/01/26 17:39:41 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void	get_path(t_data *data)
{
	int	i;

	i = 0;
	if (!data)
		return ;
	while (ft_strncmp(data->env[i], "PATH=", 5))
		i++;
	data->path = ft_split(data->env[i] + 5, ':');
	if (!data->path)
	{
		data->error = 1;
		return ;
	}
}

void	print_path(t_data *data)
{
	int	i;

	i = 0;
	while (data->path[i])
	{
		printf("path[%d] : >%s<\n", i, data->path[i]);
		i++;
	}
}

void	free_path(t_data *data)
{
	int	i;

	i = 0;
	if (!data->path)
		return ;
	while (data->path[i])
	{
		free(data->path[i]);
		i++;
	}
	free(data->path);
}

void	get_prog_location(t_data *data)
{
	int		i;
	int		j;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = NULL; 
	while (data->cmds[i])
	{
		j = 0;
		while (data->path[j])
		{
			tmp = ft_strjoin(data->path[j], "/");
			tmp2 = ft_strjoin(tmp, data->cmds[i][0]);
			free(tmp);
			if (!access(tmp2, F_OK))
			{
				printf("prog : %s\n", tmp2);
				free(data->cmds[i][0]);
				data->cmds[i][0] = tmp2;
				data->cmds_type[i] = 1;
			}
			else
				free(tmp2);
			j++;
		}
		i++;
	}
}
