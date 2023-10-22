#include "ft_printf.h"

static int	nbrlen(long nbr, t_struct *f);
static int 	totalnbrlen(long nbr, int len_nbr, t_struct *f);
static int	print_prefix(long nbr, t_struct *f);
static int	print_nbr_in_correct_base(long nbr, t_struct *f);

int	print_nbr(long nbr, t_struct *f)
{
	char	padding;
	int		len_nbr;
	int		len_totalnbr;
	int		printed;

	if (f->zero && !f->minus && f->precision < 0)
		padding = '0';
	else
		padding = ' ';
	len_nbr = nbrlen(nbr, f);
	len_totalnbr = totalnbrlen(nbr, len_nbr, f);
	printed = 0;
	if (padding == '0')
		printed += print_prefix(nbr, f);
	if (!f->minus && len_totalnbr < f->width)
		printed += ft_putnchar_fd(padding, f->width - len_totalnbr, FD);
	if (padding == ' ' && f->specifier != 'u' && !(nbr == 0 && f->precision == 0))
		printed += print_prefix(nbr, f);
	if (f->precision > len_nbr)
		printed += ft_putnchar_fd('0', f->precision - len_nbr, FD);
	if (!(nbr == 0 && f->precision == 0))
		printed += print_nbr_in_correct_base(nbr, f);
	if (f->minus && len_totalnbr < f->width)
		printed += ft_putnchar_fd(' ', f->width - len_totalnbr, FD);
	return (printed);
}

static int	nbrlen(long nbr, t_struct *f)
{
	int	base;
	int	len_nbr;

	if (ft_strchr("xX", f->specifier))
		base = 16;
	else
		base = 10;
	if (nbr == 0 && f->precision != 0)
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

static int 	totalnbrlen(long nbr, int len_nbr, t_struct *f)
{
	int	len_totalnbr;

	len_totalnbr = len_nbr;
	if (len_nbr < f->precision)
		len_totalnbr = f->precision;
	if (!ft_strchr("uxX", f->specifier))
		if (!(nbr == 0 && f->precision == 0))
			if (nbr < 0 || f->plus || f->space)
				len_totalnbr++;
	if (ft_strchr("xX", f->specifier))
		if (f->hash)
			len_totalnbr += ft_strlen("0x");
	return (len_totalnbr);
}

static int	print_prefix(long nbr, t_struct *f)
{
	int	printed;

	printed = 0;
	if (ft_strchr("xX", f->specifier) && nbr != 0)
	{
		if (f->hash)
		{
			if (f->specifier == 'x')
				printed += ft_putnstr_fd("0x", 2, FD);
			else if (f->specifier == 'X')
				printed += ft_putnstr_fd("0X", 2, FD);
		}
	}
	else
	{
		if (nbr < 0)
			printed += ft_putnchar_fd('-', 1, FD);
		else if (f->plus)
			printed += ft_putnchar_fd('+', 1, FD);
		else if (f->space)
			printed += ft_putnchar_fd(' ', 1, FD);
	}
	return (printed);
}

static int	print_nbr_in_correct_base(long nbr, t_struct *f)
{
	int	printed;

	printed = 0;
	if (f->specifier == 'x')
		printed += ft_putnbr_base_fd(nbr, "0123456789abcdef", FD); //header file
	else if (f->specifier == 'X')
		printed += ft_putnbr_base_fd(nbr, "0123456789ABCDEF", FD);
	else if (nbr < 0)
		printed += ft_putnbr_base_fd(nbr * -1, "0123456789", FD);
	else
		printed += ft_putnbr_base_fd(nbr, "0123456789", FD);
	return (printed);
}
