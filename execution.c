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

	str = variable_chr_tab("STDIN_FD", envp);
	if (str == NULL)
		return (-1);
	std_fd = ft_atoi(str);
	free(str);
	return (std_fd);
}

int	get_stdout_fd(char **envp)
{
	char	*str;
	int		std_fd;

	str = variable_chr_tab("STDOUT_FD", envp);
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
	str = malloc(ft_strlen(tmp) + 10);
	if (str != NULL)
	{
		ft_memmove(str, "STDIN_FD=", 9);
		ft_memmove(str + 9, (const void *)tmp, ft_strlen(tmp) + 1);
	}
	else
		close(*std_fd);
	free(tmp);
	return (str);
}

char	*dup_stdout_fd(int *std_fd)
{
	char	*tmp;
	char	*str;

	*std_fd = dup(STDOUT_FILENO);
	if (*std_fd < 0)
		return (NULL);
	tmp = ft_itoa(*std_fd);
	if (tmp == NULL)
	{
		close(*std_fd);
		return (NULL);
	}
	str = malloc(ft_strlen(tmp) + 11);
	if (str != NULL)
	{
		ft_memmove(str, "STDOUT_FD=", 10);
		ft_memmove(str + 10, (const void *)tmp, ft_strlen(tmp) + 1);
	}
	else
		close(*std_fd);
	free(tmp);
	return (str);
}

char	**add_stdinout_fd(char **envp)
{
	int		std_fd[2];
	char	*tmp[2];
	char	**tab;
	char	**ret;

	tmp[0] = dup_stdin_fd(&std_fd[0]);
	tmp[1] = dup_stdout_fd(&std_fd[1]);
	if (tmp[0] == NULL || tmp[1] == NULL)
	{
		free(tmp[0]);
		free(tmp[1]);
		return (NULL);
	}
	tab = malloc(sizeof(char *) * 3);
	ret = NULL;
	if (tab != NULL)
	{
		tab[0] = tmp[0];
		tab[1] = tmp[1];
		tab[2] = NULL;
		ret = ft_concatenate_tab(envp, tab);
	}
	if (ret == NULL)
	{
		close(std_fd[0]);
		close(std_fd[1]);
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

int	open_heredoc(t_token *tmp)
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
		str = mini_readline("> ", STDIN_FILENO);
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

int	open_file(t_token *tmp, int descriptor[])
{
	int			fd;
	static int	i;

	if (tmp->type == normal_input)
		fd = open(tmp->tok, O_RDONLY, 0644);
	else if (tmp->type == normal_output)
		fd = open(tmp->tok, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (tmp->type == append_output)
		fd = open(tmp->tok, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (tmp->type == delim_input)
	{
		fd = descriptor[i];
		i++;
	}
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

int	open_outputs(int fd, t_token *tok, int descriptor[])
{
	int	fd_tmp;

	if (tok == NULL)
		return (fd);
	if (fd == -1)
		return (-1);
	if (fd == -2)
	{
		if (tok->type == normal_output || tok->type == append_output)
			fd = open_file(tok, descriptor);
		return (open_outputs(fd, tok->next, descriptor));
	}
	if (tok->type == normal_output || tok->type == append_output)
	{
		fd_tmp = open_file(tok, descriptor);
		if (fd_tmp == -1)
		{
			close(fd);
			return (-1);
		}
		dup2(fd_tmp, fd);
		close(fd_tmp);
	}
	return (open_outputs(fd, tok->next, descriptor));
}

int	open_inputs(int fd, t_token *tok, int descriptor[])
{
	int	fd_tmp;

	if (tok == NULL)
		return (fd);
	if (fd == -1)
		return (-1);
	if (fd == -2)
	{
		if (tok->type == normal_input || tok->type == delim_input)
			fd = open_file(tok, descriptor);
		return (open_inputs(fd, tok->next, descriptor));
	}
	if (tok->type == normal_input || tok->type == delim_input)
	{
		fd_tmp = open_file(tok, descriptor);
		close (fd);
		if (fd_tmp == -1)
			return (-1);
		fd = fd_tmp;
	}
	return (open_inputs(fd, tok->next, descriptor));
}

int	execve_inout(int in, int out, char **com, char **envp)
{
	char	*path;
	t_list	*env;

	if (com == NULL)
		return (-1);
	env = get_all_variable(envp);
	path = path_exist(com[0], env);
	ft_lstclear(&env, &free_variable);
	if (path == NULL)
		return (-1);
	if (in >= 0)
		dup2(in, STDIN_FILENO);
	if (out >= 0)
		dup2(out, STDOUT_FILENO);
	execve(path, com, envp);
	free(path);
	return (-1);
}
