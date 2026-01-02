/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2026/01/02 21:53:33 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf/libftprintf.h"
#include "../inc/ft_header.h"
#include "../libft/libft.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t	g_ack;

void	send_bit(int pid, unsigned char bit)
{
	int	sig;

	if (bit == 1)
		sig = SIGUSR1;
	else
		sig = SIGUSR2;
	g_ack = 0;
	if (kill(pid, sig) == -1)
	{
		ft_fprintf(STDERR, "kill returned error\n");
		exit(1);
	}
}

void	send_byte(int pid, unsigned char c)
{
	int	bit_pos;

	bit_pos = 0;
	while (bit_pos < 8)
	{
		send_bit(pid, get_bit(bit_pos++, c));
		while (g_ack == 0)
			sleep(1);
	}
}

void	send_message(int pid, char *message)
{
	while (*message != 0)
		send_byte(pid, *message++);
}

void	confirm(int sig)
{
	if (sig == SIGUSR1)
		write(1, "1", 1);
	else
		write(1, "0", 1);
	g_ack = 1;
}

int	main(int argc, char **av)
{
	int	pid;

	if (argc != 3)
		return (ft_fprintf(STDERR, "Usage: %s <PID> <message>\n", av[0]), 1);
	pid = ft_atoi(av[1]);
	if (pid < 1)
		return (ft_fprintf(STDERR,
				"<PID> should be a positive integer number\n"), 1);
	if ((signal(SIGUSR1, confirm) == SIG_ERR) || signal(SIGUSR2,
			confirm) == SIG_ERR)
		return (ft_fprintf(STDERR, "signal error\n"), 1);
	send_message(pid, av[2]);
	return (0);
}
