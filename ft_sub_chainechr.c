/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_sub_chainechr.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: nyrandri <nyrandri@student.42antanana		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/09/23 12:51:20 by nyrandri		   #+#	  #+#			  */
/*	 Updated: 2024/09/23 12:51:54 by nyrandri		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_sub_chainechr(char *s1, char *s2)
{
	int i;
	int j;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{	
		j = 0;
		while (s1[i + j] == s2[j] && s2[j] != '\0')
			j++;
		if (s2[j] == '\0')
			return (&s1[i]);
		i++;
	}	
	return (NULL);
}
