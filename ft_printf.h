#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <unistd.h>

#include <stdio.h>	// DELETE

# ifndef FD
#  define FD 1
# endif
# ifndef NULL_PRINTOUT_P
#  define NULL_PRINTOUT_P "(nil)"
# endif
# ifndef NULL_PRINTOUT_S
#  define NULL_PRINTOUT_S "(null)"
# endif

typedef struct s_format
{
	int		hash;
	int		plus;
	int		space;
	int		minus;
	int		zero;
	int		width;
	int		precision;
	char	specifier;
	int		unresolved;
}	t_format;

// functions here
int				ft_printf(const char *f_str, ...);
unsigned int	ft_putnbr_base_fd(long n, const char *base, int fd);
size_t			ft_putnchar_fd(char c, size_t n, int fd);
size_t			ft_putnstr_fd(const char *s, size_t n, int fd);
int				print_char(char c, t_format *format);
int				print_nbr(long nbr, t_format *format);
size_t			print_parsed(const char *s, size_t parsed, t_format *format);
int				print_ptr(size_t ptr, t_format *format);
int				print_str(const char *str, t_format *format);

#endif
