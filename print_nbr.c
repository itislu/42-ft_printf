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
	int		printed_count;

	if (format -> zero && !format -> minus && format -> precision == -1) // Possibly parentheses needed
		padding = '0';
	else
		padding = ' ';
	len_nbr = nbrlen(nbr, format);
	len_totalnbr = totalnbrlen(nbr, len_nbr, format);
	printed_count = 0;
	if (padding == '0')
		printed_count += print_prefix(nbr, format);
	if (!format -> minus && len_totalnbr < format -> width)
		printed_count += ft_putnchar_fd(padding, format -> width - len_totalnbr, 1);
	if (padding == ' ' && format -> specifier != 'u' && !(nbr == 0 && format -> precision == 0))
		printed_count += print_prefix(nbr, format);
	if (format -> precision > len_nbr)
		printed_count += ft_putnchar_fd('0', format -> precision - len_nbr, 1);
	if (!(nbr == 0 && format -> precision == 0))
		printed_count += print_nbr_in_correct_base(nbr, format);
	if (format -> minus && len_totalnbr < format -> width)
		printed_count += ft_putnchar_fd(' ', format -> width - len_totalnbr, 1);
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

static int 	totalnbrlen(long nbr, int len_nbr, t_format *format)
{
	int	len_totalnbr;

	len_totalnbr = len_nbr;
	if (len_nbr < format -> precision)
		len_totalnbr = format -> precision;
	if (format -> specifier != 'u' && format -> specifier != 'x' && format -> specifier != 'X')
		if (!(nbr == 0 && format -> precision == 0))
			if (nbr < 0 || format -> plus || format -> space)
				len_totalnbr++;
	if (format -> specifier == 'x' || format -> specifier == 'X')
		if (format -> hash)
			len_totalnbr += 2;
	return (len_totalnbr);
}

static int	print_prefix(long nbr, t_format *format)
{
	int	printed_count;

	printed_count = 0;
	if ((format -> specifier == 'x' || format -> specifier == 'X') && nbr != 0)
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
