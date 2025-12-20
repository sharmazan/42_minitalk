/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2025/12/20 17:39:48 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf/libftprintf.h"
#include <unistd.h>

// int	main(void)
// {
// 	ft_printf("%d\n", getpid());
// }

#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static void	on_signal(int sig)
{
	const char	*msg = NULL;

	if (sig == SIGUSR1)
		msg = "Caught SIGUSR1\n";
	else if (sig == SIGUSR2)
		msg = "Caught SIGUSR2\n";
	else
		msg = "Caught other signal\n";
	// async-signal-safe output:
	(void)write(STDOUT_FILENO, msg, strlen(msg));
}

int	main(void)
{
	struct sigaction	sa;

	printf("PID: %ld\n", (long)getpid());
	fflush(stdout);
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = on_signal;
	// Optional: restart some interrupted syscalls automatically
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask); // signals blocked while handler runs
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		perror("sigaction SIGUSR1");
		return (1);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		perror("sigaction SIGUSR2");
		return (1);
	}
	// Wait for signals forever
	for (;;)
		pause();
}
