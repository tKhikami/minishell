/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_create_tree.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: nyrandri <nyrandri@student.42antanana		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/09/23 17:58:41 by nyrandri		   #+#	  #+#			  */
/*	 Updated: 2024/09/23 17:58:43 by nyrandri		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

t_node	*ft_create_node(char *str)
{
	t_node	*ret;

	ret = malloc(sizeof(t_node));
	ret->str = str;
	ret->left = NULL;
	ret->right = NULL;
	return (ret);
}

void	ft_branching(t_node *node)
{
	char		*tmp;
	
	if (node != NULL)
	{
		tmp = ft_reverse_strtok(node->str, PIPE, &ft_is_inner_quote);
		if (tmp == node->str)
			return ;
		node->left = ft_create_node(node->str);
		node->right = ft_create_node(tmp);
		node->str = NULL;
	}	
}

t_node	*ft_create_tree(char *str)
{
	t_node	*root;

	root = ft_create_node(str);
	ft_nodeiter(root, &ft_branching);
	return (root);
}
