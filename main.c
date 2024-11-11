/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 main.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: nyrandri <nyrandri@student.42antanana		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/11/11 07:04:42 by nyrandri		   #+#	  #+#			  */
/*	 Updated: 2024/11/11 12:22:37 by nyrandri		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "header.h"

char	*ft_strtok(char *str, int c)
{
	static char *ptr;
	char		*ret;
	int			i;

	i = 0;
	if (str != NULL)
		ptr = str;
	if (ptr == NULL || ptr[0] == '\0')
		return (NULL);
	ret = ptr;
	while (ptr[i] != c && ptr[i] != '\0')
		i++;
	while  (ptr[i] == c)
	{
		if (ptr[i] == '\0')
		{
			ptr = NULL;
			return (ret);
		}
		ptr[i] = '\0';
		i++;
	}
	ptr = ptr + i;
	return (ret);
}
		

char	*path_exist(char *executable, t_list *env)
{
	char	path[1024];
	t_list	*tmp;
	char	*value;
	char	*ptr;
	char	buffer[300];

	tmp = variable_chr(env, "PATH");
	value = ((t_variable *)tmp->content)->value;
	ft_strlcpy(path, value, ft_strlen(value) + 1);
	ptr = ft_strtok(path, ':');
	while (ptr != NULL)
	{
		ft_strlcpy(buffer, ptr, ft_strlen(value) + 1);
		ft_strlcat(buffer, "/", ft_strlen(value) + 2);
		ft_strlcat(buffer, executable, ft_strlen(executable) + ft_strlen(buffer) + 2);
		ptr = path_valid(buffer);
		if (ptr == NULL)
			ptr = ft_strtok(NULL, ':');
		else
			return (ft_strdup(buffer));
	}
	return (ptr);
}

int	main(int n, char *vector[], char *envp[])
{
	if (n <= 1)
		return (0);
	t_list	*env = get_all_variable(envp);
	char *str = path_exist(vector[1], env);
	if (str == NULL)
		printf("%s n'existe pas\n", str);
	else
		printf("%s existe\n", str);
	free(str);

	return (0);
}
