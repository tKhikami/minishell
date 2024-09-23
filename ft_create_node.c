/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_create_node.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: nyrandri <nyrandri@student.42antanana		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/09/23 13:23:41 by nyrandri		   #+#	  #+#			  */
/*	 Updated: 2024/09/23 13:25:03 by nyrandri		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

t_node	*ft_create_node(void *element)
{
	t_node	*ret;

	ret = malloc(sizeof(t_node));
	ret->element = element;
	ret->left = NULL;
	ret->right = NULL;
	return (ret);
}
