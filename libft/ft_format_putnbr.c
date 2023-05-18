/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_putnbr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/03/30 14:26:10 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

static int	ft_print_zeroes(char *number, t_buffer *values, int precision)
{
	int	count;

	count = 0;
	if (values->width && values->precision)
	{
		while ((values->width--) > precision + (int)ft_strlen(number))
			count += write(1, " ", 1);
		count += write(1, "-", 1);
		while ((values->precision--) > (int)ft_strlen(number))
			count += write(1, "0", 1);
	}
	else
	{
		count += write(1, "-", 1);
		while ((values->width--) > (int)ft_strlen(number))
			count += write(1, "0", 1);
		while ((values->precision--) > (int)ft_strlen(number))
			count += write(1, "0", 1);
	}
	count += ft_putstr(number + 1);
	return (count);
}

static int	ft_print_width(char *number, t_buffer *values, int precision)
{
	int	count;

	count = 0;
	if (values->width && values->precision)
	{
		while ((values->width--) > precision)
			count += write(1, " ", 1);
		count += write(1, "-", 1);
		while ((values->precision--) > (int)ft_strlen(number) - 1)
			count += write(1, "0", 1);
	}
	else
	{
		while ((values->width--) > (int)ft_strlen(number))
			count += write(1, " ", 1);
		count += write(1, "-", 1);
		while ((values->precision--) > (int)ft_strlen(number) - 1)
			count += write(1, "0", 1);
	}
	count += ft_putstr(number + 1);
	return (count);
}

static int	ft_print_minus_width(char *number, t_buffer *values, int precision)
{
	int	count;

	count = 0;
	if (values->width && values->precision)
	{
		count += write(1, "-", 1);
		while ((values->precision--) > (int)ft_strlen(number) - 1)
			count += write(1, "0", 1);
		count += ft_putstr(number + 1);
		while ((values->width--) > precision)
			count += write(1, " ", 1);
	}
	else
	{
		count += write(1, "-", 1);
		while ((values->precision--) > (int)ft_strlen(number) - 1)
			count += write(1, "0", 1);
		count += ft_putstr(number + 1);
		while ((values->width--) > (int)ft_strlen(number))
			count += write(1, " ", 1);
	}
	return (count);
}

int	ft_format_putnbr(t_buffer *values, long long nb)
{
	int		count;
	char	*number;
	int		precision;

	count = 0;
	if (nb >= 0)
		count += ft_format_putposnbr(values, nb);
	else
	{
		number = ft_itoa(nb);
		precision = values->precision + 1;
		if (values->minus)
			count += ft_print_minus_width(number, values, precision);
		else if (values->zero)
			count += ft_print_zeroes(number, values, precision);
		else
			count += ft_print_width(number, values, precision);
		free(number);
	}
	return (count);
}
