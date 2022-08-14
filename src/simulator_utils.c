/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 17:50:32 by cvidon            #+#    #+#             */
/*   Updated: 2022/08/08 18:00:49 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 ** @brief      Log each philosopher's life cycle actions into the terminal.
 **
 ** @param[in]  philo the simulation's struct.
 */

void	ft_print(t_philo *philo, char const *const action)
{
	bool	stop_printing;

	if (philo->data->createko == true)
		return ;
	pthread_mutex_lock (&philo->data->mutex[DONE]);
	stop_printing = philo->data->done;
	pthread_mutex_unlock (&philo->data->mutex[DONE]);
	pthread_mutex_lock (&philo->data->mutex[DIED]);
	stop_printing += philo->data->died;
	pthread_mutex_unlock (&philo->data->mutex[DIED]);
	pthread_mutex_lock (&philo->data->mutex[PRINT]);
	if (*action == 'd' || !stop_printing)
		printf ("%lu %i %s\n", ft_rel_time (philo), philo->id, action);
	pthread_mutex_unlock (&philo->data->mutex[PRINT]);
}

/*
 ** @brief      Officialise the first blood.
 **
 ** @param[in]  data the simulator's struct.
 */

void	ft_died(t_data *data)
{
	pthread_mutex_lock (&data->mutex[DIED]);
	data->died = true;
	pthread_mutex_unlock (&data->mutex[DIED]);
}

/*
 ** @brief      Officialise the fact that all the philosophers ate at least
 **             'must_eat' times.
 **
 ** @param[in]  data the simulator's struct.
 */

void	ft_done(t_data *data)
{
	pthread_mutex_lock (&data->mutex[DONE]);
	data->done = true;
	pthread_mutex_unlock (&data->mutex[DONE]);
}
