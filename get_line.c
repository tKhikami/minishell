/* ************************************************************************** */
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

void	get_line(int *exit_status, char *envp[])
{
	char	*str;
	t_list	*envar;

	envar = NULL;
	(void)exit_status;
	(void)envp;
	while (1)
	{
		str = readline("$>");
		if (str != NULL)
		{
			//*exit_status = exec_ult(str, envp);
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
