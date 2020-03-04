/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 19:59:12 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/22 19:51:20 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		ps_handler(t_format info, va_list *args)
{
	char	*a;
	size_t	len;

	(void)args;
	info.flag &= info.flag & MINUS_FLAG && info.flag & ZERO_FLAG ?
	~ZERO_FLAG : info.flag;
	a = info.width > 1 ? malloc(info.width + 1) : malloc(2);
	a[0] = '%';
	a[1] = '\0';
	len = info.width > 1 ? info.width : 1;
	if (info.width > 1 && (info.flag & ZERO_FLAG))
		ft_memset(a, '0', info.width);
	if (info.width > 1 && !(info.flag & ZERO_FLAG))
		ft_memset(a, ' ', info.width);
	if (info.width > 1 && info.flag & MINUS_FLAG)
		a[0] = '%';
	if (info.width > 1 && !(info.flag & MINUS_FLAG))
		a[info.width - 1] = '%';
	if (info.width > 1)
		a[info.width] = '\0';
	write(info.fd, a, len);
	ft_strdel(&a);
	return (len);
}
