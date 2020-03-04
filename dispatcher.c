/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 13:32:52 by mboulara          #+#    #+#             */
/*   Updated: 2019/08/01 18:49:50 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	dispatcher_(t_format info, va_list *args)
{
	if (info.specifier == 'c')
		return (c_handler(info, args));
	if (info.specifier == 's')
		return (s_handler(info, args));
	if (info.specifier == 'p')
		return (p_handler(info, args));
	if (info.specifier == 'd' || info.specifier == 'i')
		return (d_handler(info, args));
	if (info.specifier == 'u')
		return (u_handler(info, args));
	if (info.specifier == 'o')
		return (o_handler(info, args));
	if (info.specifier == 'x')
		return (x_handler(info, args));
	if (info.specifier == 'X')
		return (xx_handler(info, args));
	if (info.specifier == 'f')
		return (f_handler(info, args));
	if (info.specifier == '%')
		return (ps_handler(info, args));
	return (0);
}
