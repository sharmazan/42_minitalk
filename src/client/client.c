/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2025/12/23 16:21:11 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf/libftprintf.h"
#include "../inc/ft_header.h"
#include "../libft/libft.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	send_bit(int pid, unsigned char bit)
{
	int		sig;
	char	c;

	write(STDOUT, "enter\n", 6);
	c = bit + '0';
	if (bit == 1)
		sig = SIGUSR1;
	else
		sig = SIGUSR2;
	if (kill(pid, sig) == -1)
	{
		ft_fprintf(STDERR, "kill returned error\n");
		exit(1);
	}
	usleep(300);
	write(STDOUT, "exit\n", 5);
}

char	get_bit(int pos, unsigned char c)
{
	if (((1 << pos) & c) == 0)
		return (0);
	return (1);
}

void	send_byte(int pid, unsigned char c)
{
	int	bit_pos;

	bit_pos = 0;
	while (bit_pos < 8)
		send_bit(pid, get_bit(bit_pos++, c));
}

void	send_message(int pid, char *message)
{
	while (*message != 0)
		send_byte(pid, *message++);
}

void	confirm(int sig)
{
	if (sig == SIGUSR1)
		write(1, "Received bit\n", 13);
}

int	main(int argc, char **av)
{
	pid_t				pid;
	struct sigaction	sa;

	if (argc != 3)
	{
		ft_fprintf(STDERR, "Usage: %s <PID> <message>\n", av[0]);
		return (1);
	}
	pid = (pid_t)ft_atoi(av[1]);
	if (pid < 1)
	{
		ft_fprintf(STDERR, "<PID> should be a positive integer number\n");
		return (1);
	}
	// signal(SIGUSR1, confirm);
	sa.sa_handler = confirm;
	// sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if ((sigaction(SIGUSR1, &sa, NULL) == -1) || (sigaction(SIGUSR2, &sa,
				NULL) == -1))
		return (ft_fprintf(STDERR, "sigaction error\n"), 1);
	send_message(pid, av[2]);
	return (0);
}
