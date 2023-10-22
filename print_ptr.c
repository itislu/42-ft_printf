#include "ft_printf.h"

static int	print_nil(t_struct *f);
static int	ptrlen(size_t ptr);
static int	totalptrlen(size_t ptr, int len_ptr, t_struct *f);

int	print_ptr(size_t ptr, t_struct *f)
{
	int		len_ptr;
	int		len_totalptr;
	int		printed;

	printed = 0;
	if (!ptr)
		printed += print_nil(f);
	else
	{
		len_ptr = ptrlen(ptr);	// now is 2 smaller
		len_totalptr = totalptrlen(ptr, len_ptr, f);
		if (!f->minus && len_totalptr < f->width)
			printed += ft_putnchar_fd(' ', f->width - len_totalptr, FD);
		if (f->plus)
			printed += ft_putnchar_fd('+', 1, FD);
		else if (f->space)
			printed += ft_putnchar_fd(' ', 1, FD);
		printed += ft_putnstr_fd("0x", 2, FD);
		if (f->precision > len_ptr)
			printed += ft_putnchar_fd('0', f->precision - len_ptr, FD);
		printed += ft_putnbr_base_fd(ptr, "0123456789abcdef", FD);
		if (f->minus && len_totalptr < f->width)
			printed += ft_putnchar_fd(' ', f->width - len_totalptr, FD);
	}
	return (printed);
}

static int	print_nil(t_struct *f)
{
	int	len;
	int	printed;

	len = ft_strlen(NULL_PRINTOUT_PTR);
	printed = 0;
	if (!f->minus && len < f->width)
		printed += ft_putnchar_fd(' ', f->width - len, FD);
	printed += ft_putnstr_fd(NULL_PRINTOUT_PTR, len, FD);
	if (f->minus && len < f->width)
		printed += ft_putnchar_fd(' ', f->width - len, FD);
	return (printed);
}

static int	ptrlen(size_t ptr)
{
	int	len_ptr;

	len_ptr = 0;
	while (ptr)
	{
		ptr /= 16;
		len_ptr++;
	}
	return (len_ptr);
}

static int	totalptrlen(size_t ptr, int len_ptr, t_struct *f)
{
	int	len_totalptr;

	len_totalptr = len_ptr;
	if (len_totalptr < f->precision)
		len_totalptr = f->precision;
	if (f->plus || f->space)
		len_totalptr++;
	len_totalptr += ft_strlen("0x");
	return (len_totalptr);
}

/*
	f->minus = 0;
	f->width = 0;

// Has no effect
	f->zero = 0;	// would place the zeros between the 0x and the address, but that's undefined behaviour
	f->plus = 0;	// would always place a + before 0x
	f->space = 0;
	f->hash = 0;
	f->precision = -1;	// pads with zeros between 0x and the address, but it's undefined behaviour
*/