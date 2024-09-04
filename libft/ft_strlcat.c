/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 08:37:14 by atolojan          #+#    #+#             */
/*   Updated: 2024/08/01 08:37:17 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_d;
	size_t	i;

	len_d = ft_strlen(dst);
	if (size < len_d)
		return (ft_strlen(src) + size);
	else
	{
		i = 0;
		while (src[i] != '\0' && (len_d + i + 1) < size)
		{
			dst[len_d + i] = src[i];
			i++;
		}
		dst[len_d + i] = '\0';
		return (len_d + ft_strlen(src));
	}
	return (0);
}
