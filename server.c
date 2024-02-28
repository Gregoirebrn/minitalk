/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 02:14:04 by grebrune          #+#    #+#             */
/*   Updated: 2024/02/28 17:12:41 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static unsigned char	*ft_realloc(unsigned char c, unsigned char *str)
{
	size_t			i;
	unsigned char	*new;

	i = ft_strlen((char *)str);
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

static unsigned char	*do_bit(int sig, siginfo_t *info, unsigned char *str)
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
			kill(info->si_pid, SIGUSR2);
			b = 0;
			c = 0;
			return (free(str), NULL);
		}
		str = ft_realloc(c, str);
		c = 0;
		b = 0;
	}
	usleep(SLEEP_T);
	kill(info->si_pid, SIGUSR1);
	return (str);
}

static void	signal_handler(int sig, siginfo_t *info, void *ucontext)
{
	static unsigned char	*str = NULL;

	(void)ucontext;
	str = do_bit(sig, info, str);
}

int	main(void)
{
	struct sigaction	s_sig;

	ft_putstr_fd("PID : ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
	s_sig.sa_sigaction = signal_handler;
	s_sig.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sig, NULL);
	sigaction(SIGUSR2, &s_sig, NULL);
	while (1)
		pause();
}
