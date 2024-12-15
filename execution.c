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

int	get_stdin_fd(char **envp)
{
	char	*str;
	int		std_fd;

	str = variable_chr_tab("std_fd", envp);
	if (str == NULL)
		return (-1);
	std_fd = ft_atoi(str);
	free(str);
	return (std_fd);
}

char	*dup_stdin_fd(int *std_fd)
{
	char	*tmp;
	char	*str;

	*std_fd = dup(STDIN_FILENO);
	if (*std_fd < 0)
		return (NULL);
	tmp = ft_itoa(*std_fd);
	if (tmp == NULL)
	{
		close(*std_fd);
		return (NULL);
	}
	str = malloc(ft_strlen(tmp) + 8);
	if (str != NULL)
	{
		ft_memmove(str, "std_fd=", 7);
		ft_memmove(str + 7, (const void *)tmp, ft_strlen(tmp) + 1);
	}
	else
		close(*std_fd);
	free(tmp);
	return (str);
}

char	**add_stdin_fd(char **envp)
{
	int		std_fd;
	char	*tmp;
	char	**tab;
	char	**ret;

	tmp = dup_stdin_fd(&std_fd);
	if (tmp == NULL)
		return (NULL);
	tab = malloc(sizeof(char *) * 2);
	ret = NULL;
	if (tab != NULL)
	{
		tab[0] = tmp;
		tab[1] = NULL;
		ret = ft_concatenate_tab(envp, tab);
	}
	if (ret == NULL)
	{
		close(std_fd);
		free(tmp);
	}
	free(tab);
	return (ret);
}

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

char	*mini_readline(char *prompt, int fd)
{
	char	*str;

	ft_putstr_fd(prompt, fd);
	str = get_next_line(fd);
	str[ft_strlen(str) - 1] = '\0';
	return (str);
}

int	open_heredoc(t_token *tmp, int std_fd)
{
	int		fd[2];
	char	*str;
	char	*doc;

	if (pipe(fd) == -1)
		return (-1);
	doc = ft_strtrim(tmp->tok, " ");
	str = ft_strdup("");
	while (ft_strcmp(str, doc) != 0)
	{
		free(str);
		str = mini_readline("> ", std_fd);
		if (ft_strcmp(str, doc) == 0 || ft_strcmp(str, doc) == 2000000000)
			break ;
		ft_putendl_fd(str, fd[1]);
	}
	if (str == NULL)
	{
		close(fd[0]);
		fd[0] = -1;
	}
	free(str);
	free(doc);
	close(fd[1]);
	return (fd[0]);
}

int	open_file(t_token *tmp, int std_fd)
{
	int	fd;

	if (tmp->type == normal_input)
		fd = open(tmp->tok, O_RDONLY, 0644);
	else if (tmp->type == normal_output)
		fd = open(tmp->tok, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (tmp->type == append_output)
		fd = open(tmp->tok, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (tmp->type == delim_input)
		fd = open_heredoc(tmp, std_fd);
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
			fd = open_file(tok, 1);
		return (open_outputs(fd, tok->next));
	}
	if (tok->type == normal_output || tok->type == append_output)
	{
		fd_tmp = open_file(tok, 1);
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

int	open_inputs(int fd, t_token *tok, int std_fd)
{
	int	fd_tmp;

	if (tok == NULL)
		return (fd);
	if (fd == -1)
		return (-1);
	if (fd == -2)
	{
		if (tok->type == normal_input || tok->type == delim_input)
			fd = open_file(tok, std_fd);
		return (open_inputs(fd, tok->next, std_fd));
	}
	if (tok->type == normal_input || tok->type == delim_input)
	{
		fd_tmp = open_file(tok, std_fd);
		close (fd);
		if (fd_tmp == -1)
			return (-1);
		fd = fd_tmp;
	}
	return (open_inputs(fd, tok->next, std_fd));
}

int	execve_inout(int in, int out, char **com, char **envp)
{
	int		id;
	char	*path;
	t_list	*env;

	if (com == NULL)
		return (-1);
	env = get_all_variable(envp);
	path = path_exist(com[0], env);
	ft_lstclear(&env, &free_variable);
	if (path == NULL)
		return (-1);
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
	wait(NULL);
	free(path);
	return (0);
}
