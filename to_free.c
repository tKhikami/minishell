/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrandri <nyrandri@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:19:08 by nyrandri          #+#    #+#             */
/*   Updated: 2024/12/30 12:28:16 by nyrandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_free	*creat_tfree(void *ptr, int type)
{
	t_free	*new;

	new = malloc(sizeof(t_free));
	if (new == NULL)
		return (NULL);
	new->ptr = ptr;
	new->type = type;
	return (new);
}

void	delone_tfree(t_free *tfree, void (*del)(void *))
{
	if (tfree == NULL)
		return ;
	(*del)(tfree->ptr);
	free(tfree);
}

void	add_tfree(t_list **lst, void *ptr, int type)
{
	t_free	*new;

	new = creat_tfree(ptr, type);
	if (new == NULL)
		return ;
	ft_lstadd_back(lst, ft_lstnew(new));
}

void	oper_type_tfree(void *tfree)
{
	t_free	*ptr;

	if (tfree == NULL)
		return ;
	ptr = (t_free *)tfree;
	if (ptr->type == 1)
		delone_tfree(ptr, &adapt_lstclear);
	else if (ptr->type == 2)
		delone_tfree(ptr, &adapt_tabfree);
	else if (ptr->type == 3)
		delone_tfree(ptr, &adapt_free_token);
}

void    adapt_free_token(void *tok)
{
	free_token((t_token *)tok);
}

void	adapt_tabfree(void *tab)
{
	ft_tabfree((char **)tab);
}

void	adapt_lstclear(void *lst)
{
	t_list	*tmp;

	tmp = (t_list *)lst;
	ft_lstclear(&tmp, free);
}

void	handler_tfree(t_list **lstroot, void *ptr, int type)
{
	static t_list	**lst;

	if (lstroot != NULL)
		lst = lstroot;
	else if (lstroot == NULL && ptr != NULL)
		add_tfree(lst, ptr, type);
	else if (lstroot == NULL && ptr == NULL && type == 1)
	{
		ft_lstclear(&((*lst)->next), &oper_type_tfree);
		(*lst)->next = NULL;
	}
	else if (lstroot == NULL && ptr == NULL && type == -1)
	{
		ft_lstclear(lst, &oper_type_tfree);
		*lst = NULL;
	}
}
