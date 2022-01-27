/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:41:07 by fle-blay          #+#    #+#             */
/*   Updated: 2022/01/27 11:40:03 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

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
