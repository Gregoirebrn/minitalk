/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 02:14:04 by grebrune          #+#    #+#             */
/*   Updated: 2024/02/05 17:10:52 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int sig)
{
	static pid_t			pid_cli = 0;
	static unsigned char	received_c = 0;
	static int				byte_count = 0;

	if (pid_cli == 0)
		pid_cli = getpid();
	if (sig == SIGUSR2)
	{
		received_c <<= 1;
		byte_count++;
	}
	else if (sig == SIGUSR1)
	{
		received_c <<= 1;
		received_c |= 1;
		byte_count++;
	}
	if (byte_count == 8)
	{
		ft_putchar_fd(received_c, 1);
		received_c = 0;
		byte_count = 0;
	}
}

int	main(void)
{
	struct sigaction	s_sig;

	ft_putstr_fd("PID : ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
	s_sig.sa_handler = signal_handler;
	sigaction(SIGUSR1, &s_sig, 0);
	sigaction(SIGUSR2, &s_sig, 0);
	while (1)
		pause();
	return (0);
}
