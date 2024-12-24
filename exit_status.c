/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:14:45 by atolojan          #+#    #+#             */
/*   Updated: 2024/12/17 11:30:51 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_state(int pid)
{
	int	status;
	int	signal;
	int	exit_status;

	exit_status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) != 1)
	{
		if (WIFSIGNALED(status) == 1)
		{
			signal = WTERMSIG(status);
			return (signal + 128);
		}
	}
	else
	{
		exit_status = WEXITSTATUS(status);
		return (exit_status);
	}
	return (-2);
}
