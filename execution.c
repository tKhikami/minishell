/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 execution.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: nyrandri <nyrandri@student.42antanana		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/11/11 13:57:09 by nyrandri		   #+#	  #+#			  */
/*	 Updated: 2024/11/11 13:57:09 by nyrandri		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "header.h"

char	*path_valid(char *path)
{
	if (path == NULL)
		return (NULL);
	if (access(path, F_OK | X_OK) == 0)
		return (ft_strdup(path));
	else
		return (NULL);
}

char	*path_exist(char *executable, t_list *env)
{
	char	path[1024];
	t_list	*tmp;
	char	*value;
	char	*ptr;
	char	buffer[300];

	tmp = variable_chr(env, "PATH");
	if (tmp == NULL)
		return (NULL);
	value = ((t_assign *)tmp->content)->value;
	ft_strlcpy(path, value, ft_strlen(value) + 1);
	ptr = ft_strtok(path, ':');
	while (ptr != NULL)
	{
		ft_strlcpy(buffer, ptr, ft_strlen(value) + 1);
		ft_strlcat(buffer, "/", ft_strlen(value) + 2);
		ft_strlcat(buffer, executable, ft_strlen(executable) \
				+ ft_strlen(buffer) + 2);
		ptr = path_valid(buffer);
		if (ptr == NULL)
			ptr = ft_strtok(NULL, ':');
		else
			return (ptr);
	}
	return (ptr);
}

int	open_file(t_token *tmp)
{
	int	fd;

	if (tmp->type == normal_input)
		fd = open(tmp->tok, O_RDONLY);
	else if (tmp->type == normal_output)
		fd = open(tmp->tok, O_WRONLY | O_CREAT | O_TRUNC);
	else if (tmp->type == append_output)
		fd = open(tmp->tok, O_WRONLY | O_CREAT | O_APPEND);
	else
		fd = -1;
	if (fd == -1)
	{
		perror("minishell");
		return (-1);
	}
	else
		return (fd);
}

int	open_outputs(int fd, t_token *tok)
{
	int	fd_tmp;

	if (tok == NULL)
		return (fd);
	if (fd == -1)
		return (-1);
	if (fd == -2)
	{
		if (tok->type == normal_output || tok->type == append_output)
			fd = open_file(tok);
		return (open_outputs(fd, tok->next));
	}
	if (tok->type == normal_output || tok->type == append_output)
	{
		fd_tmp = open_file(tok);
		if (fd_tmp == -1)
		{
			close(fd);
			return (-1);
		}
		dup2(fd_tmp, fd);
		close(fd_tmp);
	}
	return (open_outputs(fd, tok->next));
}

int	open_inputs(int fd, t_token *tok)
{
	int	fd_tmp;

	if (tok == NULL)
		return (fd);
	if (fd == -1)
		return (-1);
	if (fd == -2)
	{
		if (tok->type == normal_input)
			fd = open_file(tok);
		return (open_inputs(fd, tok->next));
	}
	if (tok->type == normal_input)
	{
		fd_tmp = open_file(tok);
		close (fd);
		if (fd_tmp == -1)
			return (-1);
		fd = fd_tmp;
	}
	return (open_inputs(fd, tok->next));
}

int	execve_inout(int in, int out, char **com, char **envp)
{
	int		id;
	char	*path;
	t_list	*env;

	env = get_all_variable(envp);
	path = path_exist(com[0], env);
	ft_lstclear(&env, &free_variable);
	id = fork();
	if (id == 0)
	{
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
		if (execve(path, com, envp) == -1)
		{
			perror("execve");
			return (-1);
		}
	}
	else
		wait(NULL);
	free(path);
	return (0);
}
