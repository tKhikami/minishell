/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 header.h											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: nyrandri <nyrandri@student.42antanana		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/11/17 16:11:58 by nyrandri		   #+#	  #+#			  */
/*	 Updated: 2024/11/17 16:12:24 by nyrandri		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#ifndef HEADER_H

# define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "minishell.h"
# include <sys/stat.h>

typedef struct s_variable
{
	char	*varname;
	char	*value;
}	t_variable;

/******************* TOOLS ******************/

int		ft_lstprint(t_list *lst, int (*format)(void *));
int		ft_tablen(char **tab);
int		ultimate_tablen(char **tab);
t_list	*ft_tabtolst(char **tab);
void	invert_tab(char ***tab);
char	**ft_concatenate_tab(char **tab1, char **tab2);
void	ft_tabfree(char **tab);
char	*ft_strtok(char *str, int c);
void	ft_lstinsert(t_list *lst, t_list *newlst);
int		format_content_char(void *str);
void	free_token(t_token *tok);
void	free_variable(void *var);

/***************** ENVIRONMENT **************/

void	del_variable(void *var);
int		print_variable(void *var);
t_list	*get_one_variable(char *str);
t_list	*get_all_variable(char **tab);
t_list	*variable_chr(t_list *env, char *str);

/****************** DOLLAR ******************/

char	*fusion_tab(char **tab);
t_list	*get_varname(char *str);
t_list	*split_dollar(char *str);
int		is_variable(t_list *lst);
char	*get_dollar_value(t_list *env, char *str);
char	*change_dollar(t_list *env, char *str);
char	*dollar_expand(t_list *env, char *str);
char	**ultimate_change_dollar(t_list *env, char **tab);

/***************** SEPARATION ***************/

char	*get_one_argument(char	**str, int c);
char	**divise_argument(char	*str);
t_list	*divise_all_argument(t_token *tok, t_list *env);
char	**ultimate_get_argument(t_token *tok, t_list *env);

/**************** EXECUTION ****************/

char	*path_valid(char *path);
char	*path_exist(char *executable, t_list *env);

#endif