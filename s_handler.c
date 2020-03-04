/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 13:20:39 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/06 14:01:20 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		s_handler(t_format info, va_list *args)
{
	char	*str;
	size_t	len;
	char	*str1;

	str = (char *)va_arg(*args, char *);
	if (!str)
		str1 = ft_strdup("(null)");
	else
		str1 = ft_strdup(str);
	if (info.precision >= 0)
		str1[info.precision] = '\0';
	len = ft_strlen(str1);
	if ((size_t)info.width > len && (info.flag & MINUS_FLAG))
		str1 = ft_padding(str1, ' ', -info.width);
	else if ((size_t)info.width > len)
		str1 = ft_padding(str1, ' ', info.width);
	len = ft_strlen(str1);
	write(info.fd, str1, len);
	free(str1);
	return (len);
}
