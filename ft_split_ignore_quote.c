/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ignore_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrandri <nyrandri@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:53:11 by nyrandri          #+#    #+#             */
/*   Updated: 2024/11/11 08:29:53 by nyrandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_lsttotab(t_list *lst)
{
	t_list	*tmp;
	char	**tab;
	int		len;
	int		i;

	i = 0;
	len = ft_lstsize(lst);
	tmp = lst;
	tab = malloc((len + 1) * sizeof(char *));
	if (tab != NULL)
	{
		while (i < len)
		{
			tab[i] = (char *)tmp->content;
			i++;
			tmp = tmp->next;
		}
		tab[i] = NULL;
	}
	return (tab);
}
		
void	ft_lstfree(t_list **lst)
{
	t_list	*tmp;
	t_list	*next;

	tmp = *lst;
	while (tmp != NULL)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	*lst = NULL;
}

char	**ft_split_ignore_quote(char *str, char c)
{
	int		i;
	char	*start;
	char	**tab;
	char	*tmp;
	t_list	*lstroot;

	lstroot = NULL;
	i = 0;
	start = str;
	while (start[0] != '\0')
	{
		while (start[i] != '\0' && (start[i] != c || ft_is_inner_quote(str, &start[i])))
			i++;
		tmp = ft_substr(start, 0, i);
		if (tmp == NULL)
			return (NULL);
		ft_lstadd_back(&lstroot, ft_lstnew(tmp));
		while (start[i] == c)
			i++;
		start = &start[i];
		i = 0;
	}
	tab = ft_lsttotab(lstroot);
	ft_lstfree(&lstroot);
	return (tab);
}
