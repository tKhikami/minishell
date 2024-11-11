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

void	ft_get_line(int *exit_status, char *env[])
{
	char	*str;
	t_node	*root;
	t_list	*envp;
	static t_list	*exp;

	(void)exit_status;
	(void)root;
	//exp = NULL;
	envp = NULL;
	env_to_tlist(&envp, env, -1);
	while (1)
	{
		str = readline("$~>");
		if (str != NULL)
		{
			add_history(str);
//<<<<<<< HEAD
			ft_export(&envp, str);
			//ft_env(envp, 1);
			if (!envp)
				printf("ici\n");
			//t_assign *ass = (t_assign *)envp->content;
			printf("unset done : %d\n", ft_unset(&envp, "PATH"));
			//ft_env(envp, 0);
//=======
			//tok = ft_full_tokenization(str);
//>>>>>>> d0cce1c8df4c18691fc06f3cec791c7e5ebd140f
			free(str);
		}
		else
		{
			rl_clear_history();
			ft_printf("exit\n");
			ft_lstclear(&envp, free);
			ft_lstclear(&exp, free);
			free(str);
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
	if (n == 1)
	{
		signal(SIGINT, ft_handle_signals);
		signal(SIGQUIT, ft_handle_signals);
		ft_get_line(&exit_status, env);
		//printf("iaa %d\n", is_an_assignment("kejrhjke"));
	}
	return (exit_status);
}
