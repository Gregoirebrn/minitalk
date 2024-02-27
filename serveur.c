/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 02:14:04 by grebrune          #+#    #+#             */
/*   Updated: 2024/02/27 16:53:11 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

static size_t	ft_getlen(const unsigned char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

static unsigned char	*ft_realloc(unsigned char c, unsigned char *str)
{
	size_t			i;
	unsigned char	*new;

	i = ft_getlen(str);
	new = ft_calloc(sizeof (unsigned char), (i + 2));
	i = 0;
	while (str && str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = c;
	if (str)
		free(str);
	return (new);
}

void	signal_handler(int sig, siginfo_t *info, void *ucontext)
{
	static pid_t			pid_cli = 0;
	static unsigned char	received_c = 0;
	static unsigned char	*str = NULL;
	static int				byte_count = 0;

	(void)ucontext;
	if (sig == SIGINT)
	{
		ft_putstr_fd("\nServer closed.\n", 1);
		exit (0);
	}
	if (pid_cli == 0)
		pid_cli = info->si_pid;
	if (sig == SIGUSR2)
		received_c <<= 1;
	else if (sig == SIGUSR1)
	{
		received_c <<= 1;
		received_c |= 1;
	}
	byte_count++;
	if (byte_count == 8)
	{
		if (!received_c)
		{
			kill(pid_cli, SIGUSR2);
			ft_putstr_fd((char *)str, 1);
			ft_putstr_fd("\n", 1);
			str = NULL;
			byte_count = 0;
			pid_cli = 0;
			return ;
		}
		str = ft_realloc(received_c, str);
		received_c = 0;
		byte_count = 0;
	}
	kill(pid_cli, SIGUSR1);
}

int	main(void)
{
	struct sigaction	s_sig;

	ft_putstr_fd("PID : ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
	s_sig.sa_sigaction = signal_handler;
	s_sig.sa_flags = SA_SIGINFO;
	sigemptyset(&s_sig.sa_mask);
	sigaddset(&s_sig.sa_mask, SIGINT);
	sigaction(SIGUSR1, &s_sig, 0);
	sigaction(SIGUSR2, &s_sig, 0);
	sigaction(SIGINT, &s_sig, 0);
	while (1)
		pause();
	return (0);
}
