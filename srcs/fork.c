/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:09:57 by fle-blay          #+#    #+#             */
/*   Updated: 2022/01/28 17:02:45 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

void	make_fork(t_data *data)
{
	int	i;
	int	return_value;

	i = 0;
	while (i < data->ac - 4)
	{
		data->child[i] = fork();
		if (data->child[i] == -1)
			custom_exit(data, 2, "fork fail");
		if (data->child[i] == 0)
		{
			if (i == 0)
			{
				data->fd1 = open(data->cmds[1][0], O_RDONLY);
				if (data->fd1 == -1)
					custom_exit(data, 2, "open fail");
				if (dup2(data->fd1, 0)== -1)
					custom_exit(data, 2, "dup2 fail");
				if (close(data->fd1) == -1)
					custom_exit(data, 2, "close fail");
			}
			close(data->pipefd[i][0]);
			dup2(data->pipefd[i][1], 1);
			close(data->pipefd[i][1]);
			if (execve(data->cmds[i + 2][0], data->cmds[i + 2], NULL) == -1)
				custom_exit(data, 2, "execve fail");
		}
		else
		{
			close(data->pipefd[i][1]);
			dup2(data->pipefd[i][0], 0);
			close(data->pipefd[i][0]);
			// verif le retour du child via le wait pour verif val
			// et print l'erreur eventuelle
			if (wait(&return_value) == -1)
				custom_exit(data, 2, "wait fail");
			// check val de return_value et sortir en consequence ?
			i++;
		}
	}
	// ajouter check erreur comme au dessus
	data->fd2 = open(data->cmds[i + 3][0], O_CREAT | O_RDWR, S_IRWXU);
	dup2(data->fd2, 1);
	close(data->fd2);
	exit(execve(data->cmds[i + 2][0], data->cmds[i + 2], NULL));
}
