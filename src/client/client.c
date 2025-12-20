/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2025/12/20 18:15:42 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf/libftprintf.h"
#include <unistd.h>

// int	main(int ac, char **av)
// {
// 	if (ac != 3)
// 	{
// 		ft_printf("Usage:\n%s <SERVER_PID> <MESSAGE>!!!\n", av[0]);
// 		return (0);
// 	}
// 	ft_printf("My PID is %d\n", getpid());
// }

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	pid_t	pid;
	char	*message;
	int		sig;

	// int		which;
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <PID> <1|2>\n", argv[0]);
		return (1);
	}
	pid = (pid_t)atoi(argv[1]);
	message = argv[2];
	fprintf(stderr, "Message: %s\n", message);
	while (*message != 0)
	{
		fprintf(stderr, "%c\n", *message);
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
		sleep(1);
	}
	return (0);
}
