/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkargs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:54:01 by cvidon            #+#    #+#             */
/*   Updated: 2022/08/08 16:54:02 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 ** @brief      Check if a string looks like a positive numeric value.
 **
 ** @param[in]  str the string to check.
 ** @return     True or false.
 */

static int	ft_is_numeric(char const *str)
{
	int	i;

	i = 0;
	if (*str == '+')
		str++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == '\0')
		return (TRUE);
	return (FALSE);
}

/*
 ** @brief      Check if the user given arguments are valid.
 **
 ** @param[in]  ac the number of arguments given at program start.
 ** @param[in]  av the arguments given at program start.
 ** @return     0 if valid, otherwise 1.
 */

int	ft_check_args(int ac, char const *const *av)
{
	if (ac < 5)
	{
		write (2, "Error: Too few arguments.\n", 26);
		return (FAILURE);
	}
	if (ac > 6)
	{
		write (2, "Error: Too many arguments.\n", 27);
		return (FAILURE);
	}
	while (ac-- > 1)
	{
		if (ft_is_numeric (av[ac]) == FALSE)
		{
			write (2, "Error: Invalid character.\n", 29);
			return (FAILURE);
		}
		if (ft_atol (av[ac]) > INT_MAX || ft_atol (av[ac]) < 0)
		{
			write (2, "Error: Out of range value.\n", 27);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}
