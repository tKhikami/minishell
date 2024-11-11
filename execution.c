/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 execution.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: nyrandri <nyrandri@student.42antanana		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/11/11 13:57:09 by nyrandri		   #+#	  #+#			  */
/*	 Updated: 2024/11/11 13:57:09 by nyrandri		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "header.h"

char	*path_valid(char *path)
{
	struct stat statbuff;

	if (path == NULL)
		return (NULL);
	if (stat(path, &statbuff) == 0)
		return (ft_strdup(path));
	else
		return (NULL);
}
