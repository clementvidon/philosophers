/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:43:05 by cvidon            #+#    #+#             */
/*   Updated: 2022/08/08 15:48:44 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 ** @brief      Clear all the program dynamically allocated memory.
 **
 ** @param[in]  philo the simulation's struct.
 ** @param[in]  data the simulator's struct.
 */

static void	ft_clear_memory(t_philo *philo, t_data *data)
{
	if (data && data->mutex)
		free (data->mutex);
	if (data)
		free (data);
	if (philo && philo->fork)
		free (philo->fork);
	if (philo)
		free (philo);
}

/*
 ** @brief      Handle edge cases.
 **
 ** If the 'must_eat' parameter is set to 0. Or if there is only one
 ** philosopher.
 **
 ** @param[in]  ac the number of arguments given at program start.
 ** @param[in]  av the arguments given at program start.
 ** @return     1 if there are no matching edge case, otherwise 0.
 */

static bool	ft_edgecases(int ac, char const *const *av)
{
	if ((ac == 6 && ft_atol (av[5]) == 0))
		return (true);
	if (ft_atol (av[1]) == 0)
		return (true);
	return (false);
}

/*
 ** @brief      Start and terminate the program.
 **
 ** Input info:
 **  ./philo philo_nb time_die time_eat time_slp [ must_eat ]
 **  Example: ./philo 4 410 200 200 7
 **
 ** @param[in]  ac the number of arguments given at program start.
 ** @param[in]  av the arguments given at program start.
 ** @return     0 if everything went well, otherwise 1.
 */

int	main(int ac, char const *const *av)
{
	t_data	*data;
	t_philo	*philo;

	data = NULL;
	philo = NULL;
	if (ft_check_args (ac, av) != SUCCESS)
		return (ft_clear_memory (philo, data), EXIT_FAILURE);
	if (ft_edgecases (ac, av))
		return (ft_clear_memory (philo, data), EXIT_SUCCESS);
	if (ft_init (&philo, &data, ac, av) != SUCCESS)
		return (ft_clear_memory (philo, data), EXIT_FAILURE);
	if (ft_simulator (philo, data) != SUCCESS)
		return (ft_clear_memory (philo, data), EXIT_FAILURE);
	return (ft_clear_memory (philo, data), EXIT_SUCCESS);
}
