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
/*
void	ft_branching(t_node *node, char *flag, int (*ignore)(char *, char *))
{
	if (node != NULL)
	{
		node->element = 
*/
void	ft_get_line(void)
{
	char	*str;
//	t_node	*root;

	while (1)
	{
		str = readline("$>");
		if (str != NULL)
		{
			add_history(str);
			char **tab = ft_split(str, ' ');
//			root = ft_create_tree(str);
			char *tmp = ft_sub_chainechr(tab[0], tab[1]);
			ft_printf("%s\n", tmp);
//			ft_print_tree(root);
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
