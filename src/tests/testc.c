/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2026/01/02 20:50:21 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t	g_ack = 0;

void	signal_handler(int signal)
{
	write(1, "Ack\n", 4);
	g_ack = 1;
}

int	main(int ac, char **av)
{
	int	server_pid;

	printf("PID: %d\n", getpid());
	if (ac != 2)
		exit(1);
	signal(SIGUSR1, signal_handler);
	server_pid = atoi(av[1]);
	for (int i = 0; i < 10; i++)
	{
		g_ack = 0;
		kill(server_pid, SIGUSR1);
		printf("%d SIG1 sent\n", i);
		while (g_ack == 0)
			usleep(10);
	}
	return (0);
}

*/
