/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:43:11 by fle-blay          #+#    #+#             */
/*   Updated: 2022/01/28 12:29:08 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

void	make_fork(t_data *data)
{
	int fd1;
	int	fd2;
	int	i;

	i = 0;
	while (i < data->ac - 4)
	{
		data->child[i] = fork();
		if (data->child[i] == -1)
			custom_exit(data, 1, "fork fail");
		if (data->child[i] == 0)
		{
			if (i == 0)
			{
				fd1 = open(data->cmds[1][0], O_RDONLY);
				dup2(fd1, 0);
				close (fd1);
			}
			close(data->pipefd[i][0]);
			dup2(data->pipefd[i][1], 1);
			close(data->pipefd[i][1]);
			exit(execve(data->cmds[i + 2][0], data->cmds[i + 2], NULL));
		}
		else
		{
			close(data->pipefd[i][1]);
			dup2(data->pipefd[i][0], 0);
			close(data->pipefd[i][0]);
			wait(NULL);
			i++;
		}
	}
	fd2 = open(data->cmds[i + 3][0], O_CREAT | O_RDWR, S_IRWXU);
	dup2(fd2, 1);
	close(fd2);
	exit(execve(data->cmds[i + 2][0], data->cmds[i + 2], NULL));
}

int	main(int ac, char *av[], char *env[])
{
	t_data	data;

	data = (t_data){.ac = ac, .av = av, .env = env};
	if (ac < 5)
		return (0);
	init_data(&data);

	make_fork(&data);

	custom_exit(&data, 0, NULL);
	return (0);
}
