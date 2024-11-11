/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_is_inner_quote.c								:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: nyrandri <nyrandri@student.42antanana		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/09/23 13:26:57 by nyrandri		   #+#	  #+#			  */
/*	 Updated: 2024/09/23 13:27:25 by nyrandri		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

int ft_is_inner_quote(char *str, char *to_compare)
{
	int		i;	
	char	*open;
	char	*close;

	open = str;
	close = str - 1;
	if (str == NULL)
		return (0);
	while (close < to_compare)
	{
		i = 0;
		open = close + 1;
		while (open[i] != '\"' && open[i] != '\'' && open[i] != '\0')
			i++;
		open = &open[i];
		if (open > to_compare)
			break ;
		close = &open[1];
		while (close[0] != open[0] && close[0] != '\0')
			close++;
	}	
	if (open < to_compare && to_compare < close && close[0] != '\0')
		return (1);
	else
		return (0);
}
