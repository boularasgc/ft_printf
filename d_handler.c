/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 12:40:44 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/06 14:02:27 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*space_padding(int size, char *str)
{
	str[0] = '0';
	str = ft_padding(str, '0', size);
	str[0] = ' ';
	return (str);
}

static char		*apply_d_width(t_format info, char *str, intmax_t i)
{
	char		p_c;
	int			size;

	p_c = info.flag & ZERO_FLAG ? '0' : ' ';
	p_c = info.flag & MINUS_FLAG ? ' ' : p_c;
	p_c = info.precision >= 0 && info.flag & ZERO_FLAG ? ' ' : p_c;
	size = info.flag & MINUS_FLAG ? -info.width : info.width;
	if (i < 0 && p_c == '0')
	{
		str[0] = '0';
		str = ft_padding(str, p_c, size);
		str[0] = '-';
	}
	else if (i >= 0 && info.flag & PLUS_FLAG && p_c == '0')
	{
		str[0] = '0';
		str = ft_padding(str, p_c, size);
		str[0] = '+';
	}
	else if (i >= 0 && info.flag & SPACE_FLAG && p_c == '0')
		str = space_padding(size, str);
	else
		str = ft_padding(str, p_c, size);
	return (str);
}

static char		*d_customizer(t_format info, char *str, intmax_t i)
{
	int			len;

	len = ft_strlen(str);
	if (i >= 0 && info.precision > len)
		str = ft_padding(str, '0', info.precision);
	if (i < 0 && info.precision > len - 1)
	{
		str[0] = '0';
		str = ft_padding(str, '0', info.precision);
		str = ft_strjoin("-", str);
	}
	str[0] = info.precision == 0 ? '\0' : str[0];
	str = info.flag & PLUS_FLAG && i >= 0 ? ft_strjoin("+", str) : str;
	if (i >= 0 && (info.flag & SPACE_FLAG) && !(info.flag & PLUS_FLAG))
		str = ft_strjoin(" ", str);
	len = ft_strlen(str);
	str = info.width > len ? apply_d_width(info, str, i) : str;
	return (str);
}

size_t			d_handler(t_format info, va_list *args)
{
	intmax_t	i;
	size_t		len;
	char		buf[256];
	char		*s;

	if (info.length >= L)
		i = (long)(intmax_t)va_arg(*args, intmax_t);
	else
		i = (int)va_arg(*args, int);
	s = itoa_base((long)i, buf, 10);
	s[ft_strlen(s)] = '\0';
	s = d_customizer(info, s, i);
	len = ft_strlen(s);
	write(info.fd, s, len);
	return (len);
}
