/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:42:27 by fle-blay          #+#    #+#             */
/*   Updated: 2022/01/27 16:41:22 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>

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
}			t_data;

void	get_cmds(t_data *data);
void	print_cmds(t_data *data);
void	free_cmds(t_data *data);
void	get_path(t_data *data);
void	print_path(t_data *data);
void	free_path(t_data *data);
void	set_types(t_data *data);
void	print_types(t_data *data);
int		get_file_status(char *try, t_data *data, int i, int swap);
void	get_status(t_data *data);
void	init_data(t_data *data);
void	custom_exit(t_data *data, int error);
void	create_pipes(t_data *data);
void	free_pipes(t_data *data);
void	make_fork(t_data *data);
#endif
