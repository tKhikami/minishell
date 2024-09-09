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
	if (sig == 2)
	{
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	}
}

int	main(void)
{
	char	*str;

	signal(SIGINT, ft_handle_signals);
	while (1)
	{
		str = readline("$>");
		if (str != NULL)
		{
			add_history(str);
			free(str);
		}
	}
	return (0);
}
