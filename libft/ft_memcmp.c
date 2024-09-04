/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 08:33:42 by atolojan          #+#    #+#             */
/*   Updated: 2024/08/01 08:33:44 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	t1;
	unsigned char	t2;

	i = 0;
	t1 = 0;
	t2 = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		t1 = (unsigned char)((char *)s1)[i];
		t2 = (unsigned char)((char *)s2)[i];
		if (((char *)s1)[i] != ((char *)s2)[i])
			return (t1 - t2);
		i++;
	}
	return (t1 - t2);
}
