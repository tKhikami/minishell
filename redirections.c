/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 08:42:15 by atolojan          #+#    #+#             */
/*   Updated: 2024/11/19 17:28:04 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(int *fd, char *cmd, char *envp[])
{
	t_list	*env;
	char	*path;
	char	*args[2];

	env = get_all_variable(envp);
	if (!env)
		return ;
	path = path_exist(cmd, env);
	if (!path)
	{
		if (fd)
			close(*fd);
		return ;
	}
	args[0] = path;
	args[1] = NULL;
	if (execve(path, args, envp) == -1)
	{
		if (fd)
			close(*fd);
		perror("Erreur de path");
		return ;
	}
	else
		printf("Bien execute\n");
}

void	open_dup(t_token *tok, int *fd)
{
	int	type;

	type = tok->type;
	if (type == 1)
		*fd = open(tok->tok, O_RDONLY, 0444);
	else if (type == 2)
		*fd = open(tok->tok, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (type == 4)
		*fd = open(tok->tok, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (*fd < 0)
	{
		perror("File");
		return ;
	}
	if (type == 4)
		type = 2;
	if (type != 3 && dup2(*fd, type - 1) < 0)
	{
		perror("Redirection");
		close(*fd);
		return ;
	}
	if (type == 1 || type == 2 || type == 4)
		close(*fd);
}

void	set_redirect(char *cmd, t_token *tok, char *envp[])
{
	int	id;
	int	fd;

	fd = -1;
	cmd[ft_strlen(cmd) - 1] = '\0';
	id = fork();
	if (id == 0)
	{
		open_dup(tok, &fd);
		exec_cmd(&fd, cmd, envp);
	}
	else
		wait(NULL);
}

void	heredoc_to_file(t_token *tok)
{
	int		fd;
	char	*line;
	t_token	*heredoc;
	char	*concat[2];

	fd = -1;
	concat[1] = ft_strdup("\0");
	heredoc = tok;
	if (tok->next && tok->type == 2)
	{
		tok = tok->next;
		open_dup(tok, &fd);
	}
	while (1)
	{
		write(2, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(heredoc->tok, line, ft_strlen(heredoc->tok)) == 0)
		{
			printf("%s", concat[1]);
			return ;
		}
		else
		{
			concat[0] = concat[1];
			concat[1] = ft_strjoin(concat[0], line);
			free(concat[0]);
			free(line);
		}
	}
}

void	check_redirections(char *str, char *envp[])
{
	t_token	*tok;
	t_token	*head;
	t_token	*cmd;

	(void)envp;
	tok = ft_full_tokenization(str);
	if (!tok)
		return ;
	head = tok;
	if ((int)tok->type == 0)
		cmd = tok;
	tok = tok->next;
	if (!tok)
		exec_cmd(NULL, cmd->tok, envp);
	while (tok)
	{
		if ((int)tok->type == 1 && cmd)
			return (set_redirect(cmd->tok, tok, envp));
		else if ((int)tok->type == 2 && cmd)
			return (set_redirect(cmd->tok, tok, envp));
		else if ((int)tok->type == 3 && cmd)
			return (heredoc_to_file(tok));
		tok = tok->next;
	}
}
