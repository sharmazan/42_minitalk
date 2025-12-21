/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2025/12/21 17:19:31 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf/libftprintf.h"
#include "../inc/ft_header.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	main(int argc, char **av)
{
	pid_t	pid;
	char	*message;
	int		sig;

	// int		which;
	if (argc != 3)
	{
		ft_fprintf(STDERR, "Usage: %s <PID> <message>\n", av[0]);
		return (1);
	}
	pid = (pid_t)atoi(av[1]);
	message = av[2];
	ft_fprintf(STDOUT, "Message: %s\n", message);
	while (*message != 0)
	{
		// which = atoi(av[2]);
		if (*message == '1')
			sig = SIGUSR1;
		else
			sig = SIGUSR2;
		// sig = ((char)*message == '1') ? SIGUSR1 : SIGUSR2;
		if (kill(pid, sig) == -1)
		{
			perror("kill");
			return (1);
		}
		message += 1;
		usleep(1);
	}
	return (0);
}
