/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 02:14:04 by grebrune          #+#    #+#             */
/*   Updated: 2024/02/12 16:45:27 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static size_t	ft_getlen(unsigned const char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

static unsigned char	*ft_realloc(unsigned char *src_str, unsigned char c)
{
	size_t			i;
	unsigned char	*new_str;

	i = ft_getlen(src_str);
	new_str = malloc(sizeof (char) * (i + 2));
	i = 0;
	while (src_str && src_str[i])
	{
		new_str[i] = src_str[i];
	}
	new_str[i++] = c;
	new_str[i] = '\0';
	if (src_str)
		free(src_str);
	return (new_str);
}

void	signal_handler(int sig, siginfo_t *info, void *ucontext)
{
	static pid_t			pid_cli = 0;
	static unsigned char	received_c = 0;
	static int				byte_count = 0;
	static unsigned char	*str = 0;

	(void)ucontext;
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
			ft_putstr_fd("\n", 1);
			byte_count = 0;
			pid_cli = 0;
			return ;
		}
		str = ft_realloc(str, received_c);
		received_c = 0;
		byte_count = 0;
	}
	kill(pid_cli, SIGUSR1);
	ft_putstr_fd(str, 1);
	free(str);
}

int	main(void)
{
	struct sigaction	s_sig;

	ft_putstr_fd("PID : ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
	s_sig.sa_sigaction = signal_handler;
	s_sig.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sig, 0);
	sigaction(SIGUSR2, &s_sig, 0);
	while (1)
		pause();
	return (0);
}
