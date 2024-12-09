/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 main.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: nyrandri <nyrandri@student.42antanana		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/11/11 07:04:42 by nyrandri		   #+#	  #+#			  */
/*	 Updated: 2024/11/11 12:22:37 by nyrandri		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "header.h"

int	main(int n, char *vector[], char *envp[])
{
	if (n != 2)
		return (-1);
	t_list	*env = get_all_variable(envp);
	t_token	*tok = full_tokenization(vector[1]);
	char	**command = ultimate_get_argument(tok, env);

	int	in_fd = open_inputs(-2, tok);
	int	out_fd = open_outputs(-2, tok);

	if (in_fd == -1 || out_fd == -1)
		return (-1);
	execve_inout(in_fd, out_fd, command, envp);
	close(in_fd);
	close(out_fd);
	ft_lstclear(&env, &free_variable);
	free_token(tok);
	ft_tabfree(command);
	return (0);
}
