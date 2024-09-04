/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:40:19 by atolojan          #+#    #+#             */
/*   Updated: 2024/09/04 17:38:24 by nyrandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_list_to_string(t_list *list)
{
	char	*str;
	int		i;
	t_list	*tmp;

	i = 0;
	str = ft_calloc(1, ft_lstsize(list) + 1);
	if (str == NULL)
		return (NULL);
	tmp = list;
	while (tmp != NULL)
	{
		str[i] = *(char *)(tmp->content);
		tmp = tmp->next;
		i++;
	}
	return (str);
}

char	*ft_readline(const char *prompt)
{
	char	c;
	char	*s;
	char	*str;
	t_list	*list;

	list = NULL;
	write(1, prompt, ft_strlen(prompt));
	while (read(STDIN_FILENO, &c, 1) != -1 && c != '\n')
	{
		s = malloc(sizeof(char));
		if (s == NULL)
			return (NULL);
		*s = c;
		ft_lstadd_back(&list, ft_lstnew(s));
	}
	str = ft_list_to_string(list);
	ft_lstclear(&list, free);
	return (str);
}
