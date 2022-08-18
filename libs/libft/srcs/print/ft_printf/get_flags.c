/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:51:26 by gudias            #+#    #+#             */
/*   Updated: 2022/01/14 17:03:19 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	is_specifier(char c)
{
	if (c == 'd' || c == 'i' || c == 'u' || c == 'c')
		return (c);
	else if (c == 's' || c == 'x' || c == 'X' || c == 'p' || c == '%')
		return (c);
	return (0);
}

static void	reset_flags(t_flags *flags)
{
	flags->left_justify = 0;
	flags->zero_padding = 0;
	flags->hex_prefix = 0;
	flags->sign = 0;
	flags->space = 0;
	flags->specifier = 0;
	flags->width = 0;
	flags->precision = -1;
}

static int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static void	set_width(int n, t_flags *flags)
{
	if (flags->precision != -1)
		flags->precision = (flags->precision * 10) + n;
	else
		flags->width = (flags->width * 10) + n;
}

t_flags	*get_flags(const char **str, t_flags *flags)
{
	if (!flags || !str)
		return (NULL);
	reset_flags(flags);
	while (!is_specifier(*(++(*str))))
	{
		if (**str == '-')
			flags->left_justify = 1;
		else if (**str == '0' && !is_digit(*(*str - 1)))
			flags->zero_padding = 1;
		else if (**str == '#')
			flags->hex_prefix = 1;
		else if (**str == '+')
			flags->sign = 1;
		else if (**str == ' ')
			flags->space = 1;
		else if (is_digit(**str))
			set_width(**str, flags);
		else if (**str == '.')
			flags->precision = 0;
	}
	flags->specifier = **str;
	return (flags);
}
