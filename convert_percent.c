#include "main.h"

unsigned int convert_c(va_list args, buffer_t *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int convert_percent(va_list args, buffer_t *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int convert_p(va_list args, buffer_t *output,
		unsigned char flags, int width, int precision, unsigned char len);

/**
 * convert_c - Converts an argument to an unsigned char and
 *             stores it to a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_c(va_list args, buffer_t *output,
		unsigned char flags, int width, int precision, unsigned char len)
{
	char c;
	unsigned int res = 0;

	(void)precision;
	(void)len;

	c = va_arg(args, int);

	res += print_width(output, res, flags, width);
	res += _memcpy(output, &c, 1);
	res += print_neg_width(output, res, flags, width);

	return (res);
}

/**
 * convert_percent - Stores a percent sign to a
 *                   buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer (always 1).
 */
unsigned int convert_percent(va_list args, buffer_t *output,
		unsigned char flags, int width, int precision, unsigned char len)
{
	char percent = '%';
	unsigned int res = 0;

	(void)args;
	(void)precision;
	(void)len;

	res += print_width(output, res, flags, width);
	res += _memcpy(output, &percent, 1);
	res += print_neg_width(output, res, flags, width);

	return (res);
}

/**
 * convert_p - Converts the address of an argument to hex and
 *             stores it to a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_p(va_list args, buffer_t *output,
		unsigned char flags, int width, int precision, unsigned char len)
{
	char *null = "(nil)";
	unsigned long int address;
	unsigned int res = 0;

	(void)len;

	address = va_arg(args, unsigned long int);
	if (address == '\0')
		return (_memcpy(output, null, 5));

	flags |= 32;
	res += convert_ubase(output, address, "0123456789abcdef",
			flags, width, precision);
	res += print_neg_width(output, res, flags, width);

	return (res);
}
