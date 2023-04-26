#include "main.h"

unsigned int convert_sbase(buffer_t *output, long int num, char *base,
		unsigned char flags, int width, int precision);
unsigned int convert_ubase(buffer_t *output,
		unsigned long int num, char *base,
		unsigned char flags, int width, int precision);

/**
 * convert_sbase - Converts a signed long to an inputted base and stores
 *                 the result to a buffer contained in a struct.
 * @output: A buffer_t struct containing a character array.
 * @num: A signed long to be converted.
 * @base: A pointer to a string containing the base to convert to.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_sbase(buffer_t *output, long int num, char *base,
		unsigned char flags, int width, int precision)
{
	int size;
	char digit, pad = '0';
	unsigned int res = 1;

	for (size = 0; *(base + size);)
		size++;

	if (num >= size || num <= -size)
		res += convert_sbase(output, num / size, base,
				flags, width - 1, precision - 1);

	else
	{
		for (; precision > 1; precision--, width--) /* Handle precision */
			res += _memcpy(output, &pad, 1);

		if (NEG_FLAG == 0) /* Handle width */
		{
			pad = (ZERO_FLAG == 1) ? '0' : ' ';
			for (; width > 1; width--)
				res += _memcpy(output, &pad, 1);
		}
	}

	digit = base[(num < 0 ? -1 : 1) * (num % size)];
	_memcpy(output, &digit, 1);

	return (res);
}

/**
 * convert_ubase - Converts an unsigned long to an inputted base and
 *                 stores the result to a buffer contained in a struct.
 * @output: A buffer_t struct containing a character array.
 * @num: An unsigned long to be converted.
 * @base: A pointer to a string containing the base to convert to.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_ubase(buffer_t *output, unsigned long int num, char *base,
		unsigned char flags, int width, int precision)
{
	unsigned int size, res = 1;
	char digit, pad = '0', *lead = "0x";

	for (size = 0; *(base + size);)
		size++;

	if (num >= size)
		res += convert_ubase(output, num / size, base,
				flags, width - 1, precision - 1);

	else
	{
		if (((flags >> 5) & 1) == 1) /* Printing a ptr address */
		{
			width -= 2;
			precision -= 2;
		}
		for (; precision > 1; precision--, width--) /* Handle precision */
			res += _memcpy(output, &pad, 1);

		if (NEG_FLAG == 0) /* Handle width */
		{
			pad = (ZERO_FLAG == 1) ? '0' : ' ';
			for (; width > 1; width--)
				res += _memcpy(output, &pad, 1);
		}
		if (((flags >> 5) & 1) == 1) /* Print 0x for ptr address */
			res += _memcpy(output, lead, 2);
	}

	digit = base[(num % size)];
	_memcpy(output, &digit, 1);

	return (res);
}
