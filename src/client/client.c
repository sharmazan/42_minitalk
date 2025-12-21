/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2025/12/21 17:56:55 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf/libftprintf.h"
#include "../inc/ft_header.h"
#include "../libft/libft.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	send_message(int pid, char *message)
{
	int	sig;

	ft_fprintf(STDOUT, "Message: %s\n", message);
	while (*message != 0)
	{
		if (*message == '1')
			sig = SIGUSR1;
		else
			sig = SIGUSR2;
		// sig = ((char)*message == '1') ? SIGUSR1 : SIGUSR2;
		if (kill(pid, sig) == -1)
		{
			perror("kill");
			exit(1);
		}
		message += 1;
		usleep(1);
	}
}

int	main(int argc, char **av)
{
	pid_t	pid;

	// int		which;
	if (argc != 3)
	{
		ft_fprintf(STDERR, "Usage: %s <PID> <message>\n", av[0]);
		return (1);
	}
	pid = (pid_t)ft_atoi(av[1]);
	send_message(pid, av[2]);
	return (0);
}
