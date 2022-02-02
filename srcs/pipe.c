/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:45:27 by fle-blay          #+#    #+#             */
/*   Updated: 2022/02/02 10:20:13 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
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
		if (!data->pipefd[i])
		{
			free_partial_tab_pipes(data, i);
			custom_exit(data, 1, "malloc fail");
		}
		if (pipe(data->pipefd[i]))
		{
			free_partial_tab_pipes(data, i);
			custom_exit(data, 1, "pipe fail");
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

void	print_pipes(t_data *data)
{
	int i;

	i = 0;
	while (i < data->ac - 4)
	{
		fprintf(stderr, "data->pipefd[%d]: Read : %d->%d - Write : %d->%d\n", \
		i, data->pipefd[i][0], fcntl(data->pipefd[i][0], F_GETFD),\
		data->pipefd[i][1], fcntl(data->pipefd[i][1], F_GETFD));
		i++;
	}
}

void	kill_pipes(int start, t_data *data)
{
	int i;

	i = 0;
	while (i < data->ac - 4)
	{
		if (i > start)
		{
			s_close(data->pipefd[i][0], data);
			s_close(data->pipefd[i][1], data);
		}
		i++;
	}
}
