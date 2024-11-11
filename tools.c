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
	int	ret;

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
	int	len;
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
	int	len;
	int	i;
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
	int	i;
	int	j;

	if (tab1 == NULL || tab2 == NULL)
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
		int		i;

		i = 0;
		while (tab[i] != NULL)
		{
				free(tab[i]);
				i++;
		}
		free(tab);
}
