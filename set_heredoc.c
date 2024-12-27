/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:38:30 by atolojan          #+#    #+#             */
/*   Updated: 2024/12/27 14:49:19 by atolojan         ###   ########.fr       */
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

int	set_heredoc(t_node *node)
{
	t_token	*tok;
	t_token	*tmp;
	char	*s;
	int		nb_heredoc;
	int		index;

	index = 0;
	if (node == NULL)
		return (0);
	if (node->str != NULL)
	{
		nb_heredoc = check_heredoc(node);
		node->heredoc = malloc(sizeof(int) * (nb_heredoc + 1));
		if (node->heredoc == NULL)
			return (-1);
		s = ft_strdup(node->str);
		tok = full_tokenization(s);
		tmp = tok;
		while (tmp)
		{
			if (set_heredoc_status(-1) == 130)
				break ;
			if (tmp->type == 3)
			{
				node->heredoc[index] = open_heredoc(tmp);
				index++;
			}
			tmp = tmp->next;
		}
		node->heredoc[index] = -42;
		clear_tok(tok);
		free(s);
	}
	else
	{
		set_heredoc(node->left);
		set_heredoc(node->right);
	}
	return (0);
}
