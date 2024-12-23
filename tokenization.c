/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrandri <nyrandri@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:16:39 by nyrandri          #+#    #+#             */
/*   Updated: 2024/12/15 18:02:12 by nyrandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*ft_create_token(char *token, t_status type)
{
	t_token	*value;

	value = malloc(sizeof(t_token));
	value->tok = token;
	value->type = type;
	value->next = NULL;
	return (value);
}

static int	mini_check_status(char *str, int i)
{
	ft_bzero(str, i);
	return (i);
}

static t_status	check_status(char **tmp)
{
	while (ft_is_in_set(" \t\n\v", *tmp[0]) != 0)
		*tmp += mini_check_status(*tmp, 1);
	if (ft_strncmp(*tmp, DELIM_INPUT, 2) == 0)
	{
		*tmp += mini_check_status(*tmp, 2);
		return (delim_input);
	}
	else if (ft_strncmp(*tmp, APPEND_OUTPUT, 2) == 0)
	{
		*tmp += mini_check_status(*tmp, 2);
		return (append_output);
	}
	else if (ft_strncmp(*tmp, NORMAL_OUTPUT, 1) == 0)
	{
		*tmp += mini_check_status(*tmp, 1);
		return (normal_output);
	}
	else if (ft_strncmp(*tmp, NORMAL_INPUT, 1) == 0)
	{
		*tmp += mini_check_status(*tmp, 1);
		return (normal_input);
	}
	return (command);
}

static void	move_cursor_to_the_first_set(char **cursor, char *set)
{
	char	*str;

	str = *cursor;
	while (ft_is_in_set(" \t\n\v", *cursor[0]) != 0)
		(*cursor)++;
	while ((ft_is_in_set(set, *cursor[0]) == 0 || \
			ft_is_inner_quote(str, *cursor)) && *cursor[0] != '\0')
		(*cursor)++;
}

static t_token	*ft_tokenization(char *str)
{
	static char	*tmp;
	t_token		*token;
	static int	i;

	token = NULL;
	if (str != NULL)
	{
		tmp = str;
		i = (int)check_status(&tmp);
	}
	else if (tmp[0] != '\0')
	{
		token = ft_create_token(tmp, i);
		if (token == NULL)
			return (NULL);
		if (i == command)
			move_cursor_to_the_first_set(&tmp, "<>");
		else
			move_cursor_to_the_first_set(&tmp, " \t\n\v<>");
		i = (int)check_status(&tmp);
		while (ft_is_in_set(" \t\n\v", tmp[0]) != 0)
			tmp++;
	}
	return (token);
}

t_token	*full_tokenization(char *str)
{
	t_token	*tok;
	t_token	*tmp;
	t_token	*prev;

	if (str == NULL)
		return (NULL);
	ft_tokenization(str);
	tmp = ft_tokenization(NULL);
	tok = tmp;
	while (tmp != NULL)
	{
		prev = tmp;
		tmp = ft_tokenization(NULL);
		prev->next = tmp;
	}
	return (tok);
}
