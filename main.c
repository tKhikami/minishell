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

int	execve_pipe(t_node *root, char **envp, int descriptor[])
{
	int	fd[2];
	int	id[2];

	if (root->str == NULL)
	{
		if (pipe(fd) == -1)
			return (-1);
		id[0] = fork();
		if (id[0] == 0) // in child left
		{
			dup2(fd[1], STDOUT_FILENO);
			close_pipe(fd);
			execve_pipe(root->left, envp, descriptor);
		}
		id[1] = fork();
		if (id[1] == 0) // in child right
		{
			dup2(fd[0], STDIN_FILENO);
			close_pipe(fd);
			execve_pipe(root->right, envp, descriptor);
		}
		else
			return (get_status_code(id, fd));
		return (-1);
	}
	else
		return (execve_cmd(root->str, envp, descriptor));
}

int	ultimate_execve(char *command, char **envp)
{
	int		id;
	int		*descriptor;
	char	**tmp;
	char	**env;
	t_node	*root;

	tmp = ft_tabdup(envp);
	env = add_stdinout_fd(tmp);
	free(tmp);
	root = ft_create_tree(command);
	descriptor = manage_heredoc(root);
	id = fork();
	if (id == 0)
		execve_pipe(root, env, descriptor);
	else
		wait(NULL);
	ft_tabfree(env);
	ft_free_tree(root);
	if (id == 0)
		return (-1);
	return (0);
}

int	main(int n, char *vector[], char *envp[])
{
	if (n != 2)
		return (-1);
	ultimate_execve(vector[1], envp);
	return (0);
}
