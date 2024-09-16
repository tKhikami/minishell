/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 09:34:02 by atolojan          #+#    #+#             */
/*   Updated: 2024/09/16 17:35:53 by nyrandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include "libft/libft.h"

/************************ TOOLS *********************/

void	ft_free_tab(char **split);
int		ft_print_tab_char(const char **tab);
int		ft_isnumber(const char *number);
void	ft_handle_signals(int sig);

/******************* BUILTIN COMMAD *****************/

int		ft_builtin_cmd(const char **tab);
int		ft_echo(const char **tab);

#endif
