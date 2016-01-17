/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_8.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <mfroehly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/17 08:14:56 by mfroehly          #+#    #+#             */
/*   Updated: 2016/01/17 08:15:05 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long int	ft_atoi_8(const char *str)
{
	long int	number;
	int			signe;

	number = 0;
	signe = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
						|| *str == '\r' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signe *= -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		number *= 10;
		number += (*str - 48);
		str++;
	}
	number *= signe;
	return (number);
}
