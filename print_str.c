#include "ft_printf.h"

static int	print(const char *str, int len, t_format *format);

int	print_str(const char *str, t_format *format)
{
	int	len;
	int	printed_count;

	printed_count = 0;
	if (!str)
	{
		len = ft_strlen(NULL_PRINTOUT_S);
		if (format -> precision != -1 && len > format -> precision)
			len = 0;
		printed_count += print(NULL_PRINTOUT_S, len, format);
	}
	else
	{
		len = ft_strlen(str);
		if (format -> precision != -1 && len > format -> precision)
			len = format -> precision;
		printed_count += print(str, len, format);
	}
	return (printed_count);
}

static int	print(const char *str, int len, t_format *format)
{
	int	printed_count;

	printed_count = 0;
	if (!format -> minus && len < format -> width) // Possibly parentheses needed
		printed_count += ft_putnchar_fd(' ', format -> width - len, 1);
	printed_count += ft_putnstr_fd((char *) str, len, 1);
	if (format -> minus && len < format -> width)
		printed_count += ft_putnchar_fd(' ', format -> width - len, 1);
	return (printed_count);
}

/*
	format -> minus = 0;
	format -> width = 0;			// How many characters to be printed alltogether at least
	format -> precision = -1;	// How many characters of string itself to be printed at most

// Has no effect
	format -> zero = 0;
	format -> plus = 0;
	format -> space = 0;
	format -> hash = 0;
*/

/*
if (format -> minus)
	{
		while (i < len)
		{
			ft_putchar_fd(str[i], 1);
			printed_count++;
			i++;
		}
		while (printed_count < format -> width)
		{
			ft_putchar_fd(' ', 1);
			printed_count++;
		}
	}
	else
	{
		while (printed_count < format -> width - len)
		{
			ft_putchar_fd(' ', 1);
			printed_count++;
		}
		while (i < len)
		{
			ft_putchar_fd(str[i], 1);
			printed_count++;
			i++;
		}
	}
*/