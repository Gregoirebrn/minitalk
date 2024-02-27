/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 02:11:04 by grebrune          #+#    #+#             */
/*   Updated: 2024/02/07 15:45:35 by grebrune         ###   ########.fr       */
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
		ft_putstr_fd("Finish Sending ", 1);
		ft_putnbr_fd(rec_bit, 1);
		ft_putstr_fd(" bits.\n", 1);
		exit (0);
	}
}

static	void	send_str(pid_t pid, char *str)
{
	int		i;
	int		x;
	unsigned char	c;

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
			pause();
		}
		x++;
	}
	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR2);
		pause();
	}
}

int	main(int ac, char **av)
{
	pid_t			pid;

	if (ac < 3 || !av[2])
		return (2);
	ft_putstr_fd("Sended at ", 1);
	ft_putnbr_fd(atoi(av[1]), 1);
	ft_putstr_fd("\n", 1);
	pid = atoi(av[1]);
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	send_str(pid, av[2]);
	while (1)
		pause ();
	return (0);
}
