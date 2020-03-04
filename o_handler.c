/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 18:39:08 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/06 14:01:49 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	char	get_opad_char(t_format info)
{
	char		p_c;

	p_c = info.flag & ZERO_FLAG ? '0' : ' ';
	p_c = info.flag & MINUS_FLAG && info.flag & ZERO_FLAG ? ' ' : p_c;
	p_c = info.precision >= 0 && info.flag & ZERO_FLAG ? ' ' : p_c;
	return (p_c);
}

static char		*apply_oct_width(t_format info, char *str, char c)
{
	int			len;

	len = ft_strlen(str);
	if (info.width > len && c == '0')
		str = ft_padding(str, c, info.width);
	else if (info.width > len && info.flag & MINUS_FLAG)
		str = ft_padding(str, c, -info.width);
	else if (info.width > len && !(info.flag & MINUS_FLAG))
		str = ft_padding(str, c, info.width);
	return (str);
}

size_t			o_handler(t_format info, va_list *args)
{
	uintmax_t	i;
	size_t		len;
	char		*s;
	char		c;
	char		buf[256];

	if (info.length == NONE)
		i = (unsigned int)va_arg(*args, unsigned int);
	else
		i = (uintmax_t)va_arg(*args, uintmax_t);
	i = info.length == H ? (unsigned short int)i : i;
	i = info.length == HH ? (unsigned char)i : i;
	c = get_opad_char(info);
	s = uitoa_base(i, buf, 8, 'a');
	s = info.precision > 0 && (size_t)info.precision > ft_strlen(s) ?
	ft_padding(s, '0', info.precision) : s;
	s[0] = (info.precision == 0) && !(info.flag & HASH_FLAG) ? '\0' : s[0];
	s = info.flag & HASH_FLAG && i > 0 && s[0] != '0' ? ft_strjoin("0", s) : s;
	s = info.width > 0 ? apply_oct_width(info, s, c) : s;
	len = ft_strlen(s);
	write(info.fd, s, len);
	return (len);
}
