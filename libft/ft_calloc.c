/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 08:29:29 by atolojan          #+#    #+#             */
/*   Updated: 2024/08/01 08:29:32 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	void	*all;

	i = 0;
	if ((int)nmemb < 0 && (int)size < 0)
		return (0);
	if ((int)nmemb < 0 && size == 0)
		nmemb = 1;
	if (nmemb == 0 && (int)size < 0)
		size = 1;
	if ((nmemb != 0 && (int)size < 0) || ((int)nmemb < 0 && size != 0))
		return (0);
	all = malloc(nmemb * size);
	if (!all)
		return (0);
	while (i < nmemb * size)
	{
		((char *)all)[i] = 0;
		i++;
	}
	return (all);
}
