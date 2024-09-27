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

void	ft_get_line(int *exit_status)
{
	char	*str;
	t_node	*root;

	(void)exit_status;
	while (1)
	{
		str = readline("$>");
		if (str != NULL)
		{
			add_history(str);
			root = ft_create_tree(str);
			ft_print_tree(root);
			ft_free_tree(root);
			free(str);
		}
		else
		{
			rl_clear_history();
			ft_printf("exit\n");
			return ;
		}
	}
	return ;
}

int	main(int n, char *arg[], char *env[])
{
	int	exit_status;

	exit_status = 0;
	(void)arg;
	(void)env;
	if (n == 1)
	{
		signal(SIGINT, ft_handle_signals);
		signal(SIGQUIT, ft_handle_signals);
		ft_get_line(&exit_status);
	}
	return (exit_status);
}
