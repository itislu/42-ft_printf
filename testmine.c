#include "ft_printf.h"
#include <stdarg.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char function_argtype_test(char c)
{
	return (c);
}

void f(char *format, ...)
{
	va_list t;

	va_start(t, format);
	char c;
	//int	i = 1000;
	c = function_argtype_test((int) va_arg(t, int));
	//c = (int) c;
	printf("sizeof:	%lu\n", sizeof(c));
	printf("c:	%c\n", c);
	printf("d:	%d", (int) c);
	//printf("%c\n", c);
}

int	test_ft_printf(void)
{

	int		i = -10;
	char	*a = 1;
	return (ft_printf("%+028.*pw",-16, a));
}

int	test_printf(void)
{

	int		i = -10;
	char	*a = 1;
	return (printf("%+028.*pw",-16, a));
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


	//void	*ptr = NULL;
	//int	result;

	//printf("|%0.00013|\n");
	//printf("|% .0s|\n", ptr);
	//printf("|%- #0+20.16u|\n", 20);
	//result = printf("|%- 0-0#0|\n");
	//printf("|%- #0w%%w|\n");
	//printf("|%.10%|\n");
	//printf("|%-10.1s|\n", "sring");
	//const char *const_str = "const_string";
	//printf("%s\n", const_str);
	//const char *str;
	//str = malloc(5);
	//str[0] = 't';
	//str[1] = '\0';
	//printf("%p\n", str);
	//printf("%p\n", "id");
	//f("A", 1000);

	//int i = 1;
	//printf("|");
	//int	result;
	//result = printf("'   %");
	//printf("|");

	//result = printf("%..i", 5);

	//printf("\nreturned: %i\n", result);
}

/*

"%0*.*iw", 10, -5, -10
"%+ 0#*.*w",-40, -10
"%0*+iw", -8		// The minus from neg. width behaves slightly different
"%s"
"%25.33p", p

Asterisk:
"%*.3w", 5
"%.*.3w", 5


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