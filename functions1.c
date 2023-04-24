#include "main.h"

/**
 * print_unsigned - function that prints an unsigned number
 * @types: parameter
 * @buffer: parameter
 * @flags: parameter
 * @width: parameter
 * @precision: parameter
 * @size: parameter
 * Return: number
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	unsigned long int nu = va_arg(types, unsigned long int);

	nu = convert_size_unsgnd(nu, size);
	if (nu == 0)
		buffer[a--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	while (nu > 0)
	{
		buffer[a--] = (nu % 10) + '0';
		nu /= 10;
	}
	a++;
	return (write_unsgnd(0, a, buffer, flags, width, precision, size));
}


/**
 * print_octal - function that prints an unsigned number
 * @types: parameter
 * @buffer: parameter
 * @flags: parameter
 * @width: parameter
 * @precision: parameter
 * @size: parameter
 * Return: number
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int a = BUFF_SIZE - 2;
	unsigned long int nu = va_arg(types, unsigned long int);
	unsigned long int in_num = nu;

	UNUSED(width);
	nu = convert_size_unsgnd(nu, size);
	if (nu == 0)
		buffer[a--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	while (nu > 0)
	{
		buffer[a--] = (nu % 8) + '0';
		nu /= 8;
	}
	if (flags & F_HASH && in_num != 0)
		buffer[a--] = '0';
	a++;
	return (write_unsgnd(0, a, buffer, flags, width, precision, size));
}


/**
 * print_hexadecimal - function that prints an unsigned number
 * @types: parameter
 * @buffer: parameter
 * @flags: parameter
 * @width: parameter
 * @precision: parameter
 * @size: parameter
 * Return: number
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}


/**
 * print_hexa_upper - function that prints an unsigned number
 * @types: parameter
 * @buffer: parameter
 * @flags: parameter
 * @width: parameter
 * @precision: parameter
 * @size: parameter
 * Return: number
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}


/**
 * print_hexa - funvtion that prints a hexadecimal number in lower or upper
 * @types: parameter
 * @map_to: parameter
 * @buffer: parameter
 * @flags: parameter
 * @flag_ch: parameter
 * @width: parameter
 * @precision: parameter
 * @size: parameter
 * @size: parameter
 * Return: number
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	unsigned long int nu = va_arg(types, unsigned long int);
	unsigned long int in_num = nu;

	UNUSED(width);
	nu = convert_size_unsgnd(nu, size);
	if (nu == 0)
		buffer[a--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	while (nu > 0)
	{
		buffer[a--] = map_to[nu % 16];
		nu /= 16;
	}
	if (flags & F_HASH && in_num != 0)
	{
		buffer[a--] = flag_ch;
		buffer[a--] = '0';
	}
	a++;
	return (write_unsgnd(0, a, buffer, flags, width, precision, size));
}
