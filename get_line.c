
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
	char	*str;
	t_list	*my_env;

	my_env = NULL;
	env_to_tlist(&my_env, envp, -1);
	while (1)
	{
		setup_signals_parent();
		str = readline("$>");
		if (str != NULL)
		{
			add_history(str);
			ultimate_execve(str, &my_env);
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
	ft_lstclear(&my_env, free);
	return ;
}
