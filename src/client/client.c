/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2025/12/21 19:35:11 by ssharmaz         ###   ########.fr       */
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

	c = bit + '0';
	write(1, &c, 1);
	if (bit == 1)
		sig = SIGUSR1;
	else
		sig = SIGUSR2;
	// sig = ((char)*message == '1') ? SIGUSR1 : SIGUSR2;
	if (kill(pid, sig) == -1)
	{
		perror("kill");
		exit(1);
	}
	usleep(1);
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
	ft_fprintf(STDOUT, "Message: %s\n", message);
	while (*message != 0)
	{
		send_byte(pid, *message);
		message += 1;
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
