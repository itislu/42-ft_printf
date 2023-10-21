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

static size_t	print_flags(const char *f_str, size_t *i, t_struct *format);
static size_t	print_width(const char *f_str, size_t *i, t_struct *format);
static size_t	print_precision(const char *f_str, size_t *i, t_struct *format);

size_t	print_parsed(const char *f_str, size_t parsed, t_struct *format)
{
	size_t	i;
	size_t	printed;

	i = 0;
	printed = 0;
	if (f_str[0] == '%')
	{
		printed += ft_putnchar_fd('%', ++i, FD);
		printed += print_flags(f_str, &i, format);
		printed += print_width(f_str, &i, format);
		printed += print_precision(f_str, &i, format);
	}
	printed += ft_putnstr_fd(&f_str[i], parsed - i, FD);
	return (printed);
}

static size_t	print_flags(const char *f_str, size_t *i, t_struct *format)
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
	while (f_str[*i] && ft_strchr("#+- 0", f_str[*i])) // header file
		(*i)++;
	return (printed);
}

static size_t	print_width(const char *f_str, size_t *i, t_struct *format)
{
	size_t	printed;

	printed = 0;
	if (format->width)
		printed += ft_putnbr_base_fd(format->width, "0123456789", FD);	//macro
	if (f_str[*i] == '*')
		(*i)++;
	else
		while (ft_isdigit(f_str[*i]))
			(*i)++;
	return ((size_t) printed);
}

static size_t	print_precision(const char *f_str, size_t *i, t_struct *format)
{
	size_t	printed;

	printed = 0;
	if (format->precision != -1)
	{
		printed += ft_putnchar_fd('.', 1, FD);
		(*i)++;
		printed += ft_putnbr_base_fd(format->precision, "0123456789", FD);	//macro
		if (f_str[*i] == '*')
			(*i)++;
		else
			while (ft_isdigit(f_str[*i]))
				(*i)++;
	}
	return ((size_t) printed);
}
