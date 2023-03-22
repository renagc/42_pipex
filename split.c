/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-c <rgomes-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 08:33:57 by rgomes-c          #+#    #+#             */
/*   Updated: 2023/03/21 13:30:18 by rgomes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static void	*ft_calloc(size_t count, size_t size)
{
	void	*s;
	size_t	i;

	i = 0;
	s = malloc(count * size);
	if (!s)
		return (0);
	while (i < (count * size))
	{
		((char *)s)[i] = 0;
		i++;
	}
	return (s);
}

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sp;

	if (!s)
		return (0);
	if (start > ft_strlen(s))
		return (ft_calloc(1, 1));
	if ((start + len) > ft_strlen(s))
		len = ft_strlen(s) - start;
	sp = malloc((len + 1) * sizeof(char));
	if (!sp)
		return (NULL);
	i = 0;
	while (s[start] != '\0' && i < len && start < ft_strlen(s))
	{
		sp[i] = s[start];
		i++;
		start++;
	}
	sp[i] = '\0';
	return (sp);
}

//split
static int	ft_count_words(char const *s, char c)
{
	int		i;
	int		count;

	if (!s)
		return (0);
	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] && (s[i] != c))
			i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		i;
	int		count;
	int		j;

	split = (char **)malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!split || !s)
		return (0);
	j = 0;
	i = 0;
	while (s[i] != '\0' && ft_count_words(s, c) != 0)
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		count = i;
		while (s[i] != '\0' && s[i] != c)
			i++;
		if (i > count)
			split[j] = ft_substr(s, count, i - count);
		j++;
	}
	split[j] = NULL;
	return (split);
}
