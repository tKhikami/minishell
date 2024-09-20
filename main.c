/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 main.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: nyrandri <nyrandri@student.42antanana		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/09/03 08:43:58 by nyrandri		   #+#	  #+#			  */
/*	 Updated: 2024/09/04 08:31:49 by nyrandri		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_node(void *node)
{
	static int	i;

	i++;
	ft_printf("######## %d #######\n", i);
	ft_printf("element	: %s\n", ((t_node *)node)->element);
	ft_printf("left		: %p\n", ((t_node *)node)->left);
	ft_printf("right	: %p\n\n", ((t_node *)node)->right);
}

t_node	*ft_create_node(void *element)
{
	t_node	*ret;

	ret = malloc(sizeof(t_node));
	ret->element = element;
	ret->left = NULL;
	ret->right = NULL;
	return (ret);
}

void	ft_nodeiter(void *node, void (*f)(void *))
{
	if (node != NULL)
	{
		f(node);
		ft_nodeiter(((t_node *)node)->left, f);
		ft_nodeiter(((t_node *)node)->right, f);
	}
}



int	ft_is_inner_quote(char *str, char *to_compare)
{
	int		i;
	char	*open;
	char	*close;

	i = 0;
	open = str;
	close = str;
	if (str == NULL)
		return (0);
	while (close < to_compare)
	{
		while (open[i] != '\"' && open[i] != '\'' && open[i] != '\0')
			i++;
		open = &open[i];
		if (close[0] == '\0')
			break ;
		close = &open[1];
		while (close[0] != open[0] && close[0] != '\0')
			close++;
	}
	if (open < to_compare && to_compare < close && close[0] != '\0')
		return (1);
	else
		return (0);
}

char	**ft_reverse_split_in_two(char *str, char c)
{
	int		len;
	int		i;
	char	**ret;

	len = ft_strlen(str);
	i = 1;
	while (i <= len && (str[len - i] != c || ft_is_inner_quote(str, &str[len - i])))
		i++;
	if (i == len + 1)
	{
		ret = malloc(sizeof(char *) * 2);
		if (ret == NULL)
			return (NULL);
		ret[0] = ft_substr(str, 0, ft_strlen(str));
		if (ret[0] == NULL)
		{
			free(ret);
			return (NULL);
		}
		ret[1] = NULL;
	}
	else
	{
		ret = malloc(sizeof(char *) * 4);
		if (ret == NULL)
			return (NULL);
		ret[0] = ft_substr(str, 0, len - i);
		ret[1] = ft_strdup("|");
		ret[2] = ft_substr(str, len - i + 1, i);
		if (ret[0] == NULL || ret[1] == NULL || ret[2] == NULL)
		{
			free(ret[0]);
			free(ret[1]);
			free(ret[2]);
			free(ret);
			return (NULL);
		}
		ret[3] = NULL;
	}
	return (ret);
}



void	ft_branching(void *node)
{
	char	**tab;

	tab = ft_reverse_split_in_two(((t_node *)node)->element, '|');
	if (tab != NULL)
	{
		free(((t_node *)node)->element);
		if (tab[1] != NULL)
		{
			((t_node *)node)->element = tab[1];
			((t_node *)node)->left = ft_create_node(tab[0]);
			((t_node *)node)->right = ft_create_node(tab[2]);
		}
		else
		{
			((t_node *)node)->element = tab[0];
		}
		free(tab);
	}
}

t_node	*ft_create_tree(char *str)
{
	t_node	*root;

	root = ft_create_node(str);

	ft_nodeiter(root, &ft_branching);
	return (root);
}

void	ft_print_tree(void *root)
{
	ft_nodeiter((t_node *)root, &ft_print_node);
}

void	ft_get_line(void)
{
	char	*str;
	t_node	*root;

	while (1)
	{
		str = readline("$>");
		if (str != NULL)
		{
			add_history(str);
			root = ft_create_tree(str);

			ft_print_tree(root);
		}
		else
		{
			rl_clear_history();
			ft_printf("exit\n");
			exit(EXIT_SUCCESS);
		}
	}
	exit(EXIT_SUCCESS);
}

int	main(int n, char *arg[], char *env[])
{
	(void)arg;
	(void)env;
	if (n == 1)
	{
		signal(SIGINT, ft_handle_signals);
		signal(SIGQUIT, ft_handle_signals);
		ft_get_line();
	}
	return (0);
}
