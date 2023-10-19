/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_tests.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 13:07:10 by ldulling          #+#    #+#             */
/*   Updated: 2023/10/16 11:59:50 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>

/*
You have to implement the following conversions:
• %c Prints a single character.
• %s Prints a string (as defined by the common C convention).
• %p The void * pointer argument has to be printed in hexadecimal format.
• %d Prints a decimal (base 10) number.
• %i Prints an integer in base 10.
• %u Prints an unsigned decimal (base 10) number.
• %x Prints a number in hexadecimal (base 16) lowercase format.
• %X Prints a number in hexadecimal (base 16) uppercase format.
• %% Prints a percent sign.

Bonus:
• Manage any combination of the following flags: ’-0.’ and the field minimum width under all conversions.
• Manage all the following flags: ’# +’ (Yes, one of them is a space)
*/

// %[flags][width][.precision][length]
/*int	ft_printf(const char *format, ...)
{

}
*/



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

void	ito3(int **i)
{
	**i = 3;
}

void	ito2(int *i)
{
	*i = 2;
	ito3(&i);
}

int	ito1(void)
{
	int i = 1;
	ito2(&i);
	return (i);
}
/*
int	main(void)
{
	//void	*ptr = NULL;
	int	result;

	printf("|%0.00013|\n");
	//printf("|% .0s|\n", ptr);
	//printf("|%- #0+20.16u|\n", 20);
	result = printf("|%- 0-0#0|\n");
	printf("|%- #0w%%w|\n");
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
	printf("\nreturned: %i\n", result);
}
*/