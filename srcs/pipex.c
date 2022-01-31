/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:43:11 by fle-blay          #+#    #+#             */
/*   Updated: 2022/01/31 16:53:51 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include <stddef.h>

int	main(int ac, char *av[], char *env[])
{
	t_data	data;

	data = (t_data){.ac = ac, .av = av, .env = env};
	if (ac < 5 || (!ft_strcmp(av[1], "here_doc") && ac < 6))
		return (0);
	init_data(&data);
	make_fork(&data);
	custom_exit(&data, 0, NULL);
	return (0);
}
