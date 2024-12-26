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

int	execve_cmd(char *command, char **envp, int descriptor[])
{
	int		fd[2];
	t_token *tok;
	char	**cmd;
	t_list	*env;

	env = get_all_variable(envp);
	tok = full_tokenization(command);
	fd[0] = open_inputs(-2, tok, descriptor);
	fd[1] = open_outputs(-2, tok, descriptor);
	cmd = ultimate_get_argument(tok, env);
	execve_inout(fd[0], fd[1], cmd, envp);
	if (fd[0] >= 0 && fd[0] != STDIN_FILENO)
		close(fd[0]);
	if (fd[1] >= 0 && fd[1] != STDOUT_FILENO)
		close(fd[1]);
	ft_tabfree(cmd);
	free_token(tok);
	ft_lstclear(&env, &free_variable);
	return (-1);
}

void	close_pipe(int fd[])
{
	close(fd[0]);
	close(fd[1]);
}

int	get_status_code(int id[], int fd[])
{
	int	status;

	close_pipe(fd);
	waitpid(id[1], &status, 0);
	waitpid(id[0], NULL, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (-1);
}

int	execve_pipe(t_node *root, char **envp)
{
	int	fd[2];
	int	id[2];

	if (root->str == NULL)
	{
		if (pipe(fd) == -1)
			return (-1);
		id[0] = fork();
		if (id[0] == 0)
		{
			dup2(fd[1], STDOUT_FILENO);
			close_pipe(fd);
			execve_pipe(root->left, envp);
		}
		id[1] = fork();
		if (id[1] == 0)
		{
			dup2(fd[0], STDIN_FILENO);
			close_pipe(fd);
			execve_pipe(root->right, envp);
		}
		else
			return (get_status_code(id, fd));
		return (-1);
	}
	else
		return (execve_cmd(root->str, envp, root->heredoc));
}

int	has_pipe(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (0);
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '|' && !ft_is_inner_quote(cmd, &cmd[i]))
			return (1);
		i++;
	}
	return (0);
}

int	lonely_builtin(char *cmd, char **envp)
{
	t_list	*env;
	t_token	*tok;
	char	**command;
	char	*dup;
	int		is_lonely;

	is_lonely = 0;
	if (!cmd)
		return (0);
	dup = ft_strdup(cmd);
	if (!dup)
		return (0);
	tok = full_tokenization(dup);
	env = get_all_variable(envp);
	command = ultimate_get_argument(tok, env);
	if (is_builtin(command[0]))
		is_lonely = 1;
	ft_tabfree(command);
	ft_lstclear(&env, free);
	free(env);
	clear_tok(tok);
	free(dup);
	return (is_lonely);
}

int	ultimate_execve(char *command, char **envp)
{
	char	**env;
	t_node	*root;
	int		fd[1];

	fd[0] = -42;
	env = ft_tabdup(envp);
	if (!has_pipe(command) && lonely_builtin(command, envp))
	{
		execve_cmd(command, envp, fd);
		return (0);
	}
	root = ft_create_tree(command);
	set_heredoc(root);
	id = fork();
	if (id == 0)
		execve_pipe(root, env);
	else
		wait(NULL);
	ft_tabfree(env);
	ft_free_tree(root);
	return (0);
}

int	main(int n, char *vector[], char *envp[])
{
	if (n != 1)
		return (-1);
	(void)vector;
	signal(SIGINT, &handle_signals);
	signal(SIGQUIT, &handle_signals);
	get_line(envp);
	ultimate_execve(vector[1], envp);
	return (0);
}
