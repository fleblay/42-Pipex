/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:09:57 by fle-blay          #+#    #+#             */
/*   Updated: 2022/02/01 18:24:43 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

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
	if (i == 0 && data->hd)
	{
		treat_here_doc(data);
		i++;
	}
	s_close(data->pipefd[i][0], data);
	s_dup2(data->pipefd[i][1], 1, data);
	s_close(data->pipefd[i][1], data);

	/*
	ft_putstr_fd("ici", 2);
	ft_putnbr_fd(i, 2);
	s_close(data->pipefd[i + 1][0], data);
	*/
	
	try_cmd(i + 2, data);
	if (data->cmds_type[i + 2] == -1)
		error_cmd(data, "pipex: command not found: ", data->av[i + 2], 127);
	if (access(data->cmds[i + 2][0], X_OK) == -1)
		error_cmd(data, "pipex: permission denied: ", data->av[i + 2], 126);
	exit(execve(data->cmds[i + 2][0], data->cmds[i + 2], data->env));
}

static void	treat_last(int i, t_data *data)
{
	if (data->hd)
		data->fd2 = s_open(data->av[i + 3],
				O_CREAT | O_WRONLY | O_APPEND, S_IRWXU, data);
	else
		data->fd2 = s_open(data->av[i + 3],
				O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU, data);
	s_dup2(data->fd2, 1, data);
	s_close(data->fd2, data);
	try_cmd(i + 2, data);
	if (data->cmds_type[i + 2] == -1)
		error_cmd(data, "pipex: command not found: ", data->av[i + 2], 127);
	if (access(data->cmds[i + 2][0], X_OK) == -1)
		error_cmd(data, "pipex: permission denied: ", data->av[i + 2], 126);
	exit(execve(data->cmds[i + 2][0], data->cmds[i + 2], data->env));
}

//on enleve le wait avant le i++ pour ne plus timeout sur /dev/urandom | head -1

#include <sys/wait.h>

void	make_fork(t_data *data)
{
	int	i;
	int	res_wait;

	(void)res_wait;
	i = 0;
	while (i < data->ac - 4)
	{
		data->child[i] = s_fork(data);
		if (data->child[i] == 0)
			treat_child(i, data);
		else
		{
			s_close(data->pipefd[i][1], data);
			s_dup2(data->pipefd[i][0], 0, data);
			s_close(data->pipefd[i][0], data);
			i++;
		}
	}
	treat_last(i, data);
}
