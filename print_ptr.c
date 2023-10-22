#include "ft_printf.h"

static int	print_nil(t_struct *f);
static int	ptrlen(size_t ptr);
static int	totalptrlen(int len_ptr, t_struct *f);
static int	puthex(size_t ptr);

int	print_ptr(size_t ptr, t_struct *f)
{
	int		len_ptr;
	int		len_totalptr;
	int		printed;

	printed = 0;
	if (!ptr)
		return (printed += print_nil(f));
	len_ptr = ptrlen(ptr);	// If necessary, use pointers and just 1 function
	len_totalptr = totalptrlen(len_ptr, f);
	if (!f->minus && f->width > len_totalptr && !(f->zero && f->precision < 0))
		printed += ft_putnchar_fd(' ', f->width - len_totalptr, FD);
	if (f->plus)
		printed += ft_putnchar_fd('+', 1, FD);
	else if (f->space)
		printed += ft_putnchar_fd(' ', 1, FD);
	printed += ft_putnstr_fd("0x", 2, FD);
	if (f->precision > len_ptr)
		printed += ft_putnchar_fd('0', f->precision - len_ptr, FD);
	else if (f->zero && !f->minus && f->precision < 0 && f->width > len_totalptr)
		printed += ft_putnchar_fd('0', f->width - len_totalptr, FD);
	printed += puthex(ptr);
	if (f->minus && f->width > len_totalptr)
		printed += ft_putnchar_fd(' ', f->width - len_totalptr, FD);
	return (printed);
}

static int	print_nil(t_struct *f)
{
	int	len;
	int	printed;

	len = ft_strlen(NULL_PRINTOUT_PTR);
	printed = 0;
	if (!f->minus && f->width > len)
		printed += ft_putnchar_fd(' ', f->width - len, FD);
	printed += ft_putnstr_fd(NULL_PRINTOUT_PTR, len, FD);
	if (f->minus && f->width > len)
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

static int	totalptrlen(int len_ptr, t_struct *f)
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

static int	puthex(size_t ptr)
{
	int	printed;

	printed = 0;
	if (ptr >= 16)
		printed += puthex(ptr / 16);
	ptr %= 16;
	if (ptr >= 10)
		printed += ft_putnchar_fd(ptr - 10 + 'a', 1, FD);
	else
		printed += ft_putnchar_fd(ptr + '0', 1, FD);
	return (printed);
}
