/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 14:55:57 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/06 14:03:05 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		c_handler(t_format info, va_list *args)
{
	char	*a;
	char	value;
	size_t	len;

	a = info.width > 1 ? malloc(info.width + 1) : malloc(2);
	if (info.length == L)
		value = (wint_t)va_arg(*args, wint_t);
	else
		value = (char)va_arg(*args, int);
	a[0] = value;
	a[1] = '\0';
	len = info.width > 1 ? info.width : 1;
	if (info.width > 1)
		ft_memset(a, ' ', info.width);
	if (info.width > 1 && info.flag & MINUS_FLAG)
		a[0] = value;
	if (info.width > 1 && !(info.flag & MINUS_FLAG))
		a[info.width - 1] = value;
	if (info.width > 1)
		a[info.width] = '\0';
	write(info.fd, a, len);
	free(a);
	return (len);
}
