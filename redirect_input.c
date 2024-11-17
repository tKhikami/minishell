/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 08:42:15 by atolojan          #+#    #+#             */
/*   Updated: 2024/11/11 17:05:01 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_redirections(char *str)
{
	t_token	*tok;
	t_token	*cmd_tok;

	tok = ft_full_tokenization(str);
	if (!tok)
		return ;
	cmd_tok = tok;
	tok = tok->next;
	while (tok)
	{
		if ((int)tok->type == 1)
			redirect_input(cmd_tok, tok);
		else if ((int)tok->type == 2)
			redirect_output(cmd_tok, tok);
		tok = tok->next;
	}
}
/*
char	*find_exec(void)
{
	char	*path;
	char	*dir;

	path = getenv("PATH");
	if (!path)
	{
		perror("PATH");
		return (NULL);
	}
	dir = ft_strtok(path, ':');
	while (dir)
	{
		if (access(dir, X_OK))
*/
void	redirect_input(t_token *cmd, t_token *tok)
{
	int	fd;
	char	*path;

	fd = open(tok->tok, O_CREAT);
	if (fd < 0)
	{
		perror("File");
		return ;
	}
	dup2(fd, STDIN_FILENO);
	if (fd < 0)
	{
		perror("Redirection");
		return ;
	}
	path = getenv
}
