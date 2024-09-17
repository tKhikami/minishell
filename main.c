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

void	ft_get_line(void)
{
	char	*str;

	while (1)
	{
		str = readline("$>");
		if (str != NULL)
		{
			add_history(str);
			char	**tab = ft_split(str, ' ');
			int		len = ft_builtin_cmd((const char **)tab);
			if (len == -1)
				ft_printf("command not found\n");

			/*execution code goes here*/

			free(str);
		}
		else
		{
			rl_clear_history();
			ft_printf("exit\n");
			exit(EXIT_SUCCESS);
		}
	}
	exit(EXIT_SUCCESS);
}

int	main(int n, char *arg[], char *env[])
{
	(void)arg;
	(void)env;
	if (n == 1)
	{
		signal(SIGINT, ft_handle_signals);
		signal(SIGQUIT, ft_handle_signals);
		ft_get_line();
	}
	return (0);
}
