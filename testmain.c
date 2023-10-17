#include "ft_printf.h"
#include <stdio.h>
#include <string.h>

int	ft_printf(const char *f_str, ...);
void	reset_format(t_format *format);
int	parser(const char *f_str, int *i, t_format *format, va_list *arg_ptr);
size_t	set_format(const char *f_str, int *i, t_format *format);
void	set_flags(const char *f_str, int *i, t_format *format);
void	set_width(const char *f_str, int *i, t_format *format);
void	set_precision(const char *f_str, int *i, t_format *format);
void	set_specifier(const char *f_str, int *i, t_format *format);
int	print_argument(t_format *format, va_list *arg_ptr);

static void passt_da_des_eh(int a, int b)
{
	if (a == b)
		printf("\e[38;2;0;255;0mPASST\e[0m\n\n");
	else
		printf("\e[38;2;255;0;0mPASST NET: %d != %d\e[0m\n\n", a, b);
}

int main(void)
{
	char *format;
	char *string;
	char character;
	int num;
	int lft;
	int lorig;
	ft_printf(format, 1, 2, 3);

	// PAUL TESTS

	puts("=== Character: %c ===");
	format = "%c\n";
	character = 'A';
	lft = ft_printf(format, character);
	lorig = printf(format, character);
	passt_da_des_eh(lft, lorig);
	character = 'B';
	lft = ft_printf(format, character);
	lorig = printf(format, character);
	passt_da_des_eh(lft, lorig);

	puts("=== String: %s ===");
	format = "%s\n";
	string = NULL;
	lft = ft_printf(format, string);
	lorig = printf(format, string);
	passt_da_des_eh(lft, lorig);
	string = "Hello I am a String";
	lft = ft_printf(format, string);
	lorig = printf(format, string);
	passt_da_des_eh(lft, lorig);

	puts("\n=== Integer: %d ===");
	format = "%d\n";
	num = 0;
	lft = ft_printf(format, num);
	lorig = printf(format, num);
	passt_da_des_eh(lft, lorig);
	num = 42;
	lft = ft_printf(format, num);
	lorig = printf(format, num);
	passt_da_des_eh(lft, lorig);
	num = -42;
	lft = ft_printf(format, num);
	lorig = printf(format, num);
	passt_da_des_eh(lft, lorig);
	num = 2147483647;
	lft = ft_printf(format, num);
	lorig = printf(format, num);
	passt_da_des_eh(lft, lorig);
	num = -2147483648;
	lft = ft_printf(format, num);
	lorig = printf(format, num);
	passt_da_des_eh(lft, lorig);

	puts("\n=== Hexa lower-Cased: %x ===");
	format = "%x\n";
	num = 0;
	lft = ft_printf(format, num);
	lorig = printf(format, num);
	passt_da_des_eh(lft, lorig);
	num = 42;
	lft = ft_printf(format, num);
	lorig = printf(format, num);
	passt_da_des_eh(lft, lorig);
	num = -42;
	lft = ft_printf(format, num);
	lorig = printf(format, num);
	passt_da_des_eh(lft, lorig);
	num = 2147483647;
	lft = ft_printf(format, num);
	lorig = printf(format, num);
	passt_da_des_eh(lft, lorig);
	num = -2147483648;
	lft = ft_printf(format, num);
	lorig = printf(format, num);
	passt_da_des_eh(lft, lorig);

	puts("\n=== Hexa UPPER-CASED: %X ===");
	format = "%X\n";
	num = 0;
	lft = ft_printf(format, num);
	lorig = printf(format, num);
	passt_da_des_eh(lft, lorig);
	num = 42;
	lft = ft_printf(format, num);
	lorig = printf(format, num);
	passt_da_des_eh(lft, lorig);
	num = -42;
	lft = ft_printf(format, num);
	lorig = printf(format, num);
	passt_da_des_eh(lft, lorig);
	num = 2147483647;
	lft = ft_printf(format, num);
	lorig = printf(format, num);
	passt_da_des_eh(lft, lorig);
	num = -2147483648;
	lft = ft_printf(format, num);
	lorig = printf(format, num);
	passt_da_des_eh(lft, lorig);

	puts("\n=== Multiple-Options (%d%s%X) ===");
	format = "%d%s%X\n";
	string = ": ";
	num = 0;
	lft = ft_printf(format, num, string, num);
	lorig = printf(format, num, string, num);
	passt_da_des_eh(lft, lorig);
	num = 42;
	lft = ft_printf(format, num, string, num);
	lorig = printf(format, num, string, num);
	passt_da_des_eh(lft, lorig);
	num = -42;
	lft = ft_printf(format, num, string, num);
	lorig = printf(format, num, string, num);
	passt_da_des_eh(lft, lorig);
	num = 2147483647;
	lft = ft_printf(format, num, string, num);
	lorig = printf(format, num, string, num);
	passt_da_des_eh(lft, lorig);
	num = -2147483648;
	lft = ft_printf(format, num, string, num);
	lorig = printf(format, num, string, num);
	passt_da_des_eh(lft, lorig);

	puts("\n=== Percent: %% ===");
	format = "%%\n";
	lft = ft_printf(format);
	lorig = printf("%%\n");
	passt_da_des_eh(lft, lorig);

	puts("\n=== Pointer: %p ===");
	format = "%p\n";
	string = NULL;
	lft = ft_printf(format, string);
	lorig = printf(format, string);
	passt_da_des_eh(lft, lorig);
	string = "Im a pointer";
	lft = ft_printf(format, string);
	lorig = printf(format, string);
	passt_da_des_eh(lft, lorig);
	puts("\n=== Not supported Option and normal text: %y ===");
	format = "Im not supported %y\n";
	lft = ft_printf(format, string);
	lorig = printf(format, string);
	passt_da_des_eh(lft, lorig);
	puts("\n=== Custom Tests ===");
	format = "%d%d\n";
	num = 42;
	lft = ft_printf(format, num);
	lorig = printf(format, num);
	passt_da_des_eh(lft, lorig);
	format = NULL;
	num = 42;
	lft = ft_printf(format, num);
	lorig = printf(format, num);
	passt_da_des_eh(lft, lorig);
	format = "%c %s %p %d %i %u %x %X %%\n";
	num = 42;
	char c = '4';
	string = "printf";
	lft = ft_printf(format, c, string, string, num, num, num, num, num);
	lorig = printf(format, c, string, string, num, num, num, num, num);
	passt_da_des_eh(lft, lorig);

	puts("\n === Check max Pointer ===");
	format = "%p\n";
	lft = ft_printf(format, 18446744073709551615ULL);
	lorig = printf(format, 18446744073709551615ULL);
	passt_da_des_eh(lft, lorig);

	// GREX TESTS

	printf("   single %%:\n");
	lft = ft_printf("'   %");
	printf("|\n");
	lorig = printf("'   %");
	printf("|\n");
	passt_da_des_eh(lft, lorig);

	lft = ft_printf(" %c,%c,%c,%s", '0', 0, '1', "Hello");
	printf("|\n");
	lorig = printf(" %c,%c,%c,%s", '0', 0, '1', "Hello");
	printf("|\n");
	passt_da_des_eh(lft, lorig);

	ft_printf("char test \n");
	lft = ft_printf(" %c,%c,%c,", '0', 22, '1');
	printf("|\n");
	lorig = printf(" %c,%c,%c,", '0', 22, '1');
	printf("|\n");
	passt_da_des_eh(lft, lorig);
	ft_printf("char test 8\n");
	lft = ft_printf("%c,%c,%c,", '2', '1', 0);
	printf("|\n");
	lorig = printf("%c,%c,%c,", '2', '1', 0);
	printf("|\n");
	passt_da_des_eh(lft, lorig);
	ft_printf("char test 9\n");
	lft = ft_printf("%c,%c,%c,", 0, '1', '2');
	printf("|\n");
	lorig = printf("%c,%c,%c,", 0, '1', '2');
	printf("|\n");
	passt_da_des_eh(lft, lorig);
	ft_printf("str test 10\n");
	lft = ft_printf(" %s %s %s %s %s ", " - ", "", "4", "", "2 ");
	printf("|\n");
	lorig = printf(" %s %s %s %s %s ", " - ", "", "4", "", "2 ");
	printf("|\n");
	passt_da_des_eh(lft, lorig);
	lft = ft_printf(" %s", "äöü~!\"§$%&()=ß²³{[]}@<|>éÈê°\0asd");
	printf("|\n");
	lorig = printf(" %s", "äöü~!\"§$%&()=ß²³{[]}@<|>éÈê°\0asd");
	printf("|\n");
	passt_da_des_eh(lft, lorig);
	ft_printf("nullpointer p test 9\n");
	lft = ft_printf(" %p %p ", 0, 0);
	printf("|\n");
	lorig = printf(" %p %p ", 0, 0);
	printf("|\n");
	passt_da_des_eh(lft, lorig);

	ft_printf("mix test\n");
	lft = ft_printf("%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %c%%", 'A', "42", 42, 42, 42, 42, 42, 'B', "-42", -42, -42, -42, -42, 42, 'C', "0", 0, 0, 0, 0, 42, 0);
	printf("|\n");
	lorig = printf("%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %c%%", 'A', "42", 42, 42, 42, 42, 42, 'B', "-42", -42, -42, -42, -42, 42, 'C', "0", 0, 0, 0, 0, 42, 0);
	printf("|\n");
	passt_da_des_eh(lft, lorig);
	printf("test flag skip\n");
	lft = ft_printf(" % c", '0');
	printf("|\n");
	lorig = printf(" % c", '0');
	printf("|\n");
	passt_da_des_eh(lft, lorig);
	printf("NULL test:\n");
	lft = ft_printf(NULL);
	printf("|\n");
	lorig = printf(NULL);
	printf("|\n");
	passt_da_des_eh(lft, lorig);
	lft = ft_printf(NULL, 42);
	printf("|\n");
	lorig = printf(NULL, 42);
	printf("|\n");
	passt_da_des_eh(lft, lorig);
	lft = ft_printf(NULL);
	printf("|\n");
	lorig = printf(NULL);
	printf("|\n");
	passt_da_des_eh(lft, lorig);
	lft = ft_printf(" %w%", "hello");
	printf("|\n");
	lorig = printf(" %w%", "hello");
	printf("|\n");
	passt_da_des_eh(lft, lorig);

	puts("test arg failures");
	char *bla = "%d%d\n";
	printf("strlen bla: %zu\n", strlen(bla));
	format = "%d%d\n";
	num = 42;
	lft = ft_printf(format, num);
	lorig = printf(format, num);
	passt_da_des_eh(lft, lorig);
	lft = ft_printf(bla, num);
	lorig = printf(bla, num);
	passt_da_des_eh(lft, lorig);
	lft = ft_printf(format, 42);
	lorig = printf(format, 42);
	passt_da_des_eh(lft, lorig);
	lft = ft_printf(bla, 42);
	lorig = printf(bla, 42);
	passt_da_des_eh(lft, lorig);

	lft = ft_printf("int %d, %d\n", 42);
	printf("|\n");
	lorig = printf("int %d, %d\n", 42);
	printf("|\n");
	passt_da_des_eh(lft, lorig);
	lft = ft_printf("%d%d\n", 42);
	printf("|\n");
	lorig = printf("%d%d\n", 42);
	printf("|\n");
	passt_da_des_eh(lft, lorig);
	int foo = 42;
	lft = ft_printf("%d%d\n", foo);
	printf("|\n");
	lorig = printf("%d%d\n", foo);
	printf("|\n");
	passt_da_des_eh(lft, lorig);

	lft = ft_printf(bla, foo);
	printf("|\n");
	lorig = printf(bla, foo);
	printf("|\n");
	passt_da_des_eh(lft, lorig);

	lft = ft_printf("%w%w%d", 42);
	printf("|\n");
	lorig = printf("%w%w%d", 42);
	printf("|\n");
	passt_da_des_eh(lft, lorig);

	for (int i = 0; i <= 256; i++)
		ft_printf("%s\n", i + 256);
}