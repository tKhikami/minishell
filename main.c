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

t_token	*ft_create_token(char *token, t_status type)
{
	t_token	*value;

	value = malloc(sizeof(t_token));
	value->tok = token;
	value->type = type;
	return (value);
}

int	ft_is_in_set(char *set, char c)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return ((int)c);
		i++;
	}
	return (0);
}

t_status	check_status(char **tmp)
{
	while (ft_is_in_set(" \t\n\v", *tmp[0]) != 0)
	{
		*tmp[0] = '\0';
		(*tmp)++;
	}
	if (ft_strncmp(*tmp, DELIM_INPUT, 2) == 0)
	{
		ft_bzero(*tmp, 2);
		*tmp += 2;
		return (delim_input);
	}
	else if (ft_strncmp(*tmp, APPEND_OUTPUT, 2) == 0)
	{
		ft_bzero(*tmp, 2);
		*tmp += 2;
		return (append_output);
	}
	else if (ft_strncmp(*tmp, NORMAL_OUTPUT, 1) == 0)
	{
		ft_bzero(*tmp, 1);
		*tmp += 1;
		return (normal_output);
	}
	else if (ft_strncmp(*tmp, NORMAL_INPUT, 1) == 0)
	{
		ft_bzero(*tmp, 1);
		*tmp += 1;
		return (normal_input);
	}
	return (command);
}

void	move_cursor_to_the_first_set(char **cursor, char *set)
{
	char	*str;

	str = *cursor;
	while (ft_is_in_set(" \t\n\v", *cursor[0]) != 0)
		(*cursor)++;
	while ((ft_is_in_set(set, *cursor[0]) == 0 && *cursor[0] != '\0') || \
			ft_is_inner_quote(str, *cursor) == 1)
		(*cursor)++;
}

t_token	*ft_tokenization(char *str)
{
	static char	*tmp;
	t_token		*token;
	static int	i;

	token = NULL;
	if (str != NULL)
	{
		tmp = str;
		i = (int)check_status(&tmp);
	}
	else if (tmp[0] != '\0')
	{
		token = ft_create_token(tmp, i);
		if (token == NULL)
			return (NULL);
		if (i == command)
			move_cursor_to_the_first_set(&tmp, "<>");
		else
			move_cursor_to_the_first_set(&tmp, " \t\n\v<>");
		i = (int)check_status(&tmp);
		while (ft_is_in_set(" \t\n\v", tmp[0]) != 0)
			tmp++;
	}
	return (token);
}

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
		str = readline("$>");
		if (str != NULL)
		{
			/*add_history(str);
			t_token *tok = ft_tokenization(str);
			tok = ft_tokenization(NULL);
			int	i = 1;
			while (tok != NULL)
			{
				ft_printf("####### %d ######\ntok	: %s(%d)\n", i++, tok->tok, ft_strlen(tok->tok));
				ft_printf("type	: %d\n\n", (int)tok->type);
				tok = ft_tokenization(NULL);
			}*/
			add_history(str);
			ft_export(&exp, str);
			if (!exp)
				printf("ici\n");
			ft_env(envp, exp);
			printf("unset : %d\n", ft_unset(exp, str));
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
