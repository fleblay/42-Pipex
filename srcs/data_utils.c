/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 15:31:10 by fle-blay          #+#    #+#             */
/*   Updated: 2022/02/01 12:24:07 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

//	print_cmds(data);
//	print_types(data);

void	init_data(t_data *data)
{
	data->cmds_type = (int *)malloc((data->ac) * sizeof(int));
	if (!data->cmds_type)
		custom_exit(data, 1, "malloc fail");
	set_types(data);
	get_cmds(data);
	if (data->av[1])
		data->hd = !ft_strcmp(data->av[1], "here_doc");
	get_path(data);
//	get_status(data);
	data->pipefd = (int **)malloc((data->ac - 4) * sizeof(int *));
	if (!data->pipefd)
		custom_exit(data, 1, "malloc fail");
	create_pipes(data);
	data->child = (pid_t *)malloc((data->ac - 4) * sizeof(pid_t));
	if (!data->child)
		custom_exit(data, 1, "malloc fail");
//	print_cmds(data);
//	print_types(data);
}

void	custom_exit_cmd(t_data *data, int error, char *error_sentence, char *cmd)
{
	if (error)
	{
		ft_putstr_fd(error_sentence, 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\n", 2);
	}
	free(data->cmds_type);
	free_cmds(data);
	free_path(data);
	free_pipes(data);
	free(data->child);
	if (error)
		exit(1);
	else
		exit(0);
}

void	custom_exit(t_data *data, int error, char *error_type)
{
	if (error)
	{
		ft_putstr_fd("pipex : ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		//enlever les 2 lignes suivantes pour comportement idem a zsh
		if (error_type)
			ft_putstr_fd(error_type, 2);
		ft_putstr_fd("\n", 2);
	}
	free(data->cmds_type);
	free_cmds(data);
	free_path(data);
	free_pipes(data);
	free(data->child);
	if (error)
		exit(1);
	else
		exit(0);
}
