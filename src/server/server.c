/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2026/01/02 21:48:31 by ssharmaz         ###   ########.fr       */
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

static void	errexit(char *s)
{
	ft_fprintf(STDERR, "%s\n", s);
	exit(1);
}

void	handler(int sig, siginfo_t *info, void *ucontext)
{
	static char	byte;
	static int	pos = 0;

	(void)ucontext;
	if (pos == 0)
		byte = 0;
	if (sig == SIGUSR1)
		byte = byte | 1 << pos;
	pos++;
	if (pos == 8)
	{
		write(STDOUT, &byte, 1);
		pos = 0;
	}
	if (sig == SIGUSR1 && kill(info->si_pid, SIGUSR1) == -1)
		errexit("kill error");
	else if (kill(info->si_pid, SIGUSR2) == -1)
		errexit("kill error");
}

void	setup_signals(struct sigaction *sa)
{
	sa->sa_sigaction = handler;
	sa->sa_flags = SA_SIGINFO;
	sigemptyset(&(sa->sa_mask));
	sigaddset(&(sa->sa_mask), SIGUSR1);
	sigaddset(&(sa->sa_mask), SIGUSR2);
	if (sigaction(SIGUSR1, sa, NULL) == -1)
		errexit("sigaction error");
	if (sigaction(SIGUSR2, sa, NULL) == -1)
		errexit("sigaction error");
}

int	main(void)
{
	struct sigaction	sa;

	ft_fprintf(STDOUT, "%d\n", getpid());
	ft_memset(&sa, 0, sizeof(sa));
	setup_signals(&sa);
	while (1)
		pause();
}
