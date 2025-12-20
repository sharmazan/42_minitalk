/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssharmaz <ssharmaz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 23:17:00 by ssharmaz          #+#    #+#             */
/*   Updated: 2025/12/20 16:59:42 by ssharmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf/libftprintf.h"
#include <unistd.h>

int	main(int ac, char **av)
{
	if (ac != 3)
	{
		ft_printf("Usage:\n%s <SERVER_PID> <MESSAGE>!!!\n", av[0]);
		return (0);
	}
	ft_printf("My PID is %d\n", getpid());
}
