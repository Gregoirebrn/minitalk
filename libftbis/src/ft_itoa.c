/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:49:48 by grebrune          #+#    #+#             */
/*   Updated: 2023/11/09 22:04:15 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ilen(int *n, int *signe, unsigned int *uni)
{
	int				size;
	unsigned int	tmp;

	size = 0;
	if (*n < 0)
		tmp = *n * -1;
	else
		tmp = *n;
	while (tmp != 0)
	{
		tmp = tmp / 10;
		size++;
	}
	if (size == 0)
		size++;
	if (*n < 0)
	{
		*signe = *signe + 1;
		*uni = *n * -1;
		size++;
	}
	else
		*uni = *n;
	return (size);
}

char	*ft_itoa(int n)
{
	int									signe;
	int									size;
	char								*str;
	unsigned int						uni;

	signe = 0;
	uni = 0;
	size = ft_ilen(&n, &signe, &uni);
	str = malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	str[size] = '\0';
	while (0 < size--)
	{
		str[size] = uni % 10 + 48;
		uni = uni / 10;
	}
	if (signe)
		str[0] = '-';
	return (str);
}
