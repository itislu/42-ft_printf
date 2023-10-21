#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <unistd.h>

#include <stdio.h>	// DELETE

# ifndef FD
#  define FD 1
# endif
# define NULL_PRINTOUT_PTR "(nil)"
# define NULL_PRINTOUT_STR "(null)"
# define FROM_NEGATIVE_WIDTH 2
# define NOT_SET -1
# define NEGATIVE_PRECISION -2

typedef struct s_struct
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
}	t_struct;

// functions here
int				ft_printf(const char *format, ...);
unsigned int	ft_putnbr_base_fd(long n, const char *base, int fd);
size_t			ft_putnchar_fd(char c, size_t n, int fd);
size_t			ft_putnstr_fd(const char *s, size_t n, int fd);
int				print_char(char c, t_struct *f);
int				print_nbr(long nbr, t_struct *f);
size_t			print_parsed(const char *format, size_t parsed, t_struct *f);
int				print_ptr(size_t ptr, t_struct *f);
int				print_str(const char *str, t_struct *f);
size_t			set_format(const char *format, int *i, t_struct *f, va_list *ap);

#endif
