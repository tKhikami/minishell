/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_isnumber.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: nyrandri <nyrandri@student.42antanana		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/09/16 17:31:22 by nyrandri		   #+#	  #+#			  */
/*	 Updated: 2024/09/16 17:31:22 by nyrandri		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "libft/libft.h"

int ft_isnumber(const char *number)
{
	int i;

	i = 0;
	if (number != NULL)
	{	
		if (number[0] == '-' || number[0] == '+')
			i++;
		while (number[i] != '\0')
		{
			if (ft_isdigit(number[i]) == 0)
				return (-1);
			i++;
		}
		return (0);
	}	
	return (-2);
}
