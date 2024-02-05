/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:42:32 by grebrune          #+#    #+#             */
/*   Updated: 2023/12/14 21:36:03 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_ctofindinstr(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
		{
			if (i == 0)
				return (i + 1);
			return (i + 1);
		}
		i++;
	}
	return (0);
}

char	*read_line(int fd, char *line, char **next_line)
{
	char	buff[BUFFER_SIZE + 1];
	ssize_t	i;

	i = 1;
	while (i > 0)
	{
		if (ft_ctofindinstr(line, '\n'))
			return (*next_line = ft_strnext_line(line), ft_strcut(line));
		i = read(fd, buff, BUFFER_SIZE);
		if (i <= 0 && (!line))
			return (NULL);
		if (line && i == 0)
			return (*next_line = NULL, ft_lastline(line));
		buff[i] = '\0';
		line = ft_freenjoin(line, buff);
		if (!line)
			return (NULL);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*next_line = NULL;

	line = next_line;
	if (read(fd, NULL, 0) < 0)
		return (free(line), next_line = NULL);
	return (read_line(fd, line, &next_line));
}
