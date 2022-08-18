/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:51:00 by gudias            #+#    #+#             */
/*   Updated: 2022/01/14 16:51:49 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include<stdlib.h>
# include<stdarg.h>
# include<unistd.h>

typedef struct s_flags
{
	int		left_justify;
	int		zero_padding;
	int		hex_prefix;
	int		sign;
	int		space;
	int		width;
	int		precision;
	char	specifier;	
}		t_flags;

int		ft_printf(const char *str, ...);

int		ft_print(va_list ap, t_flags *flags);

int		ft_format_c(va_list ap, t_flags *flags);
int		ft_format_s(va_list ap, t_flags *flags);
int		ft_format_n(va_list ap, t_flags *flags);
int		ft_format_x(va_list ap, t_flags *flags);
int		ft_format_p(va_list ap, t_flags *flags);

t_flags	*get_flags(const char **str, t_flags *flags);

int		ft_putchar_count(char c);
int		ft_putstr_count(char *str);
int		ft_putnbr_count(unsigned int nb);
int		ft_puthex_count(unsigned long nb, int maj);

#endif
