/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyrandri <nyrandri@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:01:10 by nyrandri          #+#    #+#             */
/*   Updated: 2024/12/26 08:46:17 by atolojan         ###   ########.fr       */
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
# include <fcntl.h>
# include "libft/libft.h"
# include <sys/wait.h>

# define PIPE "|"
# define NORMAL_INPUT "<"
# define NORMAL_OUTPUT ">"
# define DELIM_INPUT "<<"
# define APPEND_OUTPUT ">>"

typedef enum e_status
{
	command,
	normal_input,
	normal_output,
	delim_input,
	append_output,
	undefine
}	t_status;

typedef struct s_token
{
	char			*tok;
	t_status		type;
	struct s_token	*next;
}	t_token;

typedef struct s_assign
{
	char	*var_name;
	char	*value;
}			t_assign;

typedef struct s_node
{
	char			*str;
	int				*heredoc;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

/************************ TOOLS *********************/

int			ft_print_tab(char **tab);
int			ft_isnumber(const char *number);
int			ft_is_inner_quote(char *str, char *to_compare);
int			ft_is_in_set(char *set, char c);
void		handle_signals(int sig);
char		*ft_substrchr(char *s1, char *s2);
char		*my_strtok(char *str, char *delims, \
		int (*ignore)(char *, char *));
t_token		*full_tokenization(char *str);
int			check_builtins(char *str, t_list *envp);
char		**ft_lsttotab(t_list *lst);
void		ft_lstfree(t_list **lst);
char		**ft_split_ignore_quote(char *str, char c);
char		**split_ignore_quote(char const *s, char c);
int			env_to_tlist(t_list **envp, char *env[], int count);
int			is_an_assignment(char *str);
void		print_content(void *content);
int			ft_is_whitespace(char c);
int			handle_export(t_list **exp, char **s, int i);
char		*search_value(t_list *exp, char *str);
t_assign	*extract_assign(char *str);
void		remove_assign(t_assign *assign);
t_list		*get_all_variable(char **str);

void		free_variable(void *var);
char		*dollar_expand(t_list *env, char *str);
void		clear_tok(t_token *head);
t_list		*make_sort_list(t_list **envp);
void		sort_list(t_list **sorted);
char		*get_var_name(t_assign *assign, char *str, int begin, int len);
int			export_print(t_list *envp, t_assign *ass, t_list *tmp);

/******************* BUILTIN COMMAD *****************/

int			ft_builtin_cmd(char **tab, t_list *envp);
int			is_builtin(char *cmd);
int			ft_cd(const char *path);
int			ft_pwd(char *tab);
int			ft_echo(char **tab);
int			ft_export(t_list **exp, char **str);
int			ft_env(t_list *envp, int sorted);
int			ft_unset(t_list **env, char *str);
int			ft_exit(const char **tab);

/***************** TREE MANIPULATION ****************/

void		ft_nodeiter(t_node *node, void (*f)(t_node *));
void		ft_print_node(t_node *node);
void		ft_print_tree(t_node *node);
void		ft_free_tree(t_node *root);
t_node		*ft_create_node(char *str);
void		ft_branching(t_node *node);
t_node		*ft_create_tree(char *str);

/****************** EXEC FUNCTION *******************/

void		check_redirections(char *str, char *envp[]);
char		*path_exist(char *exec, t_list *env);
char		**get_argument(t_token *tok, t_list *env);
char		*get_variable(char *str, t_list *env);

/********************  KERNEL  **********************/

void		get_line(int *exit_status, char *env[]);

#endif
