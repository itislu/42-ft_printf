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
	int			printed_count;
	int			temp;
	t_format	format;
	va_list		arg_ptr;

	if (f_str == NULL)
		return (-1);
	va_start(arg_ptr, f_str);
	printed_count = 0;
	i = 0;
	while (f_str[i])
	{
		reset_format(&format);
		temp = parser(f_str, &i, &format, &arg_ptr);
		if (temp == -1)
		{
			printed_count = temp;
			break ;
		}
		printed_count += temp;
	}
	va_end(arg_ptr);
	return (printed_count);
}

void	reset_format(t_format *format)
{
	format -> minus = 0;
	format -> zero = 0;
	format -> plus = 0;
	format -> space = 0;
	format -> hash = 0;
	format -> width = 0;
	format -> precision = -1;
	format -> specifier = '\0';
	return ;
}

int	parser(const char *f_str, int *i, t_format *format, va_list *arg_ptr)
{
	int	printed_count;
	ssize_t	parsed_count;

	printed_count = 0;
	parsed_count = 1;
	if (f_str[*i] == '%')
	{
		parsed_count = set_format(f_str, i, format);
		if (parsed_count == 0)
			return (-1);
		if (format -> specifier)
			printed_count += print_argument(format, arg_ptr);
	}
	if (!format -> specifier)
	{
		if (format -> precision == 0)
		{
			printed_count += ft_putnstr_fd_dotzero(&f_str[*i - parsed_count], parsed_count, 1);
		}
		else
		{
			printed_count += ft_putnstr_fd(&f_str[*i], parsed_count, 1);
			(*i)++;
		}
	}
	return (printed_count);
}

/*-- Alternative to is_valid_specifier() that already sets the format ----*/
size_t	set_format(const char *f_str, int *i, t_format *format)
{
	int	i_original;
	//size_t	parsed_count;

	i_original = *i;
	(*i)++;
	set_flags(f_str, i, format);
	set_width(f_str, i, format);
	set_precision(f_str, i, format);
	if (f_str[*i] == '\0')
		return (0);
	set_specifier(f_str, i, format);
	if (format -> specifier || format -> precision == 0)
	{
		(*i)++;
		return (*i - i_original);
	}
	else
	{
		*i = i_original;
		return (1);
	}
}

void	set_flags(const char *f_str, int *i, t_format *format)
{
	while (1)
	{
		if (f_str[*i] == '-')
			format -> minus = 1;
		else if (f_str[*i] == '0')
			format -> zero = 1;
		else if (f_str[*i] == '+')
			format -> plus = 1;
		else if (f_str[*i] == ' ')
			format -> space = 1;
		else if (f_str[*i] == '#')
			format -> hash = 1;
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
	format -> width = nbr;
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
		format -> precision = nbr;
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
	format -> specifier = specifiers[j];
	return ;
}

/* Calls the appropriate function to print the type of current argument */
// Change name of function to call_print()
int	print_argument(t_format *format, va_list *arg_ptr)
{
	int	printed_count;

	printed_count = 0;
	if (format -> specifier == 'c')
		printed_count = print_char(va_arg(*arg_ptr, int), format);
	else if (format -> specifier == 's')
		printed_count = print_str(va_arg(*arg_ptr, const char *), format);
	else if (format -> specifier == 'p')
		printed_count = print_ptr(va_arg(*arg_ptr, size_t), format); // size_t or void *
	else if (format -> specifier == 'd' || format -> specifier == 'i')
		printed_count = print_nbr((long) va_arg(*arg_ptr, int), format);
	else if (format -> specifier == 'u')
		printed_count = print_nbr((long) va_arg(*arg_ptr, unsigned int), format);
	else if (format -> specifier == 'x' || format -> specifier == 'X')
		printed_count = print_nbr(va_arg(*arg_ptr, unsigned int), format);
	else if (format -> specifier == '%')
		printed_count = ft_putnchar_fd('%', 1, 1);
	return (printed_count);
}

/*--------------------is_valid_specifier------------------------------*/

/* Checks the f_str string further if it is a valid f_str specifier */
// Change to adjusting pointer instead of index
/*int	is_valid_specifier(const char *f_str, int i)
{
	// flags
	while (is_flag(f_str[i]))
		i++;
	// width
	while (ft_isdigit(f_str[i]))
		i++;
	// precision
	if (f_str[i] == '.')
	{
		i++;
		while (ft_isdigit(f_str[i]))
			i++;
	}
	// specifier
	if (is_specifier(f_str[i]))
		return (1);
	else
		return (0);
}

// Combine with is_specifier() -> is_in_str()
int	is_flag(const char c)
{
	// Potentially put into header file as global variable
	const char	*flags;

	flags = "-0+ #";
	while (*flags)
	{
		if (c == *flags)
			return (1);
		flags++;
	}
	return (0);
}

int	is_specifier(const char c)
{
	// Potentially put into header file as global variable
	const char	*specifiers = "cspdiuxX%";

	while (*specifiers)
	{
		if (c == *specifiers)
			return (1);
		specifiers++;
	}
	return (0);
}*/
/*--------------------------------------------------------------------*/

/* Sets the va_??? type */
// Possibly just print the argument directly here?
/*void	set_type(va_list *arg_ptr, t_format *format)
{

}*/

/*
int	main(void)
{
	int	ft_return;
	int	og_return;

	//char	c = 0;
	//char	*str = (char *)c;
	int		i = 500000;
	//int		j = -1;

	ft_printf("ft: |");
	ft_return = ft_printf("%.-i%.-i", i);
	printf("|\nog: |");
	og_return = printf("%.-i%.-i", i);
	printf("|");

	printf("\nft_return: %d\nog_return: %d\n", ft_return, og_return);
}
*/
/*
Tests to be done:
"'   %"
"%"
" %"
" % "
"%% % "
"%.-i%.-i", i

"%% %  wtest"
*/