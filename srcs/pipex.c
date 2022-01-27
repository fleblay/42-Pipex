/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:43:11 by fle-blay          #+#    #+#             */
/*   Updated: 2022/01/27 15:49:28 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

int	main(int ac, char *av[], char *env[])
{
	t_data	data;

	data = (t_data){.ac = ac, .av = av, .env = env};
	if (ac < 5)
		return (0);
	init_data(&data);





	custom_exit(&data);
	return (0);
}
