/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:09:40 by grebrune          #+#    #+#             */
/*   Updated: 2023/11/14 17:22:26 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	if (s[0] == '\0' && c != 0)
		return (NULL);
	while (0 <= i)
	{
		if ((unsigned char)c == ((char *)s)[i])
			return (&((char *)s)[i]);
		i--;
	}
	return (NULL);
}
