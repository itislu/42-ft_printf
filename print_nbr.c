#include "ft_printf.h"

static int	nbrlen(long nbr, t_format *format);
static int 	totallen(long nbr, int len_nbr, t_format *format);
static int	print_prefix(long nbr, t_format *format);
static int	print_nbr_in_correct_base(long nbr, t_format *format);

int	print_nbr(long nbr, t_format *format)
{
	char	padding;
	int		len_nbr;
	int		len_total;
	int		printed_count;

	if (format -> zero && !format -> minus && format -> precision == -1) // Possibly parentheses needed
		padding = '0';
	else
		padding = ' ';
	len_nbr = nbrlen(nbr, format);
	len_total = totallen(nbr, len_nbr, format);
	printed_count = 0;
	if (format -> zero)
		printed_count += print_prefix(nbr, format);
	if (!format -> minus && len_total < format -> width)
		printed_count += ft_putnchar_fd(padding, format -> width - len_total, 1);
	if (!format -> zero && format -> specifier != 'u' && !(nbr == 0 && format -> precision == 0))
		printed_count += print_prefix(nbr, format);
	if (format -> precision > len_nbr)
		printed_count += ft_putnchar_fd('0', format -> precision - len_nbr, 1);
	if (!(nbr == 0 && format -> precision == 0))
		printed_count += print_nbr_in_correct_base(nbr, format);
	if (format -> minus && len_total < format -> width)
		printed_count += ft_putnchar_fd(' ', format -> width - len_total, 1);
	return (printed_count);
}

static int	nbrlen(long nbr, t_format *format)
{
	int	base;
	int	len_nbr;

	if (format -> specifier == 'x' || format -> specifier == 'X')
		base = 16;
	else
		base = 10;
	if (nbr == 0 && format -> precision != 0)
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

static int 	totallen(long nbr, int len_nbr, t_format *format)
{
	int	len_total;

	len_total = len_nbr;
	if (len_nbr < format -> precision)
		len_total = format -> precision;
	if (format -> specifier != 'u' && format -> specifier != 'x' && format -> specifier != 'X')
		if (!(nbr == 0 && format -> precision == 0))
			if (nbr < 0 || format -> plus || format -> space)
				len_total++;
	if (format -> specifier == 'x' || format -> specifier == 'X')
		if (format -> hash)
			len_total += 2;
	return (len_total);
}

static int	print_prefix(long nbr, t_format *format)
{
	int	printed_count;

	printed_count = 0;
	if (format -> specifier == 'x' || format -> specifier == 'X')
	{
		if (format -> hash)
		{
			if (format -> specifier == 'x')
				printed_count += ft_putnstr_fd("0x", 2, 1);
			else if (format -> specifier == 'X')
				printed_count += ft_putnstr_fd("0X", 2, 1);
		}
	}
	else
	{
		if (nbr < 0)
			printed_count += ft_putnchar_fd('-', 1, 1);
		else if (format -> plus)
			printed_count += ft_putnchar_fd('+', 1, 1);
		else if (format -> space)
			printed_count += ft_putnchar_fd(' ', 1, 1);
	}
	return (printed_count);
}

static int	print_nbr_in_correct_base(long nbr, t_format *format)
{
	int	printed_count;

	printed_count = 0;
	if (format -> specifier == 'x')
		printed_count += ft_putnbr_base_fd(nbr, "0123456789abcdef", 1);
	else if (format -> specifier == 'X')
		printed_count += ft_putnbr_base_fd(nbr, "0123456789ABCDEF", 1);
	else if (nbr < 0)
		printed_count += ft_putnbr_base_fd(nbr * -1, "0123456789", 1);
	else
		printed_count += ft_putnbr_base_fd(nbr, "0123456789", 1);
	return (printed_count);
}
