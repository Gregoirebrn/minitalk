/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 22:00:15 by grebrune          #+#    #+#             */
/*   Updated: 2023/11/14 17:22:24 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	x;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		x = 0;
		while (big[i + x] == little[x] && little[x] != '\0' && i + x < len)
			x++;
		if (little[x] == '\0')
			return ((char *)big + i);
		i++;
	}
	if (big[0] == '\0' && little[0] == '\0')
		return ((char *)big);
	return (NULL);
}
