/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 separation.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: nyrandri <nyrandri@student.42antanana		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/11/17 14:46:50 by nyrandri		   #+#	  #+#			  */
/*	 Updated: 2024/11/17 16:11:18 by nyrandri		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "header.h"

char	*get_one_argument(char	**str, int c)
{
	int		i;
	char	*ret;

	i = 0;
	if (*str == NULL)
		return (NULL);
	if ((*str)[0] == '\0')
		return (NULL);
	if (c == '\'' || c == '\"')
	{
		i = 1;
		while ((*str)[i] != c && (*str)[i] != '\0')
			i++;
		ret = ft_substr(*str, 0, i + 1);
		if ((*str)[i] == c)
			i += 1;
	}
	else
	{
		while ((*str)[i] != '\'' && (*str)[i] != '\"' && (*str)[i] != '\0')
			i++;
		ret = ft_substr(*str, 0, i);
	}
	*str = *str + i;
	return (ret);
}

char	**divise_argument(char	*str)
{
	char	*ptr;
	char	*tmp;
	t_list	*lst;
	char	**tab;

	if (str == NULL)
		return (NULL);
	ptr = str;
	lst = NULL;
	while (ptr[0] != '\0')
	{
		tmp = get_one_argument(&ptr, ptr[0]);
		if (tmp == NULL)
		{
			ft_lstclear(&lst, free);
			return (NULL);
		}
		ft_lstadd_front(&lst, ft_lstnew(tmp));
	}
	tab = ft_lsttotab(lst);
	invert_tab(&tab);
	ft_lstfree(&lst);
	return (tab);
}

t_list	*divise_all_argument(t_token *tok, t_list *env)
{
	char	**tab;
	t_list	*lst;
	t_list	*tmp;

	if (tok == NULL || env == NULL)
		return (NULL);
	tab = get_argument(tok, env);
	lst = ft_tabtolst(tab);
	free(tab);
	tmp = lst;
	while (tmp != NULL)
	{
		tab = divise_argument((char *)tmp->content);
		free(tmp->content);
		tmp->content = (void *)tab;
		tmp = tmp->next;
	}
	return (lst);
}

char	**ultimate_get_argument(t_token *tok, t_list *env)
{
	char	**buff[2];
	char	**tab;
	t_list	*lst;
	t_list	*tmp;

	if (tok == NULL || env == NULL)
		return (NULL);
	lst = divise_all_argument(tok, env);
	if (!lst)
		return (NULL);
	tmp = lst;
	tab = (char **)tmp->content;
	tmp = tmp->next;
	while (tmp != NULL)
	{
		buff[0] = tab;
		buff[1] = (char **)tmp->content;
		tab = ft_concatenate_tab(buff[0], buff[1]);
		free(buff[0]);
		free(buff[1]);
		tmp = tmp->next;
	}
	tab = ultimate_change_dollar(env, tab);
	ft_lstfree(&lst);
	return (tab);
}

static char	**mini_get_argument(t_token *ptr, char **tab)
{
	char	**buff;
	char	**ret;

	if (tab == NULL)
	{
		tab = ft_split_ignore_quote(ptr->tok, ' ');
		return (tab);
	}
	else
	{
		buff = ft_split_ignore_quote(ptr->tok, ' ');
		ret = ft_concatenate_tab(tab, buff);
		free(tab);
		free(buff);
		return (ret);
	}
}

char	**get_argument(t_token *tok, t_list *env)
{
	t_token	*tmp;
	char	**tab;

	(void)env;
	tab = NULL;
	if (tok == NULL)
		return (NULL);
	tmp = tok;
	while (tmp != NULL)
	{
		if (tmp->type == command)
		{
			tab = mini_get_argument(tmp, tab);
			if (tab == NULL)
				return (NULL);
		}
		tmp = tmp->next;
	}
	return (tab);
}
