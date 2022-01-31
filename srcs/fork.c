/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:09:57 by fle-blay          #+#    #+#             */
/*   Updated: 2022/01/31 10:59:03 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

void	make_fork(t_data *data)
{
	int	i;
	int	return_value;

	i = 0;
	while (i < data->ac - 4)
	{
		data->child[i] = s_fork(data);
		if (data->child[i] == 0)
		{
			if (i == 0)
			{
				data->fd1 = s_open(data->cmds[1][0], O_RDONLY, 0, data);
				s_dup2(data->fd1, 0, data);
				s_close(data->fd1, data);
			}
			s_close(data->pipefd[i][0], data);
			s_dup2(data->pipefd[i][1], 1, data);
			s_close(data->pipefd[i][1], data);
			s_execve(data->cmds[i + 2][0], data->cmds[i + 2], data->env, data);
		}
		else
		{
			s_close(data->pipefd[i][1], data);
			s_dup2(data->pipefd[i][0], 0, data);
			s_close(data->pipefd[i][0], data);
			// verif le retour du child via le wait pour verif val
			// et print l'erreur eventuelle
			s_wait(&return_value, data);
			// check val de return_value et sortir en consequence ?
			i++;
		}
	}
	// ajouter check erreur comme au dessus
	data->fd2 = s_open(data->cmds[i + 3][0], O_CREAT | O_RDWR, S_IRWXU, data);
	s_dup2(data->fd2, 1, data);
	s_close(data->fd2, data);
	exit(execve(data->cmds[i + 2][0], data->cmds[i + 2], NULL));
}
