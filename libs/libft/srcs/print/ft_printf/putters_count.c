/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putters_count.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:51:42 by gudias            #+#    #+#             */
/*   Updated: 2022/01/14 17:04:02 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_count(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr_count(char *str)
{
	int	count;

	if (!str)
		return (0);
	count = 0;
	while (*str)
	{
		write(1, str, 1);
		str++;
		count++;
	}
	return (count);
}

int	ft_putnbr_count(unsigned int nb)
{
	char	c;
	int		count;

	count = 0;
	if (nb > 9)
	{
		count += ft_putnbr_count(nb / 10);
		c = (nb % 10) + '0';
	}
	else
	{
		c = nb + '0';
	}
	write(1, &c, 1);
	count++;
	return (count);
}

int	ft_puthex_count(unsigned long nb, int maj)
{
	char	c;
	int		count;

	count = 0;
	if (nb > 15)
	{
		count += ft_puthex_count(nb / 16, maj);
		count += ft_puthex_count(nb % 16, maj);
	}
	else
	{
		if (nb < 10)
			c = nb + '0';
		else
		{
			c = (nb - 10) + 'a';
			if (maj)
				c -= 32;
		}
		write(1, &c, 1);
		count++;
	}
	return (count);
}
