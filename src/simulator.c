/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 15:11:14 by cvidon            #+#    #+#             */
/*   Updated: 2022/08/08 18:12:44 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 ** @brief      Destroy all the mutexes.
 **
 ** @param[in]  philo the simulation's struct.
 ** @param[in]  data the simulator's struct.
 */

static void	ft_destroy_mutexes(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < philo->data->philo_nb)
		pthread_mutex_destroy (&philo->fork[i++]);
	i = 0;
	while (i < M_NUM)
		pthread_mutex_destroy (&data->mutex[i++]);
}

/*
 ** @brief      Check if all philos ate at least 'must_eat' times.
 **
 ** @param[in]  philo the simulation's struct.
 ** @param[in]  data the simulator's struct.
 ** @return     True or false.
 */

static int	ft_are_done(t_philo *philo, t_data *data)
{
	int	i;
	int	done;
	int	meals_count;

	if (data->must_eat == -1)
		return (FALSE);
	i = -1;
	done = -1;
	while (++i < data->philo_nb)
	{
		pthread_mutex_lock (&philo->data->mutex[MEALS]);
		meals_count = philo[i].meals_counter;
		pthread_mutex_unlock (&philo->data->mutex[MEALS]);
		if (meals_count >= data->must_eat)
			if (++done == data->philo_nb - 1)
				return (TRUE);
	}
	return (FALSE);
}

/*
 ** @brief      Continuously check the simulation's termination conditions.
 **
 ** If one death occurs.
 ** If all the philosophers ate at least 'must_eat' times.
 **
 ** @param[in]  philo the simulation's struct.
 ** @param[in]  data the simulator's struct.
 ** @return     0 if everything went well.
 */

static int	ft_monitor(t_philo *philo, t_data *data)
{
	int				i;
	unsigned long	l_meal;

	i = 0;
	while (1)
	{
		pthread_mutex_lock (&data->mutex[MEALS]);
		l_meal = philo[i].last_meal;
		pthread_mutex_unlock (&data->mutex[MEALS]);
		if (l_meal && ft_are_done (philo, data))
		{
			ft_done (data);
			break ;
		}
		if (l_meal && ft_abs_time () - l_meal > (unsigned long)data->time_die)
		{
			ft_died (data);
			ft_print (&philo[i], "died");
			break ;
		}
		i = (i + 1) % data->philo_nb;
		usleep (100); // TODO improve 200 410 200 200 perf
	}
	return (SUCCESS);
}

/*
 ** @brief      Threads manager.
 **
 ** Generate, manage and destroy the simulation required threads.
 **
 ** TODO
 ** Protect 'pthread_create' cause there is a malloc behind.
 **
 ** @param[in]  philo the simulation's struct.
 ** @param[in]  data the simulator's struct.
 ** @return     0 if everything went well, otherwise 1.
 */

int	ft_simulator(t_philo *philo, t_data *data)
{
	int			i;
	pthread_t	*threads;

	threads = malloc (sizeof (pthread_t) * (size_t)data->philo_nb);
	if (threads == NULL)
		return (FAILURE);
	i = -1;
	while (++i < data->philo_nb)
	{
		if (pthread_create (&threads[i], 0, ft_simulation, (void *)&philo[i]))
		{
			while (i--)
				pthread_join (threads[i], NULL);
			return ((void)free (threads), FAILURE);
		}
	}
	if (ft_monitor (philo, data) != SUCCESS)
		return ((void)ft_destroy_mutexes (philo, data), (void)free (threads),
			FAILURE);
	i = -1;
	while (++i < data->philo_nb)
		if (pthread_join (threads[i], NULL))
			return (FAILURE);
	return ((void)ft_destroy_mutexes (philo, data), (void)free (threads),
		SUCCESS);
}
