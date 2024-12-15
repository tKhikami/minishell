/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 builtins.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: atolojan <atolojan@student.42antanana		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/09/16 13:08:30 by atolojan		   #+#	  #+#			  */
/*	 Updated: 2024/11/18 07:14:56 by nyrandri		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(const char *path)
{
	if (chdir(path) != 0)
	{
		perror((char *) path);
		return (1);
	}
	return (0);
}

int	ft_pwd(char *tab)
{
	char	path[100];

	if (tab != NULL)
	{
		write(2, "pwd: too many arguments\n", 24);
		return (0);
	}
	return (ft_printf("%s\n", getcwd(path, 100)));
}

void	print_content(void *content)
{
	printf("%s\n", (char *) content);
}

void	sort_list(t_list **sorted)
{
	t_list	*i;
	t_list	*j;
	t_list	*min_idx;
	char	*tmp;

	if (*sorted == NULL || (*sorted)->next == NULL)
		return ;
	i = *sorted;
	while (i->next != NULL)
	{
		min_idx = i;
		j = i->next;
		while (j)
		{
			if (ft_strcmp(j->content, min_idx->content) < 0)
				min_idx = j;
			j = j->next;
		}
		if (min_idx != i)
		{
			tmp = min_idx->content;
			min_idx->content = i->content;
			i->content = tmp;
		}
		i = i->next;
	}
}

t_list	*make_sort_list(t_list **envp)
{
	t_list	*sorted;
	t_list	*tmp;
	char	*str;

	sorted = NULL;
	tmp = *envp;
	while (tmp)
	{
		str = ft_strdup(tmp->content);
		if (!str)
		{
			ft_lstclear(&sorted, free);
			return (NULL);
		}
		ft_lstadd_back(&sorted, ft_lstnew(str));
		tmp = tmp->next;
	}
	sort_list(&sorted);
	return (sorted);
}

int	ft_env(t_list *envp, int sorted)
{
	t_list		*tmp;
	t_list		*sort;
	t_assign	*ass;

	tmp = envp;
	if (sorted == 0)
	{
		while (tmp != NULL)
		{
			ass = extract_assign((char *)tmp->content);
			printf("%s=%s\n", ass->var_name, ass->value);
			remove_assign(ass);
			tmp = tmp->next;
		}
	}
	else
	{
		sort = make_sort_list(&envp);
		tmp = sort;
		while (tmp != NULL)
		{
			ass = extract_assign((char *)tmp->content);
			if (ass->value == NULL)
				printf("declare -x %s\n", ass->var_name);
			else if ((ass->value)[0] == '"')
				printf("declare -x %s=%s\n", ass->var_name, ass->value);
			else
				printf("declare -x %s=\"%s\"\n", ass->var_name, ass->value);
			remove_assign(ass);
			tmp = tmp->next;
		}
		ft_lstclear(&sort, free);
	}
	return (0);
}

int	ft_echo(const char **tab)
{
	int	i;
	int	length;

	i = 1;
	length = 0;
	if (tab[1] != NULL)
	{
		if (ft_memcmp(tab[1], "-n", 3) == 0)
		{
			length += ft_print_tab(&tab[2]);
		}
		else
		{
			length += ft_print_tab(&tab[1]);
			length += write(1, "\n", 1);
		}
	}
	else
		length += write(1, "\n", 1);
	return (length);
}

int	ft_exit(const char **tab)
{
	int	ret;

	ret = 0;
	if (tab[1] != NULL)
	{
		if (ft_isnumber(tab[1]) == -1)
		{
			printf("\"%s\" is not a numeric argument\n", tab[1]);
			exit(2);
		}
		else
			exit(ft_atoi(tab[1]) % 256);
	}
	exit(0);
}

void	remove_assign(t_assign *assign)
{
	free(assign->var_name);
	free(assign->value);
	free(assign);
}

int	ft_unset(t_list **env, char *str)
{
	t_list		*tmp;
	t_list		*previous;
	t_assign	*assign;

	tmp = *env;
	previous = NULL;
	while (tmp)
	{
		assign = extract_assign((char *)tmp->content);
		if (ft_memcmp(assign->var_name, str, ft_strlen(str)) == 0)
		{
			if (previous == NULL)
				*env = tmp->next;
			else
				previous->next = tmp->next;
			remove_assign(assign);
			free(tmp);
			return (0);
		}
		remove_assign(assign);
		previous = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return (1);
	return (0);
}

char	*get_var_name(t_assign *assign, char *str, int begin, int len)
{
	char	*s;

	s = ft_substr((const char *)str, begin, len);
	if (!s)
	{
		free(assign);
		return (NULL);
	}
	return (s);
}

t_assign	*extract_assign(char *str)
{
	t_assign	*assign;
	char		*s;
	int			i;
	int			equal;

	equal = 0;
	assign = (t_assign *) malloc(sizeof (t_assign));
	if (!assign)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
		{
			s = get_var_name(assign, str, 0, i);
			if (!s)
				return (NULL);
			assign->var_name = ft_strdup((const char *)s);
			if (!assign->var_name)
			{
				free(assign);
				return (NULL);
			}
			free(s);
			if (str[i + 1] != '\0')
			{
				s = get_var_name(assign, str, i + 1, ft_strlen(str) - (i + 1));
				if (!s)
				{
					free(assign->var_name);
					return (NULL);
				}
				assign->value = ft_strdup((const char *)s);
				if (!assign->value)
				{
					free(s);
					free(assign->var_name);
					free(assign);
					return (NULL);
				}
			}
			else
			{
				assign->value = ft_strdup("\0");
				if (!assign->value)
				{
					free(assign->var_name);
					free(assign);
					return (NULL);
				}
			}
			equal = 1;
			break ;
		}
		i++;
	}
	if (equal == 0)
	{
		assign->var_name = ft_strdup((const char *)str);
		if (!assign->var_name)
		{
			free(assign);
			return (NULL);
		}
		assign->value = NULL;
	}
	return (assign);
}

void	env_to_tlist(t_list **envp, char *env[], int count)
{
	int			i;

	i = 0;
	while (env[i] != NULL && i != count)
	{
		if (is_an_assignment(env[i]))
		{
			ft_lstadd_back(envp, ft_lstnew(ft_strdup(env[i])));
		}
		i++;
	}
}

int	is_an_assignment(char *str)
{
	int	i;
	int	after_equal;

	i = 1;
	after_equal = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
		{
			if (str[i - 1] == 32 || str[i + 1] == 32)
				return (0);
			after_equal = 1;
		}
		//else if (!ft_isalnum(str[i]) && str[i] != '_' && !after_equal)
		//	return (0);
		i++;
	}
	return (1);
}

char	*search_value(t_list *exp, char *str)
{
	t_assign	*assign;
	t_list		*tmp;
	char		*to_find;

	tmp = exp;
	while (tmp)
	{
		assign = extract_assign((char *)tmp->content);
		if (!ft_memcmp(assign->var_name, str, ft_strlen(assign->var_name)))
		{
			to_find = ft_strdup(assign->var_name);
			remove_assign(assign);
			return (to_find);
		}
		remove_assign(assign);
		tmp = tmp->next;
	}
	tmp = NULL;
	return (NULL);
}

void	handle_export(t_list **exp, char **s, int i)
{
	int			a;
	char		*to_find;
	t_assign	*ass;

	a = 1;
	while (s[i + a] != NULL)
	{
		to_find = search_value(*exp, s[i + a]);
		if (to_find)
		{
			ass = extract_assign(s[i + a]);
			if (ass->value != NULL)
			{
				ft_unset(exp, ass->var_name);
				env_to_tlist(exp, &s[i + a], 1);
			}
			else
			{
				remove_assign(ass);
				return ;
			}
			remove_assign(ass);
		}
		else
		{
			env_to_tlist(exp, &s[i + a], 1);
			return ;
		}
		a++;
	}
	if (a == 1)
		ft_env(*exp, 1);
}

int	ft_export(t_list **exp, char *str)
{
	char			**str_splitted;

	str_splitted = ft_split(str, 32);
	if (!str_splitted)
		return (1);
	handle_export(exp, str_splitted, 0);
	return (0);
}

int	ft_builtin_cmd(const char **tab, t_list *envp)
{
	(void)envp;
	if (tab != NULL)
	{
		if (ft_memcmp(tab[0], "echo", 5) == 0)
			return (ft_echo(tab));
		else if (ft_memcmp(tab[0], "exit", 5) == 0)
			return (ft_exit(tab));
		else if (ft_memcmp(tab[0], "cd", 3) == 0)
			return (ft_cd((const char *)tab[1]));
		else if (ft_memcmp(tab[0], "pwd", 4) == 0)
			return (ft_pwd((char *)tab[1]));
		/*else if (ft_memcmp(tab[0], "export", 7) == 0)
			return (ft_export((char *)tab[1], envp));
		else if (ft_memcmp(tab[0], "env", 4) == 0)
			return (ft_env(envp));*/
	}
	return (-1);
}
