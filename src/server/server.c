/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2025/12/22 22:05:46 by ssharmaz         ###   ########.fr       */
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

int			g_pos;

// static void	on_signal(int sig)
// {
// 	const char	*msg = NULL;
// 	if (sig == SIGUSR1)
// 		bit = 1;
// 	else if (sig == SIGUSR2)
// 		bit = 0;
// 	(void)write(STDOUT, msg, 2);
// }

static void	on_signal(int sig)
{
	static char	byte;

	if (g_pos == 0)
		byte = 0;
	if (sig == SIGUSR1)
		byte = byte | 1 << g_pos;
	g_pos++;
	if (g_pos == 8)
	{
		write(STDOUT, &byte, 1);
		g_pos = 0;
		byte = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	printf("%ld\n", (long)getpid());
	g_pos = 0;
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = on_signal;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	// sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_fprintf(STDERR, "sigaction SIGUSR1");
		return (1);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_fprintf(STDERR, "sigaction SIGUSR2");
		return (1);
	}
	while (1)
	{
		pause();
	}
}
