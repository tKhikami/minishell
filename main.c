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

int	execve_cmd(char *command, t_list *envp, int descriptor[])
{
	int		fd[2];
	t_token *tok;
	char	**cmd;

	tok = full_tokenization(command);
	fd[0] = open_inputs(-2, tok, descriptor);
	fd[1] = open_outputs(-2, tok, descriptor);
	if (fd[0] == -1 || fd[1] == -1)
	{
		free_token(tok);
		return (-1);
	}
	cmd = ultimate_get_argument(tok, envp);
	handler_tfree(NULL, tok, 3);
	handler_tfree(NULL, cmd, 2);
	execve_inout(fd[0], fd[1], cmd, envp);
	if (fd[0] >= 0 && fd[0] != STDIN_FILENO)
		close(fd[0]);
	if (fd[1] >= 0 && fd[1] != STDOUT_FILENO)
		close(fd[1]);
	handler_tfree(NULL, NULL, -1);
	return (-1);
}

void	setup_signals_parent(void)
{
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_signals_children(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	close_pipe(int fd[])
{
	close(fd[0]);
	close(fd[1]);
}

int	get_status_code(int id[], int fd[])
{
	int	status;
	int	result;

	result = 0;
	close_pipe(fd);
	if (waitpid(id[1], &status, 0) > 0)
	{
		if (WIFEXITED(status))
			result = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			result = WTERMSIG(status) + 128;
	}
	waitpid(id[0], NULL, 0);
	setup_signals_parent();
	return (result);
}

int	execve_pipe(t_node *root, t_list *envp)
{
	int	fd[2];
	int	id[2];

	if (root->str == NULL)
	{
		if (pipe(fd) == -1)
			return (-1);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		id[0] = fork();
		if (id[0] == 0)
		{
			setup_signals_children();
			dup2(fd[1], STDOUT_FILENO);
			close_pipe(fd);
			execve_pipe(root->left, envp);
		}
		id[1] = fork();
		if (id[1] == 0)
		{
			setup_signals_children();
			dup2(fd[0], STDIN_FILENO);
			close_pipe(fd);
			execve_pipe(root->right, envp);
		}
		handler_tfree(NULL, NULL, -1);
		return (get_status_code(id, fd));
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

int	lonely_builtin(char *cmd, t_list *envp)
{
	t_token	*tok;
	char	**command;
	char	*dup;
	int		is_lonely;

	is_lonely = 0;
	if (!cmd || cmd[0] == '\0')
		return (0);
	dup = ft_strdup(cmd);
	if (!dup)
		return (0);
	tok = full_tokenization(dup);
	if (!tok)
	{
		free(dup);
		return (0);
	}
	command = ultimate_get_argument(tok, envp);
	if (command && command[0] && is_builtin(command[0]))
		is_lonely = 1;
	else if (!command)
	{
		free(dup);
		clear_tok(tok);
		return (0);
	}
	ft_tabfree(command);
	clear_tok(tok);
	free(dup);
	return (is_lonely);
}

int	ultimate_execve(char *command, t_list **envp)
{
	t_node	*root;
	int		fd[1];
	int		id;

	fd[0] = -42;
	if (!has_pipe(command) && lonely_builtin(command, *envp))
	{
		execve_cmd(command, *envp, fd);
		return (0);
	}
	root = ft_create_tree(command);
	set_heredoc(root);
	if (set_heredoc_status(-1) == 130)
	{
		set_heredoc_status(1);
		return (0);
	}
	id = fork();
	if (id == 0)
	{
		setup_signals_children();
		execve_pipe(root, *envp);
		ft_free_tree(root);
		exit(0);
	}
	else
		wait(NULL);
	ft_free_tree(root);
	return (0);
}

int	main(int n, char *vector[], char *envp[])
{
	t_list	*lst;

	lst = NULL;
	handler_tfree(&lst, NULL, -1);
	if (n != 1)
		return (-1);
	(void)vector;
	get_line(envp);
	ft_lstfree(&lst);
	return (0);
}
