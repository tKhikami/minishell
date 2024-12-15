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

int	execve_cmd(char *command, char **envp)
{
	int		fd[2];
	t_token	*tok;
	char	**cmd;
	int		std_fd;
	t_list  *env;
	
	env = get_all_variable(envp);
	tok = full_tokenization(command);
	std_fd = get_stdin_fd(envp);
	fd[0] = open_inputs(-2, tok, std_fd);
	if (fd[0] == -1)
		return (-1);
	fd[1] = open_outputs(-2, tok);
	if (fd[1] == -1)
	{
		close(fd[0]);
		return (-1);
	}
	cmd = ultimate_get_argument(tok, env);
	execve_inout(fd[0], fd[1], cmd, envp);
	close(fd[0]);
	close(fd[1]);
	free_token(tok);
	return (0);
}

int	execve_parent(char *command, char **envp, int fd[])
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	return (execve_cmd(command, envp));
}

int	execve_pipe(t_node *root, char **envp)
{
	int	fd[2];
	int	id;

	if (root == NULL)
		return (-1);
	if (root->str == NULL)
	{
		if (pipe(fd) == -1)
		{
			perror("minishell");
			return (-1);
		}
		id = fork();
		if (id == 0)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			close(fd[0]);
			return (execve_pipe(root->left, envp));
		}
		else
		{
			wait(NULL);
			return (execve_parent(root->right->str, envp, fd));
		}
	}
	else
		return (execve_cmd(root->str, envp));
}

int	main(int n, char *vector[], char *envp[])
{
	if (n != 2)
		return (-1);
	char	**env;
	char	**tmp;
	t_node	*root;

	tmp = ft_tabdup(envp);
	env = add_stdin_fd(tmp);
	free(tmp);
	root = ft_create_tree(vector[1]);
	execve_pipe(root, env);
	ft_free_tree(root);
	return (0);
}
