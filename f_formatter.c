/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_formatter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 07:23:06 by mboulara          #+#    #+#             */
/*   Updated: 2019/08/01 17:39:15 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define FPREC 6

char		*f_precision(t_format info, char *str, intmax_t *v)
{
	size_t	size;
	size_t	len;
	int		rem;

	rem = 0;
	size = info.precision >= 0 ? info.precision : FPREC;
	len = ft_strlen(str);
	str = (size > len) ? ft_padding(str, '0', size) : str;
	str = (info.precision >= 0) ? handle_remaider(str, size, &rem) : str;
	str[size] = '\0';
	v += v >= 0 ? (intmax_t)rem : (intmax_t)-rem;
	return (str);
}

char		*handle_remaider(char *str, int pos, int *rem)
{
	int		i;
	int		c;
	int		left;

	i = pos;
	left = 0;
	c = str[i] - '0';
	if (c >= 5)
	{
		str[i] = '0';
		left = 1;
	}
	while (i >= 0 && left > 0)
	{
		c = str[i] - '0' + left;
		if (c > 9)
		{
			left = c % 9;
			str[i] = '0' + (c % 10);
		}
		i--;
	}
	rem += left;
	return (str);
}

char		*manage_f_strs(t_format info, char *left, char *right, intmax_t i)
{
	char	p_c;
	char	*str;

	info.flag &= (i < 0) || (left[0] == '-') ? ~SPACE_FLAG : info.flag;
	str = (info.precision == 0) ? left :
	ft_strjoin(left, ft_strjoin(".", right));
	p_c = info.flag & ZERO_FLAG ? '0' : ' ';
	p_c = info.flag & MINUS_FLAG && info.flag & ZERO_FLAG ? ' ' : p_c;
	if (info.flag & PLUS_FLAG && i >= 0)
		str = ft_strjoin("+", str);
	if (info.flag & SPACE_FLAG && !(info.flag & PLUS_FLAG))
		str = ft_strjoin(" ", str);
	if (info.flag & HASH_FLAG && info.precision == 0)
		str = ft_strjoin(str, ".");
	if ((size_t)info.width > ft_strlen(str))
		str = manage_f_width(info, str, p_c);
	return (str);
}

char		*manage_f_width(t_format info, char *str, char p_c)
{
	char	tmp;
	int		size;

	size = (info.flag & MINUS_FLAG) ? -info.width : info.width;
	if (p_c == '0' && (str[0] == '+' || str[0] == '-' || str[0] == ' '))
	{
		tmp = str[0];
		str[0] = '0';
		str = ft_padding(str, p_c, info.width);
		str[0] = tmp;
	}
	else
		str = ft_padding(str, p_c, size);
	return (str);
}
