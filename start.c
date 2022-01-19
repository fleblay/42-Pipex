/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 11:20:53 by fle-blay          #+#    #+#             */
/*   Updated: 2022/01/19 09:29:51 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BUFFER_SIZE 512 

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include "libft.h"
#include <fcntl.h>

int main(int ac, char *av[], char *envp[])
{
	pid_t	pid;
	int		pipefd[2];	

	(void)ac;
	(void)envp;
	/*
	int i;
	i = 0;
	while (envp[i])
	{
		printf("envp[%d] : %s\n", i, envp[i]);
		i++;
	}
	*/
	if (!access(av[1], F_OK))
		printf("fichier existant\n");
	else
		perror("Erreur access");
	/*
	if (!unlink(av[1]))
		printf("fichier removed\n");
	else
		perror("Erreur");
	*/

	(void)pid;
	if (pipe(pipefd) == -1)
		perror("Pipe");

	pid = fork();
	if (pid == -1)
		perror("Erreur fork");
	if (pid == 0)
	{
		printf("enfant\n");
		if (close(pipefd[0]) == -1)
			perror("Erreur close");
		dup2(open("test.txt", O_RDONLY), 0);
		if (dup2(pipefd[1], 1) == -1)
			perror("Erreur dup2");
		if (execve(ft_split(av[1], ' ')[0], ft_split(av[1], ' '), NULL))
			perror("Erreur execve enfant");
		return (0);
	}
	else
	{
		printf("parent\n");
		if (close(pipefd[1]) == -1)
			perror("Erreur close");
		wait(NULL);
		dup2(pipefd[0], 0);
		if (execve(ft_split(av[2], ' ')[0], ft_split(av[2], ' '), NULL))
			perror("Erreur execve parent");
		printf("parent\n");
	}
	/*
	char *argv[3];
	argv[0] = "/bin/ls";
	argv[1] = "-l";
	argv[2] = NULL;
	if (execve(argv[0], argv, envp))
		perror("Erreur execve");
	printf("ici\n");
	*/
	return (0);
}
