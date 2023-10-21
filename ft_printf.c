#include "ft_printf.h"

static void	reset_format(t_struct *f);
static int	parseandprint(const char *format, int *i, t_struct *f, va_list *ap);
static int	print_argument(t_struct *f, va_list *ap);

int	ft_printf(const char *format, ...)
{
	int			i;
	int			printed;
	int			temp;
	t_struct	f;
	va_list		ap;

	if (format == NULL)
		return (-1);
	va_start(ap, format);
	f.unresolved = 0;
	printed = 0;
	i = 0;
	while (format[i])
	{
		reset_format(&f);
		temp = parseandprint(format, &i, &f, &ap);
		if (temp == -1)
		{
			printed = temp;
			break ;
		}
		printed += temp;
	}
	va_end(ap);
	return (printed);
}

static void	reset_format(t_struct *f)
{
	f->hash = 0;
	f->plus = 0;
	f->space = 0;
	f->minus = 0;
	f->zero = 0;
	f->width = 0;
	f->precision = NOT_SET;
	f->specifier = '\0';
	return ;
}

static int	parseandprint(const char *format, int *i, t_struct *f, va_list *ap)
{
	int	printed;
	size_t	parsed;

	printed = 0;
	parsed = 1;
	if (format[(*i)++] == '%')
	{
		parsed += set_format(format, i, f, ap);
		if (format[*i] == '\0' && !f->specifier && !f->unresolved)
			return (-1);
		if (f->specifier)
			printed += print_argument(f, ap);
	}
	if (!f->specifier)
		printed += print_parsed(&format[*i - parsed], parsed, f);
	return (printed);
}

/* Calls the appropriate function to print the type of current argument */
static int	print_argument(t_struct *f, va_list *ap)
{
	int	printed;

	printed = 0;
	if (f->specifier == 'c')
		printed = print_char(va_arg(*ap, int), f);
	else if (f->specifier == 's')
		printed = print_str(va_arg(*ap, const char *), f);
	else if (f->specifier == 'p')
		printed = print_ptr(va_arg(*ap, size_t), f); // size_t or void *
	else if (f->specifier == 'd' || f->specifier == 'i')
		printed = print_nbr((long) va_arg(*ap, int), f);
	else if (f->specifier == 'u')
		printed = print_nbr((long) va_arg(*ap, unsigned int), f);
	else if (f->specifier == 'x' || f->specifier == 'X')
		printed = print_nbr(va_arg(*ap, unsigned int), f);
	else if (f->specifier == '%')
		printed = ft_putnchar_fd('%', 1, FD);
	return (printed);
}
