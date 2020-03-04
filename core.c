/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 15:07:42 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/06 14:04:37 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_format		parse_format(const char *format, size_t *pos, va_list *args)
{
	t_format	info;

	info.flag = parse_flags(&*format, &*pos);
	info.width = parse_width(&*format, &*pos, args);
	info.precision = parse_precision(&*format, &*pos, args);
	info.length = parse_length(&*format, &*pos);
	info.specifier = parse_specifier(&*format, &*pos);
	return (info);
}

size_t			get_string(int fd, const char *format, size_t *pos,
va_list *args)
{
	t_format	info;

	info = parse_format(&*format, &*pos, args);
	info.fd = fd;
	return (dispatcher_(info, args));
}

int				core_printf(int fd, const char *format, va_list *args)
{
	size_t		cnt;
	size_t		pos;

	cnt = 0;
	pos = 0;
	while (format[pos])
	{
		if (format[pos] == '%')
		{
			++pos;
			cnt += get_string(fd, format, &pos, args);
		}
		else
		{
			++cnt;
			write(fd, &format[pos], 1);
		}
		pos++;
	}
	return (cnt);
}
