/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_free_tree.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: nyrandri <nyrandri@student.42antanana		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/09/27 09:48:43 by nyrandri		   #+#	  #+#			  */
/*	 Updated: 2024/09/27 09:48:43 by nyrandri		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tree(t_node *root)
{
	t_node	*left;
	t_node	*right;

	if (root != NULL)
	{
		left = root->left;
		right = root->right;
		free(root);
		ft_free_tree(left);
		ft_free_tree(right);
	}	
}
