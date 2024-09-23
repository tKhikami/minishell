/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_nodeiter.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: nyrandri <nyrandri@student.42antanana		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/09/23 12:57:18 by nyrandri		   #+#	  #+#			  */
/*	 Updated: 2024/09/23 12:57:18 by nyrandri		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

void	ft_nodeiter(t_node *node, void (*f)(t_node *))
{
	if (node != NULL && f != NULL)
	{
		f(node);
		ft_nodeiter(node->left, f);
		ft_nodeiter(node->right, f);
	}
}
