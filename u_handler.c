/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:48:32 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/06 21:33:51 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t			u_handler(t_format info, va_list *args)
{
	uintmax_t	i;
	size_t		len;
	char		c;
	char		buf[256];
	char		*s;

	c = info.flag & ZERO_FLAG ? '0' : ' ';
	c = info.precision >= 0 && info.flag & ZERO_FLAG ? ' ' : c;
	i = (uintmax_t)va_arg(*args, uintmax_t);
	i = info.length == H ? (unsigned short int)i : i;
	i = info.length == HH ? (unsigned char)i : i;
	s = uitoa_base(i, buf, 10, 'a');
	if (info.precision == 0)
		s[0] = '\0';
	s = info.precision > 0 && (size_t)info.precision > ft_strlen(s) ?
	ft_padding(s, '0', info.precision) : s;
	s = info.width > 0 && (size_t)info.width > ft_strlen(s) &&
	!(info.flag & MINUS_FLAG) ? ft_padding(s, c, info.width) : s;
	s = info.width > 0 && (size_t)info.width > ft_strlen(s) &&
	(info.flag & MINUS_FLAG) ? ft_padding(s, c, -info.width) : s;
	len = ft_strlen(s);
	write(info.fd, s, len);
	return (len);
}
