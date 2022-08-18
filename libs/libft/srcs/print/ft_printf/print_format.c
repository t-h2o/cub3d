/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:52:46 by gudias            #+#    #+#             */
/*   Updated: 2022/01/14 17:03:47 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format_c(va_list ap, t_flags *flags)
{
	int	count;

	count = 0;
	if (flags->specifier == 'c')
		count = ft_putchar_count((unsigned char) va_arg(ap, int));
	else
		count = ft_putchar_count('%');
	return (count);
}

int	ft_format_s(va_list ap, t_flags *flags)
{
	int		count;
	char	*s_arg;

	s_arg = va_arg(ap, char *);
	if (!s_arg)
		s_arg = "(null)";
	count = ft_putstr_count(s_arg);
	if (count == 0 && flags->space)
		count = ft_putchar_count(' ');
	return (count);
}

int	ft_format_n(va_list ap, t_flags *flags)
{
	int	count;
	int	arg;

	count = 0;
	if (flags->specifier == 'd' || flags->specifier == 'i')
	{
		arg = va_arg(ap, int);
		if (arg >= 0 && flags->sign)
			count = ft_putchar_count('+');
		else if (arg >= 0 && flags->space)
			count = ft_putchar_count(' ');
		else if (arg < 0)
		{
			count = ft_putchar_count('-');
			arg = -arg;
		}
	}
	else
		arg = va_arg(ap, unsigned int);
	count += ft_putnbr_count(arg);
	return (count);
}

int	ft_format_x(va_list ap, t_flags *flags)
{
	int				count;
	unsigned int	x_arg;

	count = 0;
	x_arg = va_arg(ap, unsigned int);
	if (x_arg)
	{
		if (flags->hex_prefix && flags->specifier == 'X')
			count = ft_putstr_count("0X");
		else if (flags->hex_prefix && flags->specifier == 'x')
			count = ft_putstr_count("0x");
	}
	count += ft_puthex_count(x_arg, flags->specifier == 'X');
	return (count);
}

int	ft_format_p(va_list ap, t_flags *flags)
{
	int				count;
	unsigned long	p_arg;

	(void) flags;
	count = 0;
	p_arg = va_arg(ap, unsigned long);
	if (!p_arg)
		p_arg = 0;
	count = ft_putstr_count("0x");
	count += ft_puthex_count(p_arg, 0);
	return (count);
}
