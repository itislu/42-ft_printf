#include "ft_printf.h"

static int	nbrlen(long nbr, t_format *format);
static int 	totalnbrlen(long nbr, int len_nbr, t_format *format);
static int	print_prefix(long nbr, t_format *format);
static int	print_nbr_in_correct_base(long nbr, t_format *format);

int	print_nbr(long nbr, t_format *format)
{
	char	padding;
	int		len_nbr;
	int		len_totalnbr;
	int		printed;

	if (format->zero && !format->minus && format->precision == -1)
		padding = '0';
	else
		padding = ' ';
	len_nbr = nbrlen(nbr, format);
	len_totalnbr = totalnbrlen(nbr, len_nbr, format);
	printed = 0;
	if (padding == '0')
		printed += print_prefix(nbr, format);
	if (!format->minus && len_totalnbr < format->width)
		printed += ft_putnchar_fd(padding, format->width - len_totalnbr, FD);
	if (padding == ' ' && format->specifier != 'u' && !(nbr == 0 && format->precision == 0))
		printed += print_prefix(nbr, format);
	if (format->precision > len_nbr)
		printed += ft_putnchar_fd('0', format->precision - len_nbr, FD);
	if (!(nbr == 0 && format->precision == 0))
		printed += print_nbr_in_correct_base(nbr, format);
	if (format->minus && len_totalnbr < format->width)
		printed += ft_putnchar_fd(' ', format->width - len_totalnbr, FD);
	return (printed);
}

static int	nbrlen(long nbr, t_format *format)
{
	int	base;
	int	len_nbr;

	if (format->specifier == 'x' || format->specifier == 'X')
		base = 16;
	else
		base = 10;
	if (nbr == 0 && format->precision != 0)
		len_nbr = 1;
	else
	{
		len_nbr = 0;
		while (nbr)
		{
			nbr /= base;
			len_nbr++;
		}
	}
	return (len_nbr);
}

static int 	totalnbrlen(long nbr, int len_nbr, t_format *format)
{
	int	len_totalnbr;

	len_totalnbr = len_nbr;
	if (len_nbr < format->precision)
		len_totalnbr = format->precision;
	if (format->specifier != 'u' && format->specifier != 'x' && format->specifier != 'X')
		if (!(nbr == 0 && format->precision == 0))
			if (nbr < 0 || format->plus || format->space)
				len_totalnbr++;
	if (format->specifier == 'x' || format->specifier == 'X')
		if (format->hash)
			len_totalnbr += 2;
	return (len_totalnbr);
}

static int	print_prefix(long nbr, t_format *format)
{
	int	printed;

	printed = 0;
	if ((format->specifier == 'x' || format->specifier == 'X') && nbr != 0)
	{
		if (format->hash)
		{
			if (format->specifier == 'x')
				printed += ft_putnstr_fd("0x", 2, FD);
			else if (format->specifier == 'X')
				printed += ft_putnstr_fd("0X", 2, FD);
		}
	}
	else
	{
		if (nbr < 0)
			printed += ft_putnchar_fd('-', 1, FD);
		else if (format->plus)
			printed += ft_putnchar_fd('+', 1, FD);
		else if (format->space)
			printed += ft_putnchar_fd(' ', 1, FD);
	}
	return (printed);
}

static int	print_nbr_in_correct_base(long nbr, t_format *format)
{
	int	printed;

	printed = 0;
	if (format->specifier == 'x')
		printed += ft_putnbr_base_fd(nbr, "0123456789abcdef", FD);
	else if (format->specifier == 'X')
		printed += ft_putnbr_base_fd(nbr, "0123456789ABCDEF", FD);
	else if (nbr < 0)
		printed += ft_putnbr_base_fd(nbr * -1, "0123456789", FD);
	else
		printed += ft_putnbr_base_fd(nbr, "0123456789", FD);
	return (printed);
}
