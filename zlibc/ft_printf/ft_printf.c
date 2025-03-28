/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myousaf <myousaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:33:23 by myousaf           #+#    #+#             */
/*   Updated: 2024/09/1 07:13:22 by myousaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	ft_format(int fd, char c, va_list args)
{
	int	len;

	len = 0;
	if (c == 'c')
		len += ft_putchar_fd(va_arg(args, int), fd);
	else if (c == 's')
		len += ft_putstr_fd(va_arg(args, char *), fd);
	else if (c == 'd' || c == 'i')
		len += ft_putnbr_fd(va_arg(args, int), fd);
	else if (c == 'u')
		len += ft_unsignednbr(va_arg(args, unsigned int), fd);
	else if (c == 'x')
		len += ft_lilx(va_arg(args, unsigned int));
	else if (c == 'X')
		len += ft_bigx(va_arg(args, unsigned int));
	else if (c == 'p')
		len += ft_ptrx(va_arg(args, unsigned long));
	else if (c == '%')
		len += ft_putchar_fd('%', fd);
	else
		len += ft_putchar_fd(c, fd);
	return (len);
}

int	ft_printf(int fd, const char *format, ...)
{
	int		i;
	int		len;
	va_list	args;

	i = 0;
	len = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (format[i + 1] == '\0')
				break ;
			len += ft_format(fd, format[++i], args);
		}
		else
			len += ft_putchar_fd(format[i], fd);
		i++;
	}
	va_end (args);
	return (len);
}
