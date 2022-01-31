/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 10:29:56 by fle-blay          #+#    #+#             */
/*   Updated: 2022/01/31 10:45:54 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "pipex.h"

void	s_wait(int *stat_loc, t_data *data)
{
	if (wait(stat_loc) == -1)
		custom_exit(data, 2, "wait fail");
}
