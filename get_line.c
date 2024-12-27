
/*																			  */
/*														  :::	   ::::::::   */
/*	 get_line.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: nyrandri <nyrandri@student.42antanana		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/11/11 06:55:17 by nyrandri		   #+#	  #+#			  */
/*	 Updated: 2024/11/11 06:55:17 by nyrandri		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "header.h"

void	get_line(char *envp[])
{
	char		*str;
	static char **test;

	test = envp;
	while (1)
	{
		setup_signals_parent();
		str = readline("$>");
		if (str != NULL)
		{
			ultimate_execve(str, test);
			free(str);
		}
		else
		{
			rl_clear_history();
			ft_printf("exit\n");
			free(str);
			return ;
		}
	}
	return ;
}
