/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:42:27 by fle-blay          #+#    #+#             */
/*   Updated: 2022/02/04 11:31:28 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef struct s_data {
	int		ac;
	char	**av;
	char	**env;
	char	**path;
	char	***cmds;
	int		*cmds_type;
	int		**pipefd;
	pid_t	*child;
	int		error;
	int		fd1;
	int		fd2;
	int		hd;
	int		status;
}			t_data;

void	get_cmds(t_data *data);
void	print_cmds(t_data *data);
void	free_cmds(t_data *data);
void	get_path(t_data *data);
void	print_path(t_data *data);
void	free_path(t_data *data);
void	set_types(t_data *data);
void	print_types(t_data *data);
void	get_status(t_data *data);
void	try_cmd(int i, t_data *data);
void	init_data(t_data *data);
void	custom_exit(t_data *data, int error, char *error_type);
void	error_cmd(t_data *data, char *err_stce, char *cmd, int exit_stat);
void	create_pipes(t_data *data);
void	free_pipes(t_data *data);
void	print_pipes(t_data *data);
void	kill_pipes(int start, t_data *data);
void	make_fork(t_data *data, int i);
void	s_dup2(int oldfd, int newfd, t_data *data);
void	s_close(int fd, t_data *data);
int		s_open(const char *pathname, int flags, mode_t mode, t_data *data);
void	s_execve(const char *path, char *const argv[], char *const envp[],
		t_data *data);
pid_t	s_fork(t_data *data);
void	s_wait(int *stat_loc, t_data *data);
void	s_unlink(const char *path, t_data *data);

#endif
