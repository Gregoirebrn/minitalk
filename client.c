/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 02:11:04 by grebrune          #+#    #+#             */
/*   Updated: 2024/02/28 15:17:49 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	signal_handler(int sig)
{
	static int	rec_bit = 0;

	if (sig == SIGUSR1)
	{
		rec_bit++;
	}
	if (sig == SIGUSR2)
	{
		rec_bit++;
		ft_putstr_fd("Finish Sending ", 1);
		ft_putnbr_fd(rec_bit, 1);
		ft_putstr_fd(" bits.\n", 1);
	}
}

static	void	send_end(pid_t pid)
{
	int	i;

	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR2);
		pause();
	}
}

static	int	send_str(pid_t pid, char *str)
{
	int				i;
	int				x;
	unsigned char	c;

	x = 0;
	while (str && str[x])
	{
		i = 8;
		c = str[x];
		while (i--)
		{
			if (c >> i & 1)
			{
				if (kill(pid, SIGUSR1) < 0)
					return (1);
			}
			else
				if (kill(pid, SIGUSR2) < 0)
					return (1);
			pause();
		}
		x++;
	}
	send_end(pid);
	return (0);
}

int	main(int ac, char **av)
{
	pid_t			pid;

	if (ac < 3 || !av[2])
		return (ft_putstr_fd("Missing PID & message.\n", 1), 2);
	pid = atoi(av[1]);
	if (pid < 1)
		return (ft_putstr_fd("Wrong PID.\n", 1), 2);
	ft_putstr_fd("Sending ...\n", 1);
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	if (1 == send_str(pid, av[2]))
		return (ft_putstr_fd("Wrong PID.\n", 1), 2);
	return (0);
}
