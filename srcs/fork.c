/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:09:57 by fle-blay          #+#    #+#             */
/*   Updated: 2022/01/31 13:14:17 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include <stddef.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

static void	treat_child(int i, t_data *data)
{
	if (i == 0 && ft_strcmp(data->cmds[1][0], "here_doc"))
	{
		data->fd1 = s_open(data->cmds[1][0], O_RDONLY, 0, data);
		s_dup2(data->fd1, 0, data);
		s_close(data->fd1, data);
	}
	if (i == 0 && !ft_strcmp(data->cmds[1][0], "here_doc"))
	{
		data->fd1 = s_open("./heredoc_tmp", O_CREAT | O_RDWR, S_IRWXU, data);
		char	*ret;
		ret = get_next_line(0);
		// backslash n to compare
		while (ret && ft_strncmp(ret, data->cmds[2][0], ft_strlen(data->cmds[2][0])))
		{
			write(data->fd1, ret, ft_strlen(ret));
			write(2, ret, ft_strlen(ret));
			free(ret);
			ret = get_next_line(0);
		}
		free(ret);
		s_close(data->fd1, data);
		data->fd1 = s_open("./heredoc_tmp", O_RDONLY, 0, data);
		s_dup2(data->fd1, 0, data);
		s_close(data->fd1, data);
		i++;
	}
	s_close(data->pipefd[i][0], data);
	s_dup2(data->pipefd[i][1], 1, data);
	s_close(data->pipefd[i][1], data);
	s_execve(data->cmds[i + 2][0], data->cmds[i + 2], data->env, data);
}

static void	treat_last(int i, t_data *data)
{
	data->fd2 = s_open(data->cmds[i + 3][0], O_CREAT | O_RDWR, S_IRWXU, data);
	s_dup2(data->fd2, 1, data);
	s_close(data->fd2, data);
	exit(execve(data->cmds[i + 2][0], data->cmds[i + 2], NULL));
}

void	make_fork(t_data *data)
{
	int	i;
	int	return_value;

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
			s_wait(&return_value, data);
			i++;
		}
	}
	treat_last(i, data);
}
