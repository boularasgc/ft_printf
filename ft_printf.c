/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 11:59:22 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/16 08:33:23 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_printf(const char *restrict format, ...)
{
	va_list args;
	int		i;

	va_start(args, format);
	i = core_printf(1, format, &args);
	va_end(args);
	return (i);
}

int			ft_fprintf(int fd, const char *restrict format, ...)
{
	va_list args;
	int		i;

	va_start(args, format);
	i = core_printf(fd, format, &args);
	va_end(args);
	return (i);
}
