/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_get_argument.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: nyrandri <nyrandri@student.42antanana		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/10/29 12:31:52 by nyrandri		   #+#	  #+#			  */
/*	 Updated: 2024/10/29 12:31:52 by nyrandri		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

char	**get_argument(t_token *tok, t_list *env)
{
	t_token *tmp;
	char	**tab;
	(void)env;

	if (tok == NULL)
		return (NULL);
	tmp = tok;
	while (tmp->type != command && tmp->next != NULL)
		tmp = tmp->next;
	if (tmp->type != command)
		return (NULL);
	tab = ft_split_ignore_quote(tmp->tok, ' ');
	//ultimate_dollar_transform(tab, env);
	return (tab);
}
