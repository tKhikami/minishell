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

<<<<<<< HEAD
<<<<<<< HEAD
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
	
=======
char	*ft_strtok(char *str, int c)
{
	static char *ptr;
	char		*ret;
	int			i;

	i = 0;
	if (str != NULL)
		ptr = str;
	if (ptr == NULL || ptr[0] == '\0')
		return (NULL);
	ret = ptr;
	while (ptr[i] != c && ptr[i] != '\0')
		i++;
	while  (ptr[i] == c)
	{
		if (ptr[i] == '\0')
		{
			ptr = NULL;
			return (ret);
		}
		ptr[i] = '\0';
		i++;
	}
	ptr = ptr + i;
	return (ret);
}
		

char	*path_exist(char *exec, t_list *env)
{
	char	path[1024];
	t_list	*tmp;
	char	*value;
	char	*ptr;
	char	buf[300];

	tmp = variable_chr(env, "PATH");
	value = ((t_variable *)tmp->content)->value;
	ft_strlcpy(path, value, ft_strlen(value) + 1);
	ptr = ft_strtok(path, ':');
	while (ptr != NULL)
	{
		ft_strlcpy(buf, ptr, ft_strlen(value) + 1);
		ft_strlcat(buf, "/", ft_strlen(value) + 2);
		ft_strlcat(buf, exec, ft_strlen(exec) + ft_strlen(buf) + 2);
		ptr = path_valid(buf);
		if (ptr == NULL)
			ptr = ft_strtok(NULL, ':');
		else
			return (ft_strdup(buf));
	}
	return (ptr);
}

int	main(int n, char *vector[], char *envp[])
{
	if (n <= 1)
		return (0);
	check_redirections(vector[1], envp);
>>>>>>> atolojan
=======
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
>>>>>>> 348bb52 (execution semble marcher. Il faut plus de teste)
	return (0);
}
