/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_handle_signals.c								:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: nyrandri <nyrandri@student.42antanana		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/09/16 13:44:56 by nyrandri		   #+#	  #+#			  */
/*	 Updated: 2024/09/16 13:44:56 by nyrandri		  ###	########.fr		  */
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
