#include "ft_printf.h"

static int	ptrlen(size_t ptr);
static int	puthex_fd(size_t nbr, int fd);

int	print_ptr(size_t ptr, t_format *format)
{
	int	len;
	int	printed_count;

	if (!ptr)
		len = ft_strlen(NULL_PRINTOUT_P);
	else
		len = ptrlen(ptr) + 2;
	printed_count = 0;
	if (!format -> minus && len < format -> width) // Possibly parentheses needed
		printed_count += ft_putnchar_fd(' ', format -> width - len, 1);
	if (!ptr)
		printed_count += ft_putnstr_fd(NULL_PRINTOUT_P, len, 1);
	else
	{
		printed_count += ft_putnstr_fd("0x", 2, 1);
		printed_count += puthex_fd(ptr, 1);
	}
	if (format -> minus && len < format -> width)
		printed_count += ft_putnchar_fd(' ', format -> width - len, 1);
	return (printed_count);
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

static int	puthex_fd(size_t nbr, int fd)
{
	int	printed_count;

	printed_count = 0;
	if (nbr >= 16)
		printed_count += puthex_fd(nbr / 16, fd);
	nbr %= 16;
	if (nbr >= 10)
		printed_count += ft_putnchar_fd(nbr - 10 + 'a', 1, fd);
	else
		printed_count += ft_putnchar_fd(nbr + '0', 1, fd);
	return (printed_count);
}

/*
	format -> minus = 0;
	format -> width = 0;

// Has no effect
	format -> zero = 0;	// would place the zeros between the 0x and the address, but that's undefined behaviour
	format -> plus = 0;	// would always place a + before 0x
	format -> space = 0;
	format -> hash = 0;
	format -> precision = -1;	// pads with zeros between 0x and the address, but it's undefined behaviour
*/