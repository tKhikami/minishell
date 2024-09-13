/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 main.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: nyrandri <nyrandri@student.42antanana		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/09/03 08:43:58 by nyrandri		   #+#	  #+#			  */
/*	 Updated: 2024/09/04 08:31:49 by nyrandri		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_signals(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_get_line(void)
{
	char	*str;

	while (1)
	{
		str = readline("$>");
		if (str != NULL)
		{
			add_history(str);
			/* execution code goes here */
			/* ft_printf("%s\n", str); */
			free(str);
		}
		else
		{
			rl_clear_history();
			ft_printf("exit");
			exit(EXIT_SUCCESS);
		}
	}
	exit(EXIT_SUCCESS);
}



int	main(void)
{
	signal(SIGINT, ft_handle_signals);
	signal(SIGQUIT, ft_handle_signals);
	ft_get_line();

	return (0);
}
