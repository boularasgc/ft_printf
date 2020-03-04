/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 13:44:37 by mboulara          #+#    #+#             */
/*   Updated: 2019/08/01 21:01:10 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "ft_printf.h"

char		*reverse(char *buffer)
{
	int		i;
	int		j;
	size_t	len;
	char	*str;

	i = 0;
	len = ft_strlen(buffer);
	j = len;
	str = ft_strnew(len);
	while (buffer[i])
	{
		str[--j] = buffer[i++];
	}
	str[len] = '\0';
	return (str);
}

char		*itoa_base(intmax_t num, char *buffer, int base)
{
	int		i;
	int		neg;
	int		rem;

	i = 0;
	if (num == LONG_MIN)
		return (ft_strdup("-9223372036854775808"));
	if (num == 0)
		return (ft_strdup("0"));
	if (base == 10 && num < 0)
	{
		num = -1 * num;
		neg = 1;
	}
	while (num != 0)
	{
		rem = num % base;
		buffer[i++] = (rem > 9) ? (rem - 10) + 'a' : (rem + '0');
		num = num / base;
	}
	if (neg == 1 && base == 10)
		buffer[i++] = '-';
	buffer[i] = '\0';
	return (reverse(buffer));
}

char		*uitoa_base(uintmax_t num, char *buffer, int base, char a)
{
	int		i;
	int		rem;

	i = 0;
	if (num == 0)
	{
		buffer[i++] = '0';
		buffer[i] = '\0';
		return (buffer);
	}
	while (num != 0)
	{
		rem = num % base;
		buffer[i++] = (rem > 9) ? (rem - 10) + a : (rem + '0');
		num = num / base;
	}
	buffer[i] = '\0';
	return (reverse(buffer));
}
