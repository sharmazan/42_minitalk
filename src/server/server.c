/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2025/12/23 16:22:25 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf/libftprintf.h"
#include "../inc/ft_header.h"
#include "../libft/libft.h"

#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// int		g_pos;
struct
{
	int		signal_received;
	int		signal1_received;
	int		signal2_received;
	pid_t	pid;
}			g_client;

// static void	on_signal(int sig)
// {
// 	const char	*msg = NULL;
// 	if (sig == SIGUSR1)
// 		bit = 1;
// 	else if (sig == SIGUSR2)
// 		bit = 0;
// 	(void)write(STDOUT, msg, 2);
// }

// static void	on_signal(int sig)
// {
// 	static char	byte;

// 	if (g_pos == 0)
// 		byte = 0;
// 	if (sig == SIGUSR1)
// 		byte = byte | 1 << g_pos;
// 	g_pos++;
// 	if (g_pos == 8)
// 	{
// 		write(STDOUT, &byte, 1);
// 		g_pos = 0;
// 		byte = 0;
// 	}
// }

void	handler(int sig, siginfo_t *info, void *ucontext)
{
	static char	byte;
	static int	pos = 0;

	(void)ucontext;
	if (pos == 0)
		byte = 0;
	if (sig == SIGUSR1)
	{
		byte = byte | 1 << pos;
		g_client.signal1_received = 1;
	}
	else
		g_client.signal1_received = 0;
	pos++;
	if (pos == 8)
	{
		write(STDOUT, &byte, 1);
		pos = 0;
		byte = 0;
	}
	g_client.pid = info->si_pid;
	ft_putnbr_fd(g_client.pid, STDOUT);
}

int	send_ack(void)
{
	return (0);
}

int	main(void)
{
	struct sigaction	sa;

	ft_putnbr_fd((int)getpid(), STDOUT);
	write(STDOUT, "\n", 1);
	ft_memset(&sa, 0, sizeof(sa));
	ft_memset(&g_client, 0, sizeof(g_client));
	// sa.sa_handler = on_signal;
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if ((sigaction(SIGUSR1, &sa, NULL) == -1) || (sigaction(SIGUSR2, &sa,
				NULL) == -1))
		return (ft_fprintf(STDERR, "sigaction error\n"), 1);
	while (1)
	{
		pause();
		ft_putnbr_fd(kill(SIGUSR1, g_client.pid), STDOUT);
		if (g_client.signal1_received)
		{
			if (kill(SIGUSR1, g_client.pid) == -1)
				return (ft_fprintf(STDERR, "kill error\n"), 1);
		}
		else // if (g_client.signal2_received)
			if (kill(SIGUSR2, g_client.pid) == -1)
			return (ft_fprintf(STDERR, "kill error\n"), 1);
	}
}
