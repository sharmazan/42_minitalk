/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2026/01/02 20:50:36 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
// #define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

volatile sig_atomic_t	g_client_pid = 0;

void	signal_handler(int signal)
{
	write(1, "Signal\n", 7);
}

void	handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	write(1, "Signal\n", 7);
	printf("%d\n", info->si_pid);
	g_client_pid = info->si_pid;
}

int	main(void)
{
	struct sigaction	sa;

	printf("%d\n", getpid());
	memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	while (1)
	{
		if (g_client_pid)
		{
			kill(g_client_pid, SIGUSR1);
			printf("ACK sent\n");
			g_client_pid = 0;
		}
		else
			usleep(1);
	}
	return (0);
}
*/
