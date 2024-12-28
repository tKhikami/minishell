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
	perror("minishell");
	return (ptr);
}

int	is_absolute_path(char *executable)
{
	if (executable == NULL)
		return (-1);
	if (executable[0] == '/')
		return (1);
	else
		return (0);
}

char	*get_path(char *executable, char **envp)
{
	char	*tmp;
	t_list	*env;
	char	*path;

	env = get_all_variable(envp);
	if (env == NULL)
		return (NULL);
	tmp = variable_chr_tab("PATH", envp);
	if (tmp == NULL || is_absolute_path(executable))
		path = path_valid(executable);
	else
		path = path_exist(executable, env);
	ft_lstclear(&env, &free_variable);
	return (path);
}

char	*mini_readline(char *prompt, int fd)
{
	char	*str;

	ft_putstr_fd(prompt, fd);
	str = get_next_line(fd);
	if (str == NULL)
		return (NULL);
	str[ft_strlen(str) - 1] = '\0';
	return (str);
}

int	set_heredoc_status(int set)
{
	static int	sig;

	if (set != -1)
		sig = set;
	return (sig);
}

void	sig_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		set_heredoc_status(130);
		write(1, "\n", 1);
		close(STDIN_FILENO);
	}
}

int	open_heredoc(t_token *tmp)
{
	int		fd[2];
	char	*str;
	char	*doc;

	if (pipe(fd) == -1)
		return (-1);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_heredoc);
	doc = ft_strtrim(tmp->tok, " ");
	str = ft_strdup("");
	while (ft_strcmp(str, doc) != 0)
	{
		free(str);
		str = readline("> ");
		if (set_heredoc_status(-1) == 130)
		{
			open("/dev/tty", O_RDONLY);
			break ;
		}
		if (!str)
		{
			close(fd[1]);
			ft_putstr_fd("warning: here-document ", 2);
			ft_putstr_fd("delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(doc, 2);
			ft_putstr_fd("`)\n", 2);
			free(doc);
			return (fd[0]);
		}
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
		perror("file");
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

int	execve_inout(int in, int out, char **com, t_list *envp)
{
	char	*path;
	int		built;
	char	**env;

	built = -1;
	if (com == NULL)
		return (-1);
	if (in >= 0)
		dup2(in, STDIN_FILENO);
	if (out >= 0)
		dup2(out, STDOUT_FILENO);
	if (is_builtin(com[0]))
	{
		built = execve_builtin(com, envp);
		return (built);
	}
	env = ft_lsttotab(envp);
	if (!env)
		return (-1);
	path = get_path(com[0], env);
	if (path == NULL)
		return(-1);
	execve(path, com, env);
	free(path);
	ft_tabfree(env);
	return (-1);
}
