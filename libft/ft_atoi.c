/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beeligul <beeligul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 18:54:13 by beeligul          #+#    #+#             */
/*   Updated: 2024/01/02 18:54:13 by beeligul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	long	result;
	int		a;

	while (*nptr == '\n' || *nptr == '\t' || *nptr == '\r' \
	|| *nptr == '\v' || *nptr == '\f' || *nptr == ' ')
		nptr++;
	a = *nptr == '-';
	nptr += (a || *nptr == '+');
	result = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = (result * 10) + *nptr++ - '0';
		if (result > 2147483647 && a == 0)
			return (-1);
		if (result > 2147483648U && a == 1)
			return (0);
	}
	return (result * ((a * -2) + 1));
}
