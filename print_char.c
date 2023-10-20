#include "ft_printf.h"

int	print_char(char c, t_format *format)
{
	int	printed;

	printed = 0;
	if (!format->minus && format->width > 1)
		printed += ft_putnchar_fd(' ', format->width - 1, FD);
	printed += ft_putnchar_fd(c, 1, FD);
	if (format->minus && format->width > 1)
		printed += ft_putnchar_fd(' ', format->width - 1, FD);
	return (printed);
}

/*
	format->minus = 0;
	format->width = 0;

// Has no effect
	format->precision = -1;
	format->zero = 0;
	format->plus = 0;
	format->space = 0;
	format->hash = 0;
*/

/*
	if (format->minus)
	{
		printed += ft_putnchar_fd(c, 1, 1);
		if (printed < format->width)
			printed += ft_putnchar_fd(' ', format->width - 1, 1);
	}
	else
	{
		if (format->width > 1)
			printed += ft_putnchar_fd(' ', format->width - 1, 1);
		printed += ft_putnchar_fd(c, 1, 1);
	}
*/