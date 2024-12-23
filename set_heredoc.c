/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:38:30 by atolojan          #+#    #+#             */
/*   Updated: 2024/12/23 15:08:13 by nyrandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "header.h"

void	clear_tok(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

int	check_heredoc(t_node *node)
{
	char	*str;
	int		i;
	int		has_heredoc;

	has_heredoc = 0;
	i = 0;
	str = node->str;
	while (str[i] != '\0')
	{
		if (str[i + 1] && str[i] == '<' && str[i + 1] == '<')
		{
			has_heredoc++;
			i++;
		}
		i++;
	}
	return (has_heredoc);
}

int	nbr_heredoc(t_node *node)
{
	int	hd;

	hd = 0;
	if (node->str != NULL)
		hd += check_heredoc(node);
	else
	{
		hd += nbr_heredoc(node->left);
		hd += nbr_heredoc(node->right);
	}
	return (hd);
}

int	set_heredoc(t_node *node, int *hd, int *index)
{
	t_token	*tok;
	t_token	*tmp;
	char	*s;

	if (node->str != NULL)
	{
		s = ft_strdup(node->str);
		tok = full_tokenization(s);
		tmp = tok;
		while (tmp)
		{
			if (tmp->type == 3)
			{
				hd[*index] = open_heredoc(tmp);
				(*index)++;
			}
			tmp = tmp->next;
		}
		if (tok)
			clear_tok(tok);
		free(s);
	}
	else
	{
		set_heredoc(node->left, hd, index);
		set_heredoc(node->right, hd, index);
	}
	return (0);
}

int	*manage_heredoc(t_node *node)
{
	int	hd_count;
	int	*heredoc;
	int	index;

	if (!node)
		return (NULL);
	hd_count = nbr_heredoc(node);
	if (hd_count == 0)
		return (NULL);
	heredoc = (int *) malloc(hd_count * sizeof(int) + 1);
	if (!heredoc)
		return (NULL);
	index = 0;
	set_heredoc(node, heredoc, &index);
	heredoc[hd_count] = -42;
	return (heredoc);
}
