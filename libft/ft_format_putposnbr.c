/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_putposnbr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/03/30 14:26:14 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

static int	ft_print_zeroes(char *number, t_buffer *values, int precision)
{
	int	count;

	count = 0;
	if (values->space)
		count += write(1, " ", 1);
	if (values->plus)
		count += write(1, "+", 1);
	if (values->width && values->precision)
	{
		while ((values->width--) > precision + (int)ft_strlen(number))
			count += write(1, " ", 1);
		while ((values->precision--) > (int)ft_strlen(number))
			count += write(1, "0", 1);
	}
	else
	{
		while ((values->width--) > (int)ft_strlen(number))
			count += write(1, "0", 1);
		while ((values->precision--) > (int)ft_strlen(number))
			count += write(1, "0", 1);
	}
	count += ft_putstr(number);
	return (count);
}

static int	ft_print_width(char *number, t_buffer *values, int precision)
{
	int	count;
	int	len;

	count = 0;
	len = ft_strlen(number);
	if (values->space || values->plus)
		len++;
	if (values->width && values->precision)
	{
		while ((values->width--) > precision)
			count += write(1, " ", 1);
		while ((values->precision--) > (int)ft_strlen(number))
			count += write(1, "0", 1);
	}
	else
		count += ft_print_posnbrw2(number, values, len);
	if (values->space)
		count += write(1, " ", 1);
	if (values->plus)
		count += write(1, "+", 1);
	count += ft_putstr(number);
	return (count);
}

static int	ft_print_minus_width2(char *number, t_buffer *values)
{
	int	count;

	count = 0;
	while ((values->precision--) > (int)ft_strlen(number))
		count += write(1, "0", 1);
	count += ft_putstr(number);
	while ((values->width--) > (int)ft_strlen(number))
		count += write(1, " ", 1);
	return (count);
}

static int	ft_print_minus_width(char *number, t_buffer *values, int precision)
{
	int	count;

	count = 0;
	if (values->plus || values->space)
		precision++;
	if (values->space)
		count += write(1, " ", 1);
	if (values->plus)
		count += write(1, "+", 1);
	if (values->width && values->precision)
	{
		while ((values->precision--) > (int)ft_strlen(number))
			count += write(1, "0", 1);
		count += ft_putstr(number);
		while ((values->width--) > precision)
			count += write(1, " ", 1);
	}
	else
		count += ft_print_minus_width2(number, values);
	return (count);
}

int	ft_format_putposnbr(t_buffer *values, unsigned long long nb)
{
	int		count;
	char	*number;
	int		precision;

	count = 0;
	number = ft_utoa(nb);
	precision = values->precision;
	if (values->minus)
		count += ft_print_minus_width(number, values, precision);
	else if (values->zero)
		count += ft_print_zeroes(number, values, precision);
	else
		count += ft_print_width(number, values, precision);
	free(number);
	return (count);
}
