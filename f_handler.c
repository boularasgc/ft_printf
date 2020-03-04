/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 19:57:35 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/06 14:01:59 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char			*check_nan_inf_zero(union u_double fdata)
{
	if (fdata.bits.exp == MAX_EXPONENT && fdata.bits.mant != 0)
		return ("nan");
	if (fdata.bits.exp == MAX_EXPONENT && fdata.bits.mant == 0)
	{
		if (fdata.bits.sign == 1)
			return ("-inf");
		else
			return ("inf");
	}
	if (fdata.bits.exp == 0 && fdata.bits.mant == 0)
	{
		if (fdata.bits.sign == 1)
			return ("-0");
		else
			return ("0");
	}
	return (NULL);
}

static char			*f_calc_prec(t_format info, double v_)
{
	int				i;
	uintmax_t		v1;
	int				pow;
	char			*s;

	s = malloc(256);
	pow = 1;
	i = 7;
	i = (info.precision < 0) ? 7 : info.precision + 1;
	while (--i >= 0)
	{
		pow = pow * 10;
		v_ = v_ * 10;
	}
	pow = pow / 10;
	v1 = v_;
	if (v1 % 10 >= 5)
		v1 += 10;
	v1 = ((v1) / 10);
	return (itoa_base(v1, s, 10));
}

char				*str_f_handler(t_format info, t_fvar data, double x)
{
	data.left_ = malloc(246);
	data.f_ = x;
	data.v_ = data.f_;
	data.f_ = data.f_ - data.v_;
	data.f_ = data.f_ < 0 ? -data.f_ : data.f_;
	data.right_ = f_calc_prec(info, data.f_);
	data.right_ = f_precision(info, data.right_, &data.v_);
	data.left_ = itoa_base(data.v_, data.left_, 10);
	if (x < 0 && data.v_ >= 0)
		data.left_ = ft_strjoin("-", data.left_);
	data.left_ = manage_f_strs(info, data.left_, data.right_, data.v_);
	return (data.left_);
}

size_t				f_handler(t_format info, va_list *args)
{
	union u_double	fdata;
	t_fvar			data;

	data.left_ = malloc(225);
	data.right_ = malloc(225);
	if (info.length == CL)
		fdata.x = (long double)va_arg(*args, long double);
	else
		fdata.x = (double)va_arg(*args, double);
	data.left_ = check_nan_inf_zero(fdata);
	if (data.left_ == NULL)
		data.left_ = str_f_handler(info, data, fdata.x);
	else
		data.left_ = manage_f_strs(info, data.left_, data.right_, data.v_);
	data.len = ft_strlen(data.left_);
	write(info.fd, data.left_, data.len);
	free(data.left_);
	free(data.right_);
	return (data.len);
}
