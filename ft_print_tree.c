/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_print_tree.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: nyrandri <nyrandri@student.42antanana		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/09/23 12:54:51 by nyrandri		   #+#	  #+#			  */
/*	 Updated: 2024/09/23 12:54:51 by nyrandri		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_node(t_node *node)
{
	static int  i;

    i++;
    ft_printf("######## %d #######\n", i);
    ft_printf("str  : %s\n", node->str);
	ft_printf("left	: %p\n", node->left);
	ft_printf("right	: %p\n\n", node->right);
}

void	ft_print_tree(t_node *root)
{
	ft_nodeiter((t_node *)root, &ft_print_node);
}
