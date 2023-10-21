#include "ft_printf.h"

int	print_char(char c, t_struct *f)
{
	int	printed;

	printed = 0;
	if (!f->minus && f->width > 1)
		printed += ft_putnchar_fd(' ', f->width - 1, FD);
	printed += ft_putnchar_fd(c, 1, FD);
	if (f->minus && f->width > 1)
		printed += ft_putnchar_fd(' ', f->width - 1, FD);
	return (printed);
}
