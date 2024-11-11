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

#include "minishell.h"

void	get_line(int *exit_status, char *env[])
{
	char	*str;
	t_token *tok;
	char **tab;
	t_list	*envar;
	envar = NULL;
	(void)exit_status;
	(void)env;
	(void)tok;


	while (1)
	{
		str = readline("$>");
		if (str != NULL)
		{
			add_history(str);
			tok = ft_full_tokenization(str);
			tab = get_argument(tok, envar);
			ft_print_tab((const char **)tab);
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
