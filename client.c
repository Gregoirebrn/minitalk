/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 02:11:04 by grebrune          #+#    #+#             */
/*   Updated: 2024/02/05 17:17:01 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static	void	send_str(pid_t pid, char *str)
{
	int		i;
	int		x;
	char	c;

	x = 0;
	while (str && str[x])
	{
		i = 8;
		c = str[x];
		while (i--)
		{
			if (c >> i & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(100);
		}
		x++;
	}
	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR1);
		usleep(100);
	}
}

int	main(int ac, char **av)
{
	pid_t	pid;

	if (ac < 3 || !av[2])
		return (2);
	ft_putstr_fd("Sended at ", 1);
	ft_putnbr_fd(atoi(av[1]), 1);
	ft_putstr_fd("\n", 1);
	pid = atoi(av[1]);
	send_str(pid, av[2]);
	while (1)
		pause();
	return (0);
}
