#include "main.h"

/**
 * print_char - function that prints a char
 * @types: parameter
 * @buffer: parameter
 * @flags: parameter
 * @width: parameter
 * @precision: parameter
 * @size: parameter
 * Return: number
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char i = va_arg(types, int);

	return (handle_write_char(i, buffer, flags, width, precision, size));
}


/**
 * print_string - function that prints a string
 * @types: parameter
 * @buffer: parameter
 * @flags: parameter
 * @width: parameter
 * @precision: parameter
 * @size: parameter
 * Return: number
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int lgth = 0, a;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}
	while (str[lgth] != '\0')
		lgth++;
	if (precision >= 0 && precision < lgth)
		lgth = precision;
	if (width > lgth)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], lgth);
			for (a = width - lgth; a > 0; a--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (a = width - lgth; a > 0; a--)
				write(1, " ", 1);
			write(1, &str[0], lgth);
			return (width);
		}
	}
	return (write(1, str, lgth));
}


/**
 * print_percent - function that prints a percent sign
 * @types: parameter
 * @buffer: parameter
 * @flags: parameter
 * @width: parameter
 * @precision: parameter
 * @size: parameter
 * Return: number
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}


/**
 * print_int - function that print int
 * @types: parameter
 * @buffer: parameter
 * @flags: parameter
 * @width: parameter
 * @precision: parameter
 * @size: parameter
 * Return: number
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	int is_neg = 0;
	long int i = va_arg(types, long int);
	unsigned long int nu;

	i = convert_size_number(i, size);
	if (i == 0)
		buffer[a--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	nu = (unsigned long int)i;
	if (i < 0)
	{
		nu = (unsigned long int)((-1) * i);
		is_neg = 1;
	}
	while (nu > 0)
	{
		buffer[a--] = (nu % 10) + '0';
		nu /= 10;
	}
	a++;
	return (write_number(is_neg, a, buffer, flags, width, precision, size));
}


/**
 * print_binary - function that prints an unsigned number
 * @types: parameter
 * @buffer: parameter
 * @flags: parameter
 * @width: parameter
 * @precision: parameter
 * @size: parameter
 * Return: count
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int a, b, i, sum;
	unsigned int z[32];
	int cnt;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	a = va_arg(types, unsigned int);
	b = 2147483648;
	z[0] = a / b;
	for (i = 1; i < 32; i++)
	{
		a /= 2;
		z[i] = (a / b) % 2;
	}
	for (i = 0, sum = 0, cnt = 0; i < 32; i++)
	{
		sum += z[i];
		if (sum || i == 31)
		{
			char c = '0' + z[i];

			write(1, &c, 1);
			cnt++;
		}
	}
	return (cnt);
}
