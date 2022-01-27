/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:45:27 by fle-blay          #+#    #+#             */
/*   Updated: 2022/01/27 15:45:32 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static void	free_partial_tab_pipes(t_data *data, int i)
{
	int	index;

	index = 0;
	while (index < i)
	{
		free(data->pipefd[index]);
		index++;
	}
	free(data->pipefd);
	data->pipefd = NULL;
}

void	create_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->ac - 4)
	{
		data->pipefd[i] = (int *)malloc(2 * sizeof(int));
		if (!data->pipefd[i] || pipe(data->pipefd[i]))
		{
			data->error = 1;
			free_partial_tab_pipes(data, i);
			return ;
		}
		i++;
	}
}

void	free_pipes(t_data *data)
{
	int	i;

	i = 0;
	if (!data->pipefd)
		return ;
	while (i < data->ac - 4)
	{
		free(data->pipefd[i]);
		i++;
	}
	free(data->pipefd);
}
