/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 17:39:56 by mboulara          #+#    #+#             */
/*   Updated: 2019/08/01 19:44:51 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_padding(char *str, char c, int size)
{
	char	*ret;
	int		i;
	int		j;
	int		k;

	ret = size < 0 ? ft_strnew(-size) : ft_strnew(size);
	i = 0;
	k = (size < 0) ? -size : size;
	while (i < k)
		ret[i++] = c;
	j = ft_strlen(str);
	if (size > 0)
	{
		i--;
		while (j > 0)
			ret[i--] = str[--j];
	}
	else
	{
		i = -1;
		while (++i < j)
			ret[i] = str[i];
	}
	return (ret);
}

char		*str_man(t_format info, char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (info.specifier != 'f')
	{
		if ((size_t)info.precision > len && str[0] != '-')
			str = ft_padding(str, '0', info.precision);
		if (info.width > info.precision)
			str = ft_padding(str, ' ', info.width);
	}
	return (str);
}

char		*str_precision(t_format info, char *str)
{
	int		presi_;

	presi_ = info.precision;
	if (info.specifier == 'f' && info.precision == 0)
		presi_ = 6;
	if (str[0] == '-')
	{
		str[0] = '0';
		str = ft_padding(str, '0', presi_);
		str = ft_strjoin("-", str);
	}
	else
		str = ft_padding(str, '0', presi_);
	return (str);
}

char		*str_width(t_format info, char *str)
{
	char	c;

	if (info.flag & ZERO_FLAG)
		c = '0';
	else if (info.flag & SPACE_FLAG)
		c = ' ';
	else
		c = ' ';
	if (info.flag & MINUS_FLAG)
		return (ft_padding(str, c, -info.width));
	if ((info.specifier == 'd' || info.specifier == 'i') && str[0] == '-')
	{
		info.precision = info.width - 1;
		return (str_precision(info, str));
	}
	else
		return (ft_padding(str, c, info.width));
}
