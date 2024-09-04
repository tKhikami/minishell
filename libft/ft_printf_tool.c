/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_tool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 09:12:43 by atolojan          #+#    #+#             */
/*   Updated: 2024/08/08 09:12:46 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	if (str != NULL)
		return (write(1, str, ft_strlen(str)));
	return (write(1, "(null)", 6));
}

int	ft_putnbr(long nb)
{
	int		len;
	long	num;

	len = 0;
	if (nb < 0)
	{
		len += ft_putchar('-');
		nb *= -1;
	}
	num = nb;
	if ((nb / 10) > 0)
	{
		len += ft_putnbr(num / 10);
		len += ft_putnbr(num % 10);
	}
	else
		len += ft_putchar(num + '0');
	return (len);
}

int	ft_putptr(unsigned long l)
{
	int	len;

	len = 0;
	if (l != 0)
	{
		len += ft_putstr("0x");
		len += convert_hex(l, "0123456789abcdef");
	}
	else
		len += ft_putstr("(nil)");
	return (len);
}
