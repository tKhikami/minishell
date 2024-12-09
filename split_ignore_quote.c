/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_ignore_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 08:36:07 by atolojan          #+#    #+#             */
/*   Updated: 2024/12/09 10:56:20 by nyrandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**check_malloc(char **tab, int i)
{
	if (!tab[i])
	{
		while (--i >= 0)
			free(tab[i]);
		free(tab);
	}
	return (tab);
}

static void	take_word(char **tab, const char *s, char c)
{
	int		i[2];
	int		count;

	i[0] = 0;
	i[1] = 0;
	while (s[i[0]] != '\0')
	{
		if (s[i[0]] != c)
		{
			count = 0;
			while (s[i[0]] != '\0' && s[i[0]] != c && \
					ft_is_inner_quote((char *)s, (char *)&s[i[0]]))
			{
				count++;
				(i[0])++;
			}
			tab[i[1]] = ft_substr(s, i[0] - count, count);
			check_malloc(tab, i[1]);
			(i[1])++;
		}
		else
			(i[0])++;
	}
	if (tab)
		tab[i[1]] = NULL;
}

char	**split_ignore_quote(char const *s, char c)
{
	char	**tab;
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == '\0' || s[i + 1] == c))
			count++;
		i++;
	}
	tab = malloc(sizeof (char *) * (count + 1));
	if (!tab)
		return (NULL);
	take_word(tab, s, c);
	return (tab);
}
