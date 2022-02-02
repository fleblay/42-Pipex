/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:07:54 by fle-blay          #+#    #+#             */
/*   Updated: 2022/02/02 19:33:02 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

static void	treat_here_doc(t_data *data)
{
	char	*ret;
	int		lenlimiter;

	lenlimiter = ft_strlen(data->av[2]);
	data->fd1 = s_open("./.heredoc_tmp", O_CREAT | O_RDWR, S_IRWXU, data);
	ret = get_next_line(0);
	while (ret)
	{
		if (!ft_strncmp(ret, data->av[2], lenlimiter)
			&& ((int)ft_strlen(ret) == lenlimiter + 1))
			break ;
		write(data->fd1, ret, ft_strlen(ret));
		free(ret);
		ret = get_next_line(0);
	}
	free(ret);
	s_close(data->fd1, data);
	data->fd1 = s_open("./.heredoc_tmp", O_RDONLY, 0, data);
	s_unlink("./.heredoc_tmp", data);
	s_dup2(data->fd1, 0, data);
	s_close(data->fd1, data);
}

static void	treat_child(int i, t_data *data)
{
	if (i == 0 && !data->hd)
	{
		data->fd1 = s_open(data->av[1], O_RDONLY, 0, data);
		s_dup2(data->fd1, 0, data);
		s_close(data->fd1, data);
	}
	else if (i == 0 && data->hd)
	{
		treat_here_doc(data);
		i++;
	}
	if (i < data->ac - 4)
	{
		kill_pipes(i, data);
		s_close(data->pipefd[i][0], data);
		s_dup2(data->pipefd[i][1], 1, data);
		s_close(data->pipefd[i][1], data);
	}
	else
	{
		if (data->hd)
			data->fd2 = s_open(data->av[i + 3],
					O_CREAT | O_WRONLY | O_APPEND, S_IRWXU, data);
		else
			data->fd2 = s_open(data->av[i + 3],
					O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU, data);
		s_dup2(data->fd2, 1, data);
		s_close(data->fd2, data);
	}
	try_cmd(i + 2, data);
	fprintf(stderr, "\x1b[31mENFANT %d just avant execve child \n\x1b[0m", i);
	print_pipes(data);
	exit(execve(data->cmds[i + 2][0], data->cmds[i + 2], data->env));
}

void	make_fork(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->ac - 3)
	{
		data->child[i] = s_fork(data);
		if (data->child[i] == 0)
			treat_child(i, data);
		else if (i < data->ac - 4)
		{
			s_close(data->pipefd[i][1], data);
			s_dup2(data->pipefd[i][0], 0, data);
			s_close(data->pipefd[i][0], data);
		}
		else
		{
			waitpid(data->child[i], &(data->status), 0);
			if (WIFEXITED(data->status) && WEXITSTATUS(data->status) != 0)
				data->status = WEXITSTATUS(data->status);
			while (wait(NULL) > 0);
		}
		fprintf(stderr, "\x1b[31mPARENT %d just avant i++\n\x1b[0m", i);
		print_pipes(data);
		i++;
	}
}
