/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 17:55:59 by cvidon            #+#    #+#             */
/*   Updated: 2022/08/08 17:55:59 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 ** @brief      Convert a numerical string to a long integer value.
 **
 ** @param[in]  str the numerical string to convert.
 ** @return     a long integer value.
 */

long	ft_atol(char const *str)
{
	long	sign;
	long	nb;

	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	nb = 0;
	while (*str && (*str >= '0' && *str <= '9'))
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	return (nb * sign);
}

/*
 ** @brief      Max value.
 **
 ** @param[in]  a a value.
 ** @param[in]  b a different another value.
 ** @return     The biggest value.
 */

int	ft_max(int a, int b)
{
	if (b > a)
		return (b);
	return (a);
}

/*
 ** @brief      Min value.
 **
 ** @param[in]  a a value.
 ** @param[in]  b a different value.
 ** @return     The smallest value.
 */

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}
