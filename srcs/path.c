/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:41:07 by fle-blay          #+#    #+#             */
/*   Updated: 2022/02/02 10:35:39 by fle-blay         ###   ########.fr       */
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
	while (data->env[i] && ft_strncmp(data->env[i], "PATH=", 5))
		i++;
	if (!data->env[i])
	{
		data->path = NULL;
		return ;
	}
	data->path = ft_split(data->env[i] + 5, ':');
	if (!data->path)
		custom_exit(data, 1, "split fail");
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

/*
For debug
*/

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
