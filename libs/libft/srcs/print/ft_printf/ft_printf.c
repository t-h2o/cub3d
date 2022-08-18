/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:50:29 by gudias            #+#    #+#             */
/*   Updated: 2022/01/14 16:52:19 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	ap;
	t_flags	*flags;

	va_start(ap, str);
	count = 0;
	flags = malloc (sizeof (t_flags));
	if (!flags)
		return (0);
	while (*str != '\0')
	{
		if (*str == '%')
		{	
			flags = get_flags(&str, flags);
			count += ft_print(ap, flags);
		}
		else
			count += ft_putchar_count(*str);
		str++;
	}
	va_end(ap);
	free(flags);
	return (count);
}
