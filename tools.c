/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 tools.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: nyrandri <nyrandri@student.42antanana		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/11/11 07:35:08 by nyrandri		   #+#	  #+#			  */
/*	 Updated: 2024/11/11 08:29:14 by nyrandri		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "header.h"

int	ft_lstprint(t_list *lst, int (*format)(void *))
{
	t_list	*tmp;
	int		ret;

	tmp = lst;
	ret = 0;
	while (tmp != NULL)
	{
		ret += (*format)(tmp->content);
		tmp = tmp->next;
	}
	return (ret);
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	if (tab != NULL)
	{
		while (tab[i] != NULL)
			i++;
	}
	return (i);
}

int	ultimate_tablen(char **tab)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (tab != NULL)
	{
		while (tab[i] != NULL)
		{
			len += ft_strlen(tab[i]);
			i++;
		}
	}
	return (len);
}

t_list	*ft_tabtolst(char **tab)
{
	int		len;
	t_list	*lst;

	if (tab == NULL)
		return (NULL);
	len = ft_tablen(tab) - 1;
	lst = NULL;
	while (len >= 0)
	{
		ft_lstadd_front(&lst, ft_lstnew(tab[len]));
		len--;
	}
	return (lst);
}

void	invert_tab(char ***tab)
{
	int		len;
	int		i;
	char	*tmp;

	i = 0;
	if (*tab == NULL)
		return ;
	len = ft_tablen(*tab);
	while (i < len / 2)
	{
		tmp = (*tab)[i];
		(*tab)[i] = (*tab)[len - i -1];
		(*tab)[len - i -1] = tmp;
		i++;
	}
}

char	**ft_concatenate_tab(char **tab1, char **tab2)
{
	char	**ret;
	int		i;
	int		j;

	if (tab1 == NULL || tab2 == NULL)
		return (NULL);
	if (tab2[0] == NULL)
		return (NULL);
	i = 0;
	j = 0;
	ret = malloc(sizeof(char *) * (ft_tablen(tab1) + ft_tablen(tab2) + 1));
	if (ret == NULL)
		return (NULL);
	while (j < ft_tablen(tab1))
	{
		ret[j] = tab1[j];
		j++;
	}
	while (i < ft_tablen(tab2))
	{
		ret[j + i] = tab2[i];
		i++;
	}
	ret[i + j] = NULL;
	return (ret);
}

void	ft_tabfree(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

void	ft_lstinsert(t_list *lst, t_list *newlst)
{
	t_list	*tmp;
	t_list	*last;

	if (lst == NULL || newlst == NULL)
		return ;
	tmp = lst->next;
	last = ft_lstlast(newlst);
	lst->next = newlst;
	last->next = tmp;
}

int	format_content_char(void *str)
{
	char	*tmp;

	tmp = (char *)str;
	if (tmp != NULL)
	{
		write(1, "\n", 1);
		return (write(1, str, ft_strlen(tmp)));
	}
	return (write(1, "(null)", 6));
}

void	free_token(t_token *tok)
{
	if (tok != NULL)
	{
		free_token(tok->next);
		free(tok);
		tok = NULL;
	}
}

void	free_variable(void *var)
{
	free(((t_variable *)var)->varname);
	free(((t_variable *)var)->value);
	free(var);
	var = NULL;
}
<<<<<<< HEAD
=======

int	print_token(t_token *tok)
{
	t_token	*tmp;
	int		ret;

	tmp = tok;
	ret = 0;
	if (tok == NULL)
		return (printf("NULL"));
	while (tmp != NULL)
	{
		ret += printf("Type :	%d\ntoken : %s\n\
				**************\n", (int)tmp->type, tmp->tok);
		tmp = tmp->next;
	}
	return (ret);
}

int	ft_min(int n, int m)
{
	if (n < m)
		return (n);
	else
		return (m);
}

char	**ft_tabdup(char **tab)
{
	char	**ret;
	int		i;
	int		tab_len;

	if (tab == NULL)
		return (NULL);
	tab_len = ft_tablen(tab);
	i = 0;
	ret = malloc(sizeof(char *) * (tab_len + 1));
	if (ret == NULL)
		return (ret);
	while (i < tab_len)
	{
		ret[i] = ft_strdup(tab[i]);
		ret[i + 1] = NULL;
		if (ret[i] == NULL)
		{
			ft_tabfree(ret);
			return (NULL);
		}
		i++;
	}
	return (ret);
}
>>>>>>> 348bb52 (execution semble marcher. Il faut plus de teste)
