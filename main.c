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
	(void)n;
	(void)vector;
	t_list	*env = get_all_variable(envp);
	char	*str = ft_strdup("cat -e\"main.c\" '$SHLVL'$SHLVL >> file2");
	t_token	*tok = full_tokenization(str);
	char	**tab = ultimate_get_argument(tok, env);
	ft_print_tab((const char **)tab);
	
	free_token(tok);
	ft_tabfree(tab);
	ft_lstclear(&env, &free_variable);
	free(str);
	
	return (0);
}
