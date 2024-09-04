/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 08:58:50 by atolojan          #+#    #+#             */
/*   Updated: 2024/09/04 13:15:58 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd(void)
{
	static char	*line = (char *)NULL;

	if (line)
	{
		free(line);
	}
	line = readline("mini$>");
	if (line && *line)
		add_history(line);
	return (line);
}
