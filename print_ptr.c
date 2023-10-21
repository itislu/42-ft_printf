#include "ft_printf.h"

static int	ptrlen(size_t ptr);
static int	puthex_fd(size_t nbr);

int	print_ptr(size_t ptr, t_struct *format)
{
	int	len;
	int	printed;

	if (!ptr)
		len = ft_strlen(NULL_PRINTOUT_P);
	else
		len = ptrlen(ptr) + 2;
	printed = 0;
	if (!format->minus && len < format->width)
		printed += ft_putnchar_fd(' ', format->width - len, FD);
	if (!ptr)
		printed += ft_putnstr_fd(NULL_PRINTOUT_P, len, FD);
	else
	{
		printed += ft_putnstr_fd("0x", 2, FD);
		printed += puthex_fd(ptr);
	}
	if (format->minus && len < format->width)
		printed += ft_putnchar_fd(' ', format->width - len, FD);
	return (printed);
}

static int	ptrlen(size_t ptr)
{
	int	len;

	len = 0;
	while (ptr)
	{
		ptr /= 16;
		len++;
	}
	return (len);
}

static int	puthex_fd(size_t nbr)
{
	int	printed;

	printed = 0;
	if (nbr >= 16)
		printed += puthex_fd(nbr / 16);
	nbr %= 16;
	if (nbr >= 10)
		printed += ft_putnchar_fd(nbr - 10 + 'a', 1, FD);
	else
		printed += ft_putnchar_fd(nbr + '0', 1, FD);
	return (printed);
}

/*
	format->minus = 0;
	format->width = 0;

// Has no effect
	format->zero = 0;	// would place the zeros between the 0x and the address, but that's undefined behaviour
	format->plus = 0;	// would always place a + before 0x
	format->space = 0;
	format->hash = 0;
	format->precision = -1;	// pads with zeros between 0x and the address, but it's undefined behaviour
*/