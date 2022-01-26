/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:42:27 by fle-blay          #+#    #+#             */
/*   Updated: 2022/01/26 10:10:38 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>

typedef struct s_data {
	char	**path;
	char	***cmd;
	int		**pipefd;
	pid_t	*child;
	int		error;
}			t_data;

#endif
