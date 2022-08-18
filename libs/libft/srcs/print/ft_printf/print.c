/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:02:50 by gudias            #+#    #+#             */
/*   Updated: 2022/01/14 17:03:33 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print(va_list ap, t_flags *flags)
{
	int	count;

	if (!flags || !ap)
		return (0);
	count = 0;
	if (flags->specifier == 'c' || flags->specifier == '%')
		count = ft_format_c(ap, flags);
	else if (flags->specifier == 's')
		count = ft_format_s(ap, flags);
	else if (flags->specifier == 'd' || flags->specifier == 'i')
		count = ft_format_n(ap, flags);
	else if (flags->specifier == 'u')
		count = ft_format_n(ap, flags);
	else if (flags->specifier == 'x' || flags->specifier == 'X')
		count = ft_format_x(ap, flags);
	else if (flags->specifier == 'p')
		count = ft_format_p(ap, flags);
	return (count);
}
