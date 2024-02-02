/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:19:18 by grebrune          #+#    #+#             */
/*   Updated: 2023/11/14 17:26:27 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		j;
	char		*new;

	if (!s)
		return (NULL);
	i = 0;
	while ((unsigned char)s[i] && i != start)
		i++;
	if (len > ft_strlen(s) - i)
		len = ft_strlen(s) - i;
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	j = 0;
	while (j < len)
	{
		new[j] = s[i];
		i++;
		j++;
	}
	new[j] = '\0';
	return (new);
}
