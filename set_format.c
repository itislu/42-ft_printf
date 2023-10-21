#include "ft_printf.h"

static void	set_flags(const char *f_str, int *i, t_struct *format);
static void	set_width(const char *f_str, int *i, t_struct *format);
static void	set_precision(const char *f_str, int *i, t_struct *format);
static void	set_specifier(const char *f_str, int *i, t_struct *format);

size_t	set_format(const char *f_str, int *i, t_struct *format)
{
	int	i_original;

	i_original = *i;
	set_flags(f_str, i, format);
	set_width(f_str, i, format);
	set_precision(f_str, i, format);
	set_specifier(f_str, i, format);
	return (*i - i_original);
}

static void	set_flags(const char *f_str, int *i, t_struct *format)
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

static void	set_width(const char *f_str, int *i, t_struct *format)
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

static void	set_precision(const char *f_str, int *i, t_struct *format)
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

static void	set_specifier(const char *f_str, int *i, t_struct *format)
{
	// Potentially put into header file as global variable
	//const char	*specifiers = "cspdiuxX%";
	//int		j;
	char	*specifier;

	specifier = ft_strchr("cspdiuxX%", f_str[*i]);
	if (specifier)
	{
		format->specifier = *specifier;
		(*i)++;
	}
	// j = 0;
	// while (specifiers[j] != f_str[*i] && specifiers[j])
	// 	j++;
	// format->specifier = specifiers[j];
	// if (format->specifier)
	// 	(*i)++;
	else if (f_str[*i])
		format->unresolved = 1;
	return ;
}