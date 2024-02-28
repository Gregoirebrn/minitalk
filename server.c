/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 02:14:04 by grebrune          #+#    #+#             */
/*   Updated: 2024/02/28 15:31:39 by grebrune         ###   ########.fr       */
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

static unsigned char	*do_bit(int sig, pid_t *pid, unsigned char *str)
{
	static unsigned char	c = 0;
	static int				b = 0;

	c <<= 1;
	if (sig == SIGUSR1)
		c |= 1;
	b += 1;
	if (b == 8)
	{
		if (!c)
		{
			ft_putstr_fd((char *)str, 1);
			ft_putstr_fd("\n", 1);
			kill(*pid, SIGUSR2);
			*pid = 0;
			b = 0;
			free(str);
			return (NULL);
		}
		str = ft_realloc(c, str);
		c = 0;
		b = 0;
	}
	kill(*pid, SIGUSR1);
	return (str);
}

void	signal_handler(int sig, siginfo_t *info, void *ucontext)
{
	static pid_t			pid_cli = 0;
	static unsigned char	*str = NULL;

	(void)ucontext;
	if (pid_cli == 0)
		pid_cli = info->si_pid;
	str = do_bit(sig, &pid_cli, str);
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
	sigaction(SIGUSR1, &s_sig, 0);
	sigaction(SIGUSR2, &s_sig, 0);
	while (1)
		pause();
	return (0);
}
