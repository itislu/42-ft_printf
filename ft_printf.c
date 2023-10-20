#include "ft_printf.h"

void	reset_format(t_format *format);
int		parser(const char *f_str, int *i, t_format *format, va_list *arg_ptr);
size_t	set_format(const char *f_str, int *i, t_format *format);
void	set_flags(const char *f_str, int *i, t_format *format);
void	set_width(const char *f_str, int *i, t_format *format);
void	set_precision(const char *f_str, int *i, t_format *format);
void	set_specifier(const char *f_str, int *i, t_format *format);
int		print_argument(t_format *format, va_list *arg_ptr);

int	ft_printf(const char *f_str, ...)
{
	int			i;
	int			printed;
	int			temp;
	t_format	format;
	va_list		arg_ptr;

	if (f_str == NULL)
		return (-1);
	va_start(arg_ptr, f_str);
	format.unresolved = 0;
	printed = 0;
	i = 0;
	while (f_str[i])
	{
		reset_format(&format);
		temp = parser(f_str, &i, &format, &arg_ptr);
		if (temp == -1)
		{
			printed = temp;
			break ;
		}
		printed += temp;
	}
	va_end(arg_ptr);
	return (printed);
}

void	reset_format(t_format *format)
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

int	parser(const char *f_str, int *i, t_format *format, va_list *arg_ptr)
{
	int	printed;
	size_t	parsed;

	printed = 0;
	parsed = 1;
	if (f_str[(*i)++] == '%')
	{
		parsed += set_format(f_str, i, format);
		if (f_str[*i] == '\0' && !format->specifier && !format->unresolved)
			return (-1);
		if (format->specifier)
			printed += print_argument(format, arg_ptr);
	}
	if (!format->specifier)
	{
		// Here it should print the up to 3 flags
		// Then only anything after the flags
		printed += print_parsed(&f_str[*i - parsed], parsed, format);
	}
	//(*i) += parsed;
	return (printed);
}

/*-- Alternative to is_valid_specifier() that already sets the format ----*/
size_t	set_format(const char *f_str, int *i, t_format *format)
{
	int	i_original;
	//size_t	parsed;

	i_original = *i; // Needed in case of % at the very end
	set_flags(f_str, i, format);
	set_width(f_str, i, format);
	set_precision(f_str, i, format);
	// if last & uneven amount of % & no previous unresolved check function
	set_specifier(f_str, i, format);
	// if (f_str[i] == '\0' && !format->unresolved)
	// 	return (i - i_original);
	// if (!format->specifier)
	// {
	// 	format->unresolved = 1;
	// 	//
	// }
	//if (format->specifier)
		return (*i - i_original);
	//else
	// 	i = i_original; // this should instead be past the flags I think
	// {
	// 	return (1);
	// }
}

void	set_flags(const char *f_str, int *i, t_format *format)
{
	while (1)
	{
		if (f_str[*i] == '#')
			format->hash = 1;
		else if (f_str[*i] == '+')
			format->plus = 1;
		else if (f_str[*i] == ' ')
			format->space = 1;
		else if (f_str[*i] == '-')
			format->minus = 1;
		else if (f_str[*i] == '0')
			format->zero = 1;
		else
			return ;
		(*i)++;
	}
}

void	set_width(const char *f_str, int *i, t_format *format)
{
	int	nbr;

	nbr = 0;
	while (ft_isdigit(f_str[*i]))
	{
		nbr = nbr * 10 + (f_str[*i] - '0');
		(*i)++;
	}
	format->width = nbr;
	return ;
}

// Need to add check for negative number i.e. minus sign
// However, original printf doesn't even work with negative precision
void	set_precision(const char *f_str, int *i, t_format *format)
{
	int	nbr;

	if (f_str[*i] == '.')
	{
		nbr = 0;
		(*i)++;
		while (ft_isdigit(f_str[*i]))
		{
			nbr = nbr * 10 + (f_str[*i] - '0');
			(*i)++;
		}
		format->precision = nbr;
	}
	return ;
}

void	set_specifier(const char *f_str, int *i, t_format *format)
{
	// Potentially put into header file as global variable
	const char	*specifiers = "cspdiuxX%";
	int			j;

	j = 0;
	while (specifiers[j] != f_str[*i] && specifiers[j])
		j++;
	format->specifier = specifiers[j];
	if (format->specifier)
		(*i)++;
	else if (f_str[*i])
		format->unresolved = 1;
	return ;
}

/* Calls the appropriate function to print the type of current argument */
// Change name of function to call_print()
int	print_argument(t_format *format, va_list *arg_ptr)
{
	int	printed;

	printed = 0;
	if (format->specifier == 'c')
		printed = print_char(va_arg(*arg_ptr, int), format);
	else if (format->specifier == 's')
		printed = print_str(va_arg(*arg_ptr, const char *), format);
	else if (format->specifier == 'p')
		printed = print_ptr(va_arg(*arg_ptr, size_t), format); // size_t or void *
	else if (format->specifier == 'd' || format->specifier == 'i')
		printed = print_nbr((long) va_arg(*arg_ptr, int), format);
	else if (format->specifier == 'u')
		printed = print_nbr((long) va_arg(*arg_ptr, unsigned int), format);
	else if (format->specifier == 'x' || format->specifier == 'X')
		printed = print_nbr(va_arg(*arg_ptr, unsigned int), format);
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