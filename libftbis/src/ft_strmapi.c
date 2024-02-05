/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:29:05 by grebrune          #+#    #+#             */
/*   Updated: 2023/11/14 17:22:13 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char				*dst;
	unsigned int		i;
	unsigned int		size;

	if (!s)
		return (NULL);
	i = 0;
	size = 0;
	while (s[size])
		size++;
	dst = malloc(sizeof(char) * size + 1);
	if (dst == NULL)
		return (NULL);
	while (i < size)
	{
		dst[i] = (*f)(i, s[i]);
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
