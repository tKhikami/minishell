#include "header.h"

char	*fusion_tab(char **tab)
{
	int	ultimate_len;
	char	*str;
	int	i;
	int	j;

	i = 0;
	j = 0;
	ultimate_len = ultimate_tablen(tab);
	if (ultimate_len == 0)
		return (NULL);
	str = malloc(ultimate_len + 1);
	if (str == NULL)
		return (NULL);
	while (tab[i] != NULL)
	{
		ft_memcpy(&str[j], tab[i], ft_strlen(tab[i]));
		j += ft_strlen(tab[i]);
		i++;
	}
	return (str);
}


t_list	*get_varname(char *str)
{
	int	i;
	char	*ptr;

	i = 1;
	if (str == NULL)
		return (NULL);
	ptr = str;
	while ((ft_isalnum(ptr[i]) || ptr[i] == '_') && ptr[i] != '\0')
		i++;
	ptr = ft_substr(ptr, 0, i);
	return (ft_lstnew(ptr));
}

t_list	*split_dollar(char *str)
{
	char	*ptr;
	int	len;
	t_list	*lst;

	if (str == NULL)
		return (NULL);
	ptr = str;
	len = 0;
	lst = NULL;
	while (ptr[len] != '\0')
	{
		if (ptr[len] == '$')
		{
			ft_lstadd_front(&lst, ft_lstnew(ft_substr(ptr, 0, len)));
			ft_lstadd_front(&lst, get_varname(&ptr[len]));
			ptr = &ptr[len] + 1;
			while ((ft_isalnum(ptr[0]) || ptr[0] == '_') && ptr[0] != '\0')
				ptr += 1;
			len = -1;
		}
		len++;
	}
	if (ptr[0] != '\0')
		ft_lstadd_front(&lst, ft_lstnew(ft_strdup(ptr)));
	return (lst);
}

int	is_variable(t_list *lst)
{
	char	*tmp;

	tmp = (char *)lst->content;
	if (tmp[0] == '\0')
		return (0);
	if (tmp[0] == '$' && (ft_isalnum(tmp[1]) || tmp[1] == '_'))
		return (42);
	else
		return (0);
}

char	*get_dollar_value(t_list *env, char *str)
{
	t_list	*ptr;
	char	*ret;

	if (env == NULL || str == NULL)
		return (NULL);
	ptr = variable_chr(env, &str[1]);
	if (ptr == NULL)
		ret = ft_strdup("");
	else
		ret = ft_strdup(((t_variable *)ptr->content)->value);
	if (ret == NULL)
		return (NULL);
	else
		return (ret);
}

char	*change_dollar(t_list *env, char *str)
{
	t_list	*lst;
	t_list	*ptr;
	char	*ret;
	char	*tmp;
	char	**tab;

	lst = split_dollar(str);
	if (lst == NULL)
		return (NULL);
	ptr = lst;
	while (ptr != NULL)
	{
		if (is_variable(ptr))
		{
			tmp = get_dollar_value(env, ptr->content);
			free(ptr->content);
			ptr->content = tmp;
		}
		ptr = ptr->next;
	}
	tab = ft_lsttotab(lst);
	invert_tab(&tab);
	ret = fusion_tab(tab);
	return (ret);
}

char	*dollar_expand(t_list *env, char *str)
{
	char	*ret;
	char	*tmp;
	int	len;

	if (env == NULL || str == NULL)
		return (NULL);
	len = ft_strlen(str);
	if (str[0] == '\'')
	{
		if (str[len - 1] == '\'')
			str[len - 1] = '\0';
		ret = ft_strdup(&str[1]);
	}
	else if (str[0] == '\"')
	{
		if (str[len - 1] == '\"')
			str[len - 1] = '\0';
		tmp = ft_strdup(&str[1]);
		ret = change_dollar(env, tmp);
		free(tmp);
	}
	else
		ret = change_dollar(env, str);
	return (ret);
}

char	**ultimate_change_dollar(t_list *env, char **tab)
{
	int	i;
	char	*tmp;

	i = 0;
	if (tab == NULL || env == NULL)
		return (NULL);
	while (tab[i] != NULL)
	{
		tmp = dollar_expand(env, tab[i]);
		if (tmp == NULL)
			ft_tabfree(tab);
		free(tab[i]);
		tab[i] = tmp;
		i++;
	}
	return (tab);
}
