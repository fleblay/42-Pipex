/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 10:14:19 by fle-blay          #+#    #+#             */
/*   Updated: 2022/01/31 10:51:23 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

void	s_dup2(int oldfd, int newfd, t_data *data)
{
	if (dup2(oldfd, newfd) == -1)
		custom_exit(data, 2, "dup2 fail");
}

void	s_close(int fd, t_data *data)
{
	if (close(fd) == -1)
		custom_exit(data, 2, "close fail");
}

int	s_open(const char *pathname, int flags, mode_t mode, t_data *data)
{
	int	fd;

	fd = open(pathname, flags, mode);
	if (fd == -1)
		custom_exit(data, 2, "open fail");
	return (fd);
}

void	s_execve(const char *path, char *const argv[], char *const envp[],
		t_data *data)
{
	if (execve(path, argv, envp) == -1)
		custom_exit(data, 2, "execve fail");
}

pid_t	s_fork(t_data *data)
{
	pid_t child;

	child = fork();
	if (child == -1)
		custom_exit(data, 2, "fork fail");
	return (child);
}
