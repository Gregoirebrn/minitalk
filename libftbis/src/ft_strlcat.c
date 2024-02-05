/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 22:21:22 by grebrune          #+#    #+#             */
/*   Updated: 2023/11/14 17:22:03 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	x;
	size_t	lensrc;
	size_t	lendst;

	x = 0;
	i = 0;
	lendst = 0;
	lensrc = 0;
	lensrc = ft_strlen(src);
	if (size == 0)
		return (lensrc);
	lendst = ft_strlen(dst);
	if (size < lendst)
		return (size + lensrc);
	i = lendst;
	while (src[x] && i < size - 1)
	{
		dst[i] = src[x];
		i++;
		x++;
	}
	dst[i] = '\0';
	return (lendst + lensrc);
}
