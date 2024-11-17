/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_strtok.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: nyrandri <nyrandri@student.42antanana		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/11/12 08:48:05 by nyrandri		   #+#	  #+#			  */
/*	 Updated: 2024/11/12 08:48:05 by nyrandri		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "header.h"

char	*ft_strtok(char *str, int c)
{
	static char *ptr;
	char		*ret;
	int			i;

	i = 0;
	if (str != NULL)
		ptr = str;
	if (ptr == NULL || ptr[0] == '\0')
		return (NULL);
	ret = ptr;
	while (ptr[i] != c && ptr[i] != '\0')
		i++;
	while  (ptr[i] == c)
	{	
		if (ptr[i] == '\0')
		{
			ptr = NULL;
			return (ret);
		}
		ptr[i] = '\0';
		i++;
	}	
	ptr = ptr + i;
	return (ret);
}
