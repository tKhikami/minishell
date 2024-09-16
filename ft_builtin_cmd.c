/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_builtin_cmd.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: nyrandri <nyrandri@student.42antanana		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/09/16 13:28:57 by nyrandri		   #+#	  #+#			  */
/*	 Updated: 2024/09/16 13:28:57 by nyrandri		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

int ft_echo(const char **tab)
{
	int i;
	int length;

	i = 1; 
	length = 0;
	if (tab[1] != NULL)
	{
		if (ft_memcmp(tab[1], "-n", 3) == 0)
		{	
			length += ft_print_tab_char(&tab[2]);
		}
		else
		{
			length += ft_print_tab_char(&tab[1]);
			length += write(1, "\n", 1);
		}
	}
	else
		length += write(1, "\n", 1);
	return (length);
}

int	ft_exit(const char **tab)
{
	int	ret;

	ret = 0;
	if (tab[1] != NULL)
	{
		if (ft_isnumber(tab[1]) == -1)
		{
			printf("\"%s\" is not a numeric argument\n", tab[1]);
			exit(2);
		}
		else
			exit(ft_atoi(tab[1]) % 256);
	}
	exit(0);
}

int ft_builtin_cmd(const char **tab)
{
	if (tab != NULL)
	{	
		if (ft_memcmp(tab[0], "echo", 5) == 0)
			return (ft_echo(tab));
		else if (ft_memcmp(tab[0], "exit", 5) == 0)
			return (ft_exit(tab));
	}	
	return (-1);
}
