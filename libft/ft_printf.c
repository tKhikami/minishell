/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atolojan <atolojan@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 09:12:54 by atolojan          #+#    #+#             */
/*   Updated: 2024/08/08 09:12:56 by atolojan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	convert_hex(unsigned long n, char *base)
{
	int		len;

	len = 0;
	if (n > 15)
	{
		len += convert_hex(n / 16, base);
		len += convert_hex(n % 16, base);
	}
	else
		len += ft_putchar(base[n]);
	return (len);
}

int	put_hex_low(unsigned int n)
{
	return (convert_hex(n, "0123456789abcdef"));
}

int	put_hex_upp(unsigned int n)
{
	return (convert_hex(n, "0123456789ABCDEF"));
}

int	get_value(char c, va_list *ptr)
{
	int	len;

	len = 0;
	if (c == 's')
		len += ft_putstr(va_arg(*ptr, char *));
	else if (c == 'c')
		len += ft_putchar(va_arg(*ptr, int));
	else if (c == 'd' || c == 'i')
		len += ft_putnbr(va_arg(*ptr, int));
	else if (c == 'p')
		len += ft_putptr(va_arg(*ptr, unsigned long));
	else if (c == 'u')
		len += ft_putnbr(va_arg(*ptr, unsigned int));
	else if (c == 'x')
		len += put_hex_low(va_arg(*ptr, unsigned int));
	else if (c == 'X')
		len += put_hex_upp(va_arg(*ptr, unsigned int));
	else if (c == '%')
		len += (write(1, "%", 1));
	else
		len += (write(1, &c, 1));
	return (len);
}

int	ft_printf(const char *s, ...)
{
	int		len;
	int		i;
	va_list	ptr;

	va_start(ptr, s);
	i = 0;
	len = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '%' && s[i + 1])
			len += get_value(s[(i++) + 1], &ptr);
		else
		{
			write(1, &s[i], 1);
			len++;
		}
		i++;
	}
	va_end(ptr);
	return (len);
}
