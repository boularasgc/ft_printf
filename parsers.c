/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 19:06:23 by mboulara          #+#    #+#             */
/*   Updated: 2019/08/01 19:07:52 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	parse_flags(const char *format, size_t *pos)
{
	char x;

	x = 0;
	while (format[*pos])
	{
		if (format[*pos] == '#')
			x |= HASH_FLAG;
		else if (format[*pos] == '+')
			x |= PLUS_FLAG;
		else if (format[*pos] == '-')
			x |= MINUS_FLAG;
		else if (format[*pos] == '0')
			x |= ZERO_FLAG;
		else if (format[*pos] == ' ')
			x |= SPACE_FLAG;
		else
			break ;
		(*pos)++;
	}
	return (x);
}

int		parse_width(const char *format, size_t *pos, va_list *args)
{
	int x;

	if (format[*pos] == '*')
	{
		++(*pos);
		return (va_arg(*args, int));
	}
	else
		x = ft_atoi(&format[*pos]);
	while (ft_isdigit(format[*pos]))
		(*pos)++;
	return (x);
}

/*
** the width
** '*' means the width is taken from the next argument;
** Minimum number of characters to be printed. If the value to be printed is
** shorter than this number, the result is padded with blank spaces. The value
** is not truncated even if the result is larger.
*/

int		parse_precision(const char *format, size_t *pos, va_list *args)
{
	int x;

	x = -1;
	if (format[*pos] == '.')
	{
		x = 0;
		++(*pos);
		if (format[*pos] == '*')
		{
			++(*pos);
			return (va_arg(*args, int));
		}
		else
			x = ft_atoi(&format[*pos]);
		while (ft_isdigit(format[*pos]))
			(*pos)++;
	}
	return (x);
}

int		parse_length(const char *format, size_t *pos)
{
	int x;

	x = 0;
	if ((format[*pos] == 'h') && (format[*pos + 1] == 'h'))
		x = HH;
	else if (format[*pos] == 'h')
		x = H;
	if ((format[*pos] == 'l') && (format[*pos + 1] == 'l'))
		x = LL;
	else if (format[*pos] == 'l')
		x = L;
	if (format[*pos] == 'j')
		x = J;
	if (format[*pos] == 'z')
		x = Z;
	if (format[*pos] == 't')
		x = T;
	if (format[*pos] == 'L')
		x = CL;
	if (x == HH || x == LL)
		(*pos) += 2;
	if (x == L || x == H || x == J || x == Z || x == T || x == CL)
		(*pos)++;
	return (x);
}

char	parse_specifier(const char *format, size_t *pos)
{
	char c;

	c = 0;
	if (format[*pos] == 'd' || format[*pos] == 'i')
		c = 'd';
	else if (format[*pos] == 'c')
		c = 'c';
	else if (format[*pos] == 's')
		c = 's';
	else if (format[*pos] == 'p')
		c = 'p';
	else if (format[*pos] == 'u')
		c = 'u';
	else if (format[*pos] == 'x')
		c = 'x';
	else if (format[*pos] == 'X')
		c = 'X';
	else if (format[*pos] == 'o')
		c = 'o';
	else if (format[*pos] == 'f')
		c = 'f';
	else if (format[*pos] == '%')
		c = '%';
	return (c);
}
