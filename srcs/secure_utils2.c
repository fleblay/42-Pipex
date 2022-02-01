/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 10:29:56 by fle-blay          #+#    #+#             */
/*   Updated: 2022/02/01 12:03:32 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>
#include <unistd.h>

void	s_wait(int *stat_loc, t_data *data)
{
	if (wait(stat_loc) == -1)
		custom_exit(data, 1, "wait fail");
}

void	s_unlink(const char *path, t_data *data)
{
	if (unlink(path) == -1)
		custom_exit(data, 1, "unlink fail");
}
