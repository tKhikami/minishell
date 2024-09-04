/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 08:29:41 by atolojan          #+#    #+#             */
/*   Updated: 2024/08/01 08:29:43 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (8);
	else if (c >= 'a' && c <= 'z')
		return (8);
	else if (c >= '0' && c <= '9')
		return (8);
	return (0);
}
