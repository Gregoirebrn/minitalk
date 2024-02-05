/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:56:26 by grebrune          #+#    #+#             */
/*   Updated: 2024/01/10 13:41:25 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	ft_strncpy(const char *src, char *dest, int n)
{
	int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

static int	ft_countwds(const char *str, char c)
{
	int	i;
	int	wds;

	wds = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			wds++;
			i++;
			while (str[i] != c && str[i])
				i++;
		}
		else
			i++;
	}
	return (wds);
}

static char	**ft_clean(char **tab, int x)
{
	if (x == 0)
	{
		free(tab);
		return (NULL);
	}
	while (0 < x)
	{
		x--;
		free(tab[x]);
	}
	free(tab);
	return (NULL);
}

static char	**ft_filltab(char const *s, char **tab, char c)
{
	int	i;
	int	size;
	int	x;

	x = 0;
	size = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			size = i;
			while (s[i] != c && s[i])
				i++;
			tab[x] = malloc(sizeof(char) * (i - size + 1));
			if (tab[x] == NULL)
				return (ft_clean(tab, x));
			ft_strncpy(&s[size], tab[x++], i - size);
		}
		else
			i++;
	}
	tab[x] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	int		size;
	char	**tab;

	if (s == NULL)
		return (NULL);
	size = ft_countwds(s, c);
	tab = malloc(sizeof(char *) * (size + 1));
	if (tab == NULL)
		return (NULL);
	if (!ft_filltab(s, tab, c))
		return (NULL);
	return (tab);
}
