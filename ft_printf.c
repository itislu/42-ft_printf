#include "ft_printf.h"

static void	reset_format(t_struct *format);
static int	parseandprint(const char *f_str, int *i, t_struct *format, va_list *ap);
static int		print_argument(t_struct *format, va_list *ap);

int	ft_printf(const char *f_str, ...)
{
	int			i;
	int			printed;
	int			temp;
	t_struct	format;
	va_list		ap;

	if (f_str == NULL)
		return (-1);
	va_start(ap, f_str);
	format.unresolved = 0;
	printed = 0;
	i = 0;
	while (f_str[i])
	{
		reset_format(&format);
		temp = parseandprint(f_str, &i, &format, &ap);
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

static void	reset_format(t_struct *format)
{
	format->hash = 0;
	format->plus = 0;
	format->space = 0;
	format->minus = 0;
	format->zero = 0;
	format->width = 0;
	format->precision = -1;
	format->specifier = '\0';
	return ;
}

static int	parseandprint(const char *f_str, int *i, t_struct *format, va_list *ap)
{
	int	printed;
	size_t	parsed;

	printed = 0;
	parsed = 1;
	if (f_str[(*i)++] == '%')
	{
		parsed += set_format(f_str, i, format, ap);
		if (f_str[*i] == '\0' && !format->specifier && !format->unresolved)
			return (-1);
		if (format->specifier)
			printed += print_argument(format, ap);
	}
	if (!format->specifier)
		printed += print_parsed(&f_str[*i - parsed], parsed, format);
	return (printed);
}

/* Calls the appropriate function to print the type of current argument */
// Change name of function to call_print()
static int	print_argument(t_struct *format, va_list *ap)
{
	int	printed;

	printed = 0;
	if (format->specifier == 'c')
		printed = print_char(va_arg(*ap, int), format);
	else if (format->specifier == 's')
		printed = print_str(va_arg(*ap, const char *), format);
	else if (format->specifier == 'p')
		printed = print_ptr(va_arg(*ap, size_t), format); // size_t or void *
	else if (format->specifier == 'd' || format->specifier == 'i')
		printed = print_nbr((long) va_arg(*ap, int), format);
	else if (format->specifier == 'u')
		printed = print_nbr((long) va_arg(*ap, unsigned int), format);
	else if (format->specifier == 'x' || format->specifier == 'X')
		printed = print_nbr(va_arg(*ap, unsigned int), format);
	else if (format->specifier == '%')
		printed = ft_putnchar_fd('%', 1, FD);
	return (printed);
}

/*
int	test_ft_printf(void)
{
	return (ft_printf("%0-.w11.1.%.00003...i"));
}

int	test_printf(void)
{
	return (printf("%0-.w11.1.%.00003...i"));
}

int	main(void)
{
	int	ft_return;
	int	og_return;

	//char	c = 0;
	//char	*str = (char *)c;
	//int		i = 500000;
	//int		j = -1;

	ft_printf("ft: |");
	ft_return = test_ft_printf();
	printf("|\nog: |");
	og_return = test_printf();
	printf("|");

	printf("\nft_return: %d\nog_return: %d\n", ft_return, og_return);
}
*/
/*
Not multiple flags printed:
"w%%  % % %% w%  w  w%"
"%  +   .-.%+   "


Tests to be done:
"'   %"
"%"
" %"
" % "
"%.-i%.-i", i
"w%%  % w %% wwwww% ."


"w%% % "

"%w%"
"%w% "
"%ww%"

"w%w% w"


"%   w"
"%% %  wtest"

"wwwww% w% w%"
"%% %  wtest %"
"w%%  % % %% w%  w%  w"


-1:
"w%%  % % %% w%i  w  w%"
"%% w% "
"%% % "


skip zeros:
"%0-.w11.1.%.00003...i"
*/