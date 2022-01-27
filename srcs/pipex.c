/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:43:11 by fle-blay          #+#    #+#             */
/*   Updated: 2022/01/27 18:20:32 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void	make_fork(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->ac - 4)
	{
		data->child[i] = fork();
		if (data->child[i] == -1)
			custom_exit(data, 1);
		if (!data->child[i])
		{
			ft_putnbr_fd(i, 2);
			ft_putstr_fd("\n", 2);
			if (i == 0)
			{
				ft_putstr_fd("i = 0, on close le cote read du pipe\n", 2);
				close(data->pipefd[i][0]);
			}
			if (i == data->ac - 5)
			{
				ft_putstr_fd("i = ac - 5, on close le cote write du pipe\n", 2);
				close(data->pipefd[i][1]);
			}
			if (i != 0)
				dup2(data->pipefd[i][0], 0);
			if (i < data->ac - 4)
				dup2(data->pipefd[i][1], 1);
			if (i != 0)
				waitpid(data->child[i - 1], NULL,  0);
			ft_putstr_fd("on a finit d'attendre\n", 2);
			printf("this is %d writing\n", i);
			fflush(NULL);
			execve(data->cmds[i + 2][0], data->cmds[i + 2], NULL);
		}
		i++;
	}
	ft_putstr_fd("parent :", 2);
	ft_putnbr_fd(i, 2);
	ft_putstr_fd("\n", 2);
	waitpid(data->child[i - 1], NULL, 0);
}

int	main(int ac, char *av[], char *env[])
{
	t_data	data;

	data = (t_data){.ac = ac, .av = av, .env = env};
	if (ac < 5)
		return (0);
	init_data(&data);

	make_fork(&data);

	custom_exit(&data, 0);
	return (0);
}
