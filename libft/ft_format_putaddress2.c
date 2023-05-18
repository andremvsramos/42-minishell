/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_putaddress2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andvieir <andvieir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:15:48 by andvieir          #+#    #+#             */
/*   Updated: 2023/03/30 14:25:59 by andvieir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

int	ft_paddmw1(char *hexastr, t_buffer *values, int precision, int len)
{
	int	count;

	count = 0;
	if (values->space)
			count += write(1, " ", 1);
	if (values->plus)
			count += write(1, "+", 1);
	if (ft_strncmp(hexastr, "(nil)", 6))
	{
		count += write(1, "0x", 2);
		len += 2;
	}
	while ((values->precision--) > (int)ft_strlen(hexastr))
		count += write(1, "0", 1);
	count += ft_putstr(hexastr);
	while ((values->width--) > precision)
		count += write(1, " ", 1);
	return (count);
}

int	ft_paddz2(char *hexastr, t_buffer *values, int len)
{
	int	count;

	count = 0;
	if (values->space)
		count += write(1, " ", 1);
	if (values->plus)
		count += write(1, "+", 1);
	if (ft_strncmp(hexastr, "(nil)", 6))
	{
		count += write(1, "0x", 2);
		len += 2;
	}
	while ((values->width--) > len)
		count += write(1, "0", 1);
	while ((values->precision--) > len)
		count += write(1, "0", 1);
	return (count);
}

int	ft_paddz1(char *hexastr, t_buffer *values, int precision, int len)
{
	int	count;

	count = 0;
	while ((values->width--) > precision)
		count += write(1, " ", 1);
	if (values->space)
		count += write(1, " ", 1);
	if (values->plus)
		count += write(1, "+", 1);
	if (ft_strncmp(hexastr, "(nil)", 6))
	{
		count += write(1, "0x", 2);
		len += 2;
	}
	while ((values->precision--) > (int)ft_strlen(hexastr))
		count += write(1, "0", 1);
	return (count);
}

int	ft_paddw2(char *hexastr, t_buffer *values, int len)
{
	int	count;

	count = 0;
	while ((values->width--) > len)
		count += write(1, " ", 1);
	if (values->space)
		count += write(1, " ", 1);
	if (values->plus)
		count += write(1, "+", 1);
	if (ft_strncmp(hexastr, "(nil)", 6))
		count += write(1, "0x", 2);
	while ((values->precision--) > (int)ft_strlen(hexastr))
		count += write(1, "0", 1);
	return (count);
}

int	ft_paddw1(char *hexastr, t_buffer *values, int precision, int len)
{
	int	count;

	count = 0;
	while ((values->width--) > precision)
		count += write(1, " ", 1);
	if (values->space)
		count += write(1, " ", 1);
	if (values->plus)
		count += write(1, "+", 1);
	if (ft_strncmp(hexastr, "(nil)", 6))
	{
		count += write(1, "0x", 2);
		len += 2;
	}
	while ((values->precision--) > (int)ft_strlen(hexastr))
		count += write(1, "0", 1);
	return (count);
}
