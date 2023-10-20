#include "ft_printf.h"

static int	print(const char *str, int len, t_format *format);

int	print_str(const char *str, t_format *format)
{
	int	len;
	int	printed;

	printed = 0;
	if (!str)
	{
		len = ft_strlen(NULL_PRINTOUT_S);
		if (format->precision != -1 && len > format->precision)
			len = 0;
		printed += print(NULL_PRINTOUT_S, len, format);
	}
	else
	{
		len = ft_strlen(str);
		if (format->precision != -1 && len > format->precision)
			len = format->precision;
		printed += print(str, len, format);
	}
	return (printed);
}

static int	print(const char *str, int len, t_format *format)
{
	int	printed;

	printed = 0;
	if (!format->minus && len < format->width)
		printed += ft_putnchar_fd(' ', format->width - len, FD);
	printed += ft_putnstr_fd((char *) str, len, FD);
	if (format->minus && len < format->width)
		printed += ft_putnchar_fd(' ', format->width - len, FD);
	return (printed);
}

/*
	format->minus = 0;
	format->width = 0;			// How many characters to be printed alltogether at least
	format->precision = -1;	// How many characters of string itself to be printed at most

// Has no effect
	format->zero = 0;
	format->plus = 0;
	format->space = 0;
	format->hash = 0;
*/

/*
if (format->minus)
	{
		while (i < len)
		{
			ft_putchar_fd(str[i], 1);
			printed++;
			i++;
		}
		while (printed < format->width)
		{
			ft_putchar_fd(' ', 1);
			printed++;
		}
	}
	else
	{
		while (printed < format->width - len)
		{
			ft_putchar_fd(' ', 1);
			printed++;
		}
		while (i < len)
		{
			ft_putchar_fd(str[i], 1);
			printed++;
			i++;
		}
	}
*/