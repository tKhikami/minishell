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

void	close_heredoc(t_node *root)
{
	int	i;

	i = 0;
	if (root == NULL)
		return ;
	if (root->heredoc == NULL)
		return ;
	while (root->heredoc[i] != -42)
	{
		close(root->heredoc[i]);
		i++;
	}
}

void	ft_free_tree(t_node *root)
{
	t_node	*left;
	t_node	*right;

	if (root != NULL)
	{
		left = root->left;
		right = root->right;
		close_heredoc(root);
		free(root->heredoc);
		free(root);
		ft_free_tree(left);
		ft_free_tree(right);
	}
}
