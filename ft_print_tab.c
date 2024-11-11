/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_print_tab.c								:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: nyrandri <nyrandri@student.42antanana		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/09/16 13:39:03 by nyrandri		   #+#	  #+#			  */
/*	 Updated: 2024/09/16 13:39:03 by nyrandri		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

int ft_print_tab(const char **tab)
{
	int i;
	int length;

	i = 1;
	length = 0;
	if (tab != NULL && tab[0] != NULL)
	{	
		length += write(1, tab[0], ft_strlen(tab[0]));
		write(1, "\n", 1);
		while (tab[i] != NULL)
		{
			length += write(1, tab[i], ft_strlen(tab[i]));
			write(1, "\n", 1);
			i++;
		}
	}
	return (length);
}
