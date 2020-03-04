/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 21:33:42 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/06 14:01:38 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		p_handler(t_format info, va_list *args)
{
	void	*p;
	char	*s;
	int		len;

	p = (void *)va_arg(*args, void*);
	s = ft_strnew(20);
	s = itoa_base((intmax_t)p, s, 16);
	s = str_precision(info, s);
	s = ft_strjoin("0x", s);
	len = ft_strlen(s);
	if (info.width > len && (info.flag & MINUS_FLAG))
		s = ft_padding(s, ' ', -info.width);
	else if (info.width > len)
		s = ft_padding(s, ' ', info.width);
	len = ft_strlen(s);
	write(info.fd, s, len);
	return (len);
}
