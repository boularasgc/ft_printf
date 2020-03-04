/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboulara <mboulara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:46:35 by mboulara          #+#    #+#             */
/*   Updated: 2020/01/22 08:32:47 by mboulara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define MAX_EXPONENT 2047
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
# include <wchar.h>
# include "../libft.h"

typedef enum	e_flags
{
	HASH_FLAG = 1,
	PLUS_FLAG = 2,
	MINUS_FLAG = 4,
	ZERO_FLAG = 8,
	SPACE_FLAG = 16
}				t_flags;

typedef enum	e_length
{
	NONE = 0,
	H = 1,
	HH = 2,
	L = 3,
	LL = 4,
	J = 5,
	Z = 6,
	T = 7,
	CL = 8
}				t_length;

typedef	struct	s_fvar
{
	intmax_t	v_;
	long double f_;
	char		*left_;
	char		*right_;
	size_t		len;
}				t_fvar;

typedef	struct	s_format_info
{
	char		flag;
	int			width;
	int			precision;
	int			length;
	char		specifier;
	int			fd;
}				t_format;

union			u_double {
	double				x;
	struct		s_bit
	{
		unsigned int	sign:1;
		unsigned int	exp:11;
		unsigned long	mant:52;
	}					bits;
};

union			u_ldouble {
	long double			x;
	struct		s_lbit
	{
		unsigned int	sign:1;
		unsigned int	exp:15;
		unsigned long	mant:64;
	}					lbits;
};

int				core_printf(int fd, const char *format, va_list *args);
int				ft_printf(const char *restrict format, ...);
int				ft_fprintf(int fd, const char *restrict format, ...);
char			parse_flags(const char *format, size_t *pos);
char			parse_specifier(const char *format, size_t *pos);
int				parse_width(const char *format, size_t *pos, va_list *args);
int				parse_precision(const char *format, size_t *pos, va_list *args);
int				parse_length(const char *format, size_t *pos);
size_t			get_string(int fd, const char *format1, size_t *pos,
				va_list *args);
t_format		parse_format(const char *format, size_t *pos, va_list *args);
size_t			dispatcher_(t_format info, va_list *args);
size_t			c_handler(t_format	info, va_list *args);
size_t			s_handler(t_format info, va_list *args);
size_t			p_handler(t_format info, va_list *args);
size_t			d_handler(t_format info, va_list *args);
size_t			u_handler(t_format info, va_list *args);
size_t			o_handler(t_format info, va_list *args);
size_t			x_handler(t_format info, va_list *args);
size_t			f_handler(t_format info, va_list *args);
size_t			xx_handler(t_format info, va_list *args);
size_t			ps_handler(t_format info, va_list *args);
char			*ft_padding(char *str, char c, int size);
char			*itoa_base(intmax_t num, char *buffer, int base);
char			*uitoa_base(uintmax_t num, char *buffer, int base, char a);
char			*str_precision(t_format info, char *str);
char			*str_width(t_format info, char *str);
char			*f_precision(t_format info, char *str, intmax_t *v);
char			*manage_f_strs(t_format info, char *left, char *right,
				intmax_t i);
char			*manage_f_width(t_format info, char *str, char p_c);
char			*handle_remaider(char *str, int pos, int *rem);
#endif
