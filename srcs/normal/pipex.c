/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:43:11 by fle-blay          #+#    #+#             */
/*   Updated: 2022/02/04 12:35:16 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include <stddef.h>

int	main(int ac, char *av[], char *env[])
{
	t_data	data;
	int		i;

	i = 0;
	data = (t_data){.ac = ac, .av = av, .env = env};
	if (ac != 5)
		return (1);
	init_data(&data);
	if (data.hd)
	{
		treat_here_doc(&data);
		i++;
	}
	make_fork(&data, i);
	custom_exit(&data, 0, NULL);
	return (0);
}
