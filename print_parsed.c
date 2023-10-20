/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:12:14 by ldulling          #+#    #+#             */
/*   Updated: 2023/09/25 13:13:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	print_precision(const char *s, size_t *i, t_format *format);
static size_t	print_flags(const char *s, size_t *i, t_format *format);

size_t	print_parsed(const char *s, size_t parsed, t_format *format)
{
	size_t	i;
	size_t	printed;

	i = 0;
	printed = 0;
	if (s[0] == '%')
	{
		printed += ft_putnchar_fd('%', ++i, FD);
		printed += print_flags(s, &i, format);
		if (format->precision != -1)
			printed += print_precision(s, &i, format);
	}
	printed += ft_putnstr_fd(&s[i], parsed - i, FD);
	return (printed);
}

static size_t	print_flags(const char *s, size_t *i, t_format *format)
{
	size_t	printed;

	printed = 0;
	if (format->hash)
		printed += ft_putnchar_fd('#', 1, FD);
	if (format->plus)
		printed += ft_putnchar_fd('+', 1, FD);
	if (format->space && !format->plus)
		printed += ft_putnchar_fd(' ', 1, FD);
	if (format->minus)
		printed += ft_putnchar_fd('-', 1, FD);
	if (format->zero && !format->minus)
		printed += ft_putnchar_fd('0', 1, FD);
	// strchr()
	while (s[*i] == '#' || s[*i] == '+' || s[*i] == '-' || s[*i] == ' ' || s[*i] == '0')
		(*i)++;
	return (printed);
}

static size_t	print_precision(const char *s, size_t *i, t_format *format)
{
	size_t	width;
	size_t	printed;

	width = 0;
	while (s[*i] != '.')
	{
		width++;
		(*i)++;
	}
	printed = ft_putnstr_fd(&s[*i - width], width, FD);
	printed += ft_putnchar_fd('.', 1, FD);
	(*i)++;
	printed += ft_putnbr_base_fd(format->precision, "0123456789", FD);	//macro
	while (ft_isdigit(s[*i]))
		(*i)++;
	return ((size_t) printed);
}
