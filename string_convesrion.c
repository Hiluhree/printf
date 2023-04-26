#include "main.h"

unsigned int convert_s(va_list args, buffer_t *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int convert_S(va_list args, buffer_t *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int convert_r(va_list args, buffer_t *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int convert_R(va_list args, buffer_t *output,
		unsigned char flags, int width, int precision, unsigned char len);

/**
 * convert_s - Converts an argument to a string and
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
unsigned int convert_s(va_list args, buffer_t *output,
		unsigned char flags, int width, int precision, unsigned char len)
{
	char *str, *null = "(null)";
	int size;
	unsigned int res = 0;

	(void)flags;
	(void)len;

	str = va_arg(args, char *);
	if (str == NULL)
		return (_memcpy(output, null, 6));

	for (size = 0; *(str + size);)
		size++;

	res += print_string_width(output, flags, width, precision, size);

	precision = (precision == -1) ? size : precision;
	while (*str != '\0' && precision > 0)
	{
		res += _memcpy(output, str, 1);
		precision--;
		str++;
	}

	res += print_neg_width(output, res, flags, width);

	return (res);
}

/**
 * convert_S - Converts an argument to a string and
 *             stores it to a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 *
 * Description: Non-printable characteres (ASCII values < 32 or >= 127)
 *              are stored as \x followed by the ASCII code value in hex.
 */
unsigned int convert_S(va_list args, buffer_t *output,
		unsigned char flags, int width, int precision, unsigned char len)
{
	char *str, *null = "(null)", *hex = "\\x", zero = '0';
	int size, index;
	unsigned int res = 0;

	(void)len;
	str = va_arg(args, char *);
	if (str == NULL)
		return (_memcpy(output, null, 6));

	for (size = 0; str[size];)
		size++;

	res += print_string_width(output, flags, width, precision, size);

	precision = (precision == -1) ? size : precision;
	for (index = 0; *(str + index) != '\0' && index < precision; index++)
	{
		if (*(str + index) < 32 || *(str + index) >= 127)
		{
			res += _memcpy(output, hex, 2);
			if (*(str + index) < 16)
				res += _memcpy(output, &zero, 1);
			res += convert_ubase(output, *(str + index),
					     "0123456789ABCDEF", flags, 0, 0);
			continue;
		}
		res += _memcpy(output, (str + index), 1);
	}

	res += print_neg_width(output, res, flags, width);

	return (res);
}

/**
 * convert_r - Reverses a string and stores it
 *             to a buffer contained in a struct.
 * @args: A va_list pointing to the string to be reversed.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_r(va_list args, buffer_t *output,
		unsigned char flags, int width, int precision, unsigned char len)
{
	char *str, *null = "(null)";
	int size, end, i;
	unsigned int res = 0;

	(void)flags;
	(void)len;

	str = va_arg(args, char *);
	if (str == NULL)
		return (_memcpy(output, null, 6));

	for (size = 0; *(str + size);)
		size++;

	res += print_string_width(output, flags, width, precision, size);

	end = size - 1;
	precision = (precision == -1) ? size : precision;
	for (i = 0; end >= 0 && i < precision; i++)
	{
		res += _memcpy(output, (str + end), 1);
		end--;
	}

	res += print_neg_width(output, res, flags, width);

	return (res);
}

/**
 * convert_R - Converts a string to ROT13 and stores
 *             it to a buffer contained in a struct.
 * @args: A va_list pointing to the string to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @len: A lenth modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_R(va_list args, buffer_t *output,
		unsigned char flags, int width, int precision, unsigned char len)
{
	char *alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *rot13 = "nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM";
	char *str, *null = "(null)";
	int i, j, size;
	unsigned int res = 0;

	(void)flags;
	(void)len;

	str = va_arg(args, char *);
	if (str == NULL)
		return (_memcpy(output, null, 6));

	for (size = 0; *(str + size);)
		size++;

	res += print_string_width(output, flags, width, precision, size);

	precision = (precision == -1) ? size : precision;
	for (i = 0; *(str + i) != '\0' && i < precision; i++)
	{
		for (j = 0; j < 52; j++)
		{
			if (*(str + i) == *(alpha + j))
			{
				res += _memcpy(output, (rot13 + j), 1);
				break;
			}
		}
		if (j == 52)
			res += _memcpy(output, (str + i), 1);
	}

	res += print_neg_width(output, res, flags, width);

	return (res);
}
