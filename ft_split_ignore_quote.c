/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_split_ignore_quote.c							:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: nyrandri <nyrandri@student.42antanana		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/10/29 09:53:11 by nyrandri		   #+#	  #+#			  */
/*	 Updated: 2024/11/17 14:17:33 by nyrandri		  ###	########.fr		  */
/*																			  */
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

static t_list	*mini_split(t_list *lstroot, char **start, char c)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*start)[i] != '\0' && ((*start)[i] != c || \
				ft_is_inner_quote(*start, &(*start)[i])))
		i++;
	tmp = ft_substr(*start, 0, i);
	if (tmp == NULL)
	{
		ft_lstclear(&lstroot, free);
		return (NULL);
	}
	ft_lstadd_back(&lstroot, ft_lstnew(tmp));
	while ((*start)[i] == c)
		i++;
	*start = &(*start)[i];
	return (lstroot);
}

char	**ft_split_ignore_quote(char *str, char c)
{
	char	*start;
	char	**tab;
	t_list	*lstroot;

	lstroot = NULL;
	start = str;
	if (str == NULL)
		return (NULL);
	while (start[0] != '\0')
	{
		lstroot = mini_split(lstroot, &start, c);
		if (lstroot == NULL)
			return (NULL);
	}
	tab = ft_lsttotab(lstroot);
	ft_lstfree(&lstroot);
	return (tab);
}
