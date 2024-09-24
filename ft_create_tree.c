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
	ret->stat = command;
	ret->left = NULL;
	ret->right = NULL;
	return (ret);
}

t_status	ft_define_status(char *flag)
{
	if (ft_memcmp(flag, PIPE, 2) == 0)
		return (is_pipe);
	else if (ft_memcmp(flag, NORMAL_INPUT, 2) == 0)
		return (normal_input);
	else if (ft_memcmp(flag, NORMAL_OUTPUT, 2) == 0)
		return (normal_output);
	else if (ft_memcmp(flag, DELIM_INPUT, 2) == 0)
		return (delim_input);
	else if (ft_memcmp(flag, APPEND_OUTPUT, 2) == 0)
		return (append_output);
	else
		return (undefine);
}		

void	ft_branching(t_node *node, char *flag)
{
	char		*tmp;
	
	if (node != NULL)
	{
		tmp = ft_reverse_strtok(node->str, flag, &ft_is_inner_quote);
		if (tmp == node->str)
			return ;
		node->left = ft_create_node(node->str);
		node->right = ft_create_node(tmp);
		node->stat = ft_define_status(flag);
		node->str = NULL;
	}	
}

t_node	*ft_create_tree(char *str)
{
	t_node	*root;

	root = ft_create_node(str);
	ft_nodeiter(root, &ft_branching, PIPE);
	ft_nodeiter(root, &ft_branching, NORMAL_INPUT);
	ft_nodeiter(root, &ft_branching, NORMAL_OUTPUT);
	ft_nodeiter(root, &ft_branching, DELIM_INPUT);
	ft_nodeiter(root, &ft_branching, APPEND_OUTPUT);
	return (root);
}
