/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 11:20:53 by fle-blay          #+#    #+#             */
/*   Updated: 2022/01/18 12:39:18 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int main(int ac, char *av[])
{
	pid_t pid;

	(void)pid;

	if (ac != 2)
		return (0);
	if (!access(av[1], F_OK))
		printf("fichier existant\n");
	else
		perror("Erreur");
	if (!unlink(av[1]))
		printf("fichier removed\n");
	else
		perror("Erreur");

	return (0);
}
