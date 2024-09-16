/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_print_tab_char.c								:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: nyrandri <nyrandri@student.42antanana		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/09/16 13:39:03 by nyrandri		   #+#	  #+#			  */
/*	 Updated: 2024/09/16 13:39:03 by nyrandri		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

int ft_print_tab_char(const char **tab)
{
	int i;
	int length;

	i = 1;
	length = 0;
	if (tab[0] != NULL)
	{	
		length += write(1, tab[0], ft_strlen(tab[0]));
		while (tab[i] != NULL)
		{
			length += write(1, " ", 1); 
			length += write(1, tab[i], ft_strlen(tab[i]));
			i++;
		}
	}	
	return (length);
}
