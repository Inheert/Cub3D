/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <jodiaz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:45:50 by jodiaz-a          #+#    #+#             */
/*   Updated: 2024/05/03 12:02:52 by jodiaz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	q_mots(const char *s1, char c)
{
	int	num_mots;

	num_mots = 0;
	while (s1 && *s1 != '\0' && c)
	{
		if (*s1 == c)
			s1++;
		else
		{
			num_mots++;
			while (*s1 != '\0' && *s1 != c)
				s1++;
		}
	}
	return (num_mots);
}

char	*q_lettre(const char *s1, char c)
{
	const char	*start;
	char		*mot;
	int			len;

	start = s1;
	while (*s1 && *s1 != c)
		s1++;
	len = s1 - start;
	mot = (char *)malloc(len + 1);
	if (!mot)
		return (NULL);
	while (start != s1)
	{
		*mot = *start;
		start++;
		mot++;
	}
	*mot = '\0';
	return (mot - len);
}

void	free_tout(int i, char **split)
{
	int	f;

	f = 0;
	while (f < i)
	{
		free(split[f]);
		f++;
	}
	free(split);
}

int	less25(char const *s, char c, int i, char **split)
{
	while (*s != '\0')
	{
		while (*s != '\0' && *s == c)
			s++;
		while (*s != '\0' && *s != c)
		{
			split[i] = q_lettre(s, c);
			if (!split[i])
			{
				free_tout(i, split);
				return (0);
			}
			i++;
			while (*s && *s != c)
				s++;
		}
		while (*s != '\0' && *s != c)
			s++;
	}
	split[i] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		num_mots;
	char	**split;
	int		i;

	num_mots = q_mots(s, c);
	if (!s || num_mots < 0 || !num_mots || !c)
		return (NULL);
	split = (char **)malloc(sizeof(char *) * (num_mots + 1));
	if (!split)
		return (NULL);
	i = 0;
	if (less25(s, c, i, split) == 0)
		return (NULL);
	return (split);
}
