#include "header.h"

void	del_variable(void *var)
{
		t_variable		*tmp;

		tmp = (t_variable *)var;
		if (var != NULL)
		{
				free(tmp->varname);
				free(tmp->value);
				free(tmp);
		}
}

int		print_variable(void *var)
{
		t_variable		*tmp;
		int				ret;

		tmp = (t_variable *)var;
		ret = 0;
		if (tmp == NULL)
				ret += printf("NULL");
		else
				ret += printf("%s || %s", tmp->varname, tmp->value);
		ret += printf("\n");
		return (ret);
}

t_list	*get_one_variable(char *str)
{
		t_variable		*tmp;
		t_list			*lst;
		char			*ptr;

		ptr = ft_strchr(str, '=');
		tmp = malloc(sizeof(t_variable));
		if (tmp != NULL)
		{
				tmp->varname = ft_substr(str, 0, ptr - str);
				tmp->value = ft_strdup(ptr + 1);
				if (tmp->varname == NULL || tmp->value == NULL)
				{
						free(tmp->varname);
						free(tmp->value);
						free(tmp);
						return (NULL);
				}
		}
		lst = ft_lstnew(tmp);
		if (lst == NULL)
				free(tmp);
		return (lst);
}

t_list	*get_all_variable(char **tab)
{
		int				i;
		t_list			*lst;
		t_list			*tmp;

		i = ft_tablen(tab) - 1;
		lst = NULL;
		while (i >= 0)
		{
				tmp = get_one_variable(tab[i]);
				if (tmp == NULL)
				{
						ft_lstclear(&lst, &del_variable);
						return (NULL);
				}
				ft_lstadd_front(&lst, tmp);
				i--;
		}
		return (lst);
}

t_list	*variable_chr(t_list *env, char *str)
{
		t_list	*tmp;

		if (str == NULL)
				return (NULL);
		tmp = env;
		while (tmp != NULL)
		{
				if (ft_strcmp(((t_variable *)tmp->content)->varname, str) == 0)
						return (tmp);
				tmp = tmp->next;
		}
		return (tmp);
}
