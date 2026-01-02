/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2026/01/02 21:35:42 by ssharmaz         ###   ########.fr       */
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

struct s_client	g_client;

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
		g_client.sig1 = 1;
		g_client.sig2 = 0;
	}
	else
	{
		g_client.sig1 = 0;
		g_client.sig2 = 1;
	}
	pos++;
	if (pos == 8)
	{
		write(STDOUT, &byte, 1);
		pos = 0;
	}
	g_client.pid = info->si_pid;
}

void	setup_signals(struct sigaction *sa)
{
	sa->sa_sigaction = handler;
	sa->sa_flags = SA_SIGINFO;
	sigemptyset(&(sa->sa_mask));
	sigaddset(&(sa->sa_mask), SIGUSR1);
	sigaddset(&(sa->sa_mask), SIGUSR2);
	if (sigaction(SIGUSR1, sa, NULL) == -1)
	{
		ft_fprintf(STDERR, "sigaction error\n");
		exit(1);
	}
	if (sigaction(SIGUSR2, sa, NULL) == -1)
	{
		ft_fprintf(STDERR, "sigaction error\n");
		exit(1);
	}
}

static void	errexit(char *s)
{
	ft_fprintf(STDERR, "%s\n", s);
	exit(1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_putnbr_fd((int)getpid(), STDOUT);
	write(STDOUT, "\n", 1);
	ft_memset(&sa, 0, sizeof(sa));
	ft_memset(&g_client, 0, sizeof(g_client));
	setup_signals(&sa);
	while (1)
	{
		pause();
		if (g_client.pid)
		{
			if (g_client.sig1 && kill(g_client.pid, SIGUSR1) == -1)
				errexit("kill error");
			else if (g_client.sig2 && kill(g_client.pid, SIGUSR2) == -1)
				errexit("kill error");
			g_client.pid = 0;
		}
	}
}
