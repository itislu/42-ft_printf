#include "ft_printf.h"

static void	set_flags(const char *format, int *i, t_struct *f);
static void	set_width(const char *format, int *i, t_struct *f, va_list *ap);
static void	set_precision(const char *format, int *i, t_struct *f, va_list *ap);
static void	set_specifier(const char *format, int *i, t_struct *f);

size_t	set_format(const char *format, int *i, t_struct *f, va_list *ap)
{
	int	i_original;

	i_original = *i;
	set_flags(format, i, f);
	set_width(format, i, f, ap);
	set_precision(format, i, f, ap);
	set_specifier(format, i, f);
	return (*i - i_original);
}

static void	set_flags(const char *format, int *i, t_struct *f)
{
	while (1)
	{
		if (format[*i] == '#')
			f->hash = 1;
		else if (format[*i] == '+')
			f->plus = 1;
		else if (format[*i] == ' ')
			f->space = 1;
		else if (format[*i] == '-')
			f->minus = 1;
		else if (format[*i] == '0')
			f->zero = 1;
		else
			return ;
		(*i)++;
	}
}

static void	set_width(const char *format, int *i, t_struct *f, va_list *ap)
{
	int	nbr;

	nbr = 0;
	if (format[*i] == '*')
	{
		nbr = va_arg(*ap, int);
		if (nbr < 0)
		{
			if (!f->minus)
				f->minus = FROM_NEGATIVE_WIDTH;
			nbr *= -1;
		}
		(*i)++;
	}
	else
	{
		while (ft_isdigit(format[*i]))
		{
			nbr = nbr * 10 + (format[*i] - '0');
			(*i)++;
		}
	}
	f->width = nbr;
	return ;
}

static void	set_precision(const char *format, int *i, t_struct *f, va_list *ap)
{
	int	nbr;

	if (format[*i] == '.')
	{
		nbr = 0;
		(*i)++;
		if (format[*i] == '*')
		{
			nbr = va_arg(*ap, int);
			if (nbr < 0)
				nbr = NEGATIVE_PRECISION;
			(*i)++;
		}
		else
		{
			while (ft_isdigit(format[*i]))
			{
				nbr = nbr * 10 + (format[*i] - '0');
				(*i)++;
			}
		}
		f->precision = nbr;
	}
	return ;
}

static void	set_specifier(const char *format, int *i, t_struct *f)
{
	// Potentially put into header file as global variable
	//const char	*specifiers = "cspdiuxX%";
	//int		j;
	char	*specifier;

	specifier = ft_strchr("cspdiuxX%", format[*i]);
	if (specifier && *specifier)
	{
		f->specifier = *specifier;
		(*i)++;
	}
	// j = 0;
	// while (specifiers[j] != format[*i] && specifiers[j])
	// 	j++;
	// f->specifier = specifiers[j];
	// if (f->specifier)
	// 	(*i)++;
	else if (format[*i])
		f->unresolved = 1;
	return ;
}