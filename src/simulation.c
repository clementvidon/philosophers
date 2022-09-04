/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:39:14 by cvidon            #+#    #+#             */
/*   Updated: 2022/08/08 18:43:12 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 ** @brief      The philosopher take the forks.
 **
 ** - Using a "locking hierarchy" to prevent deadlock.
 ** - Handle the 'one philo' case by making sure there are not only one fork on
 **   the table: 'lfork == rfork'.
 **
 ** @param[in]  philo the simulation's struct.
 ** @return     0 if everything went well, otherwise 1.
 */

static int	ft_start_eating(t_philo *philo)
{
	int		lfork;
	int		rfork;

	lfork = philo->id - 1;
	rfork = philo->id % philo->data->philo_nb;
	pthread_mutex_lock (&philo->fork[ft_min (lfork, rfork)]);
	ft_print (philo, "has taken a fork");
	if (lfork == rfork)
	{
		pthread_mutex_unlock (&philo->fork[ft_min (lfork, rfork)]);
		return (FAILURE);
	}
	pthread_mutex_lock (&philo->fork[ft_max (lfork, rfork)]);
	ft_print (philo, "has taken a fork");
	ft_print (philo, "is eating");
	return (SUCCESS);
}

/*
 ** @brief      The philosopher release the forks.
 **
 ** @param[in]  philo the simulation's struct.
 ** @return     0 if everything went well.
 */

static int	ft_finish_eating(t_philo *philo)
{
	int		lfork;
	int		rfork;

	lfork = philo->id - 1;
	rfork = philo->id % philo->data->philo_nb;
	pthread_mutex_unlock (&philo->fork[ft_max (lfork, rfork)]);
	pthread_mutex_unlock (&philo->fork[ft_min (lfork, rfork)]);
	return (SUCCESS);
}

/*
 ** @brief      Philosopher's meal.
 **
 ** - To start to eat, each philosopher needs
 **   his own fork + his left neighbor's one:
 **
 **     RFork Philos LFork
 **     ------------------
 **  (P3) P0  ← P1 →  P1 (self)
 **       P1  ← P2 →  P2 (self)
 **       P2  ← P3 →  P0 (self)
 **     Where F0 belongs to philo P3.
 **
 ** - A meal is considered as +1 meal as soon as it starts.  Even though they
 **   are already considered as 'done' philos that started to eat have to
 **   properly finish eating by passing through 'time_eat'.
 **
 ** @param[in]  philo the simulation's struct.
 ** @return     0 if everything went well, otherwise 1.
 */

static int	ft_eating(t_philo *philo)
{
	if (ft_start_eating (philo) != SUCCESS)
		return (FAILURE);
	pthread_mutex_lock (&philo->data->mutex[MEALS]);
	philo->last_meal = ft_abs_time ();
	philo->meals_counter++;
	pthread_mutex_unlock (&philo->data->mutex[MEALS]);
	if (ft_check_done (philo))
	{
		ft_msleep (philo, (long)philo->data->time_eat);
		ft_finish_eating (philo);
		return (FAILURE);
	}
	ft_msleep (philo, (long)philo->data->time_eat);
	ft_finish_eating (philo);
	return (SUCCESS);
}

/*
 ** @brief      Philosopher's life cycle.
 **
 ** Even philosophers are delayed to prevent any conflict during the forks taking
 ** moment.
 **
 ** @param[in]  arg the simulation's struct.
 ** @return     A NULL pointer.
 */

void	*ft_simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->id % 2 == 0)
	{
		ft_print (philo, "is thinking");
		ft_msleep (philo, (long)philo->data->time_eat);
	}
	while (1)
	{
		if (philo->data->createko)
			break ;
		if (ft_check_died(philo))
			break ;
		if (ft_eating (philo) != SUCCESS)
			break ;
		ft_print (philo, "is sleeping");
		ft_msleep (philo, (long)philo->data->time_slp);
		ft_print (philo, "is thinking");
		if (philo->data->time_slp < philo->data->time_eat)
			ft_msleep(philo, (philo->data->time_eat - philo->data->time_slp) + 1);
		else
			ft_msleep(philo, 1);
	}
	return (NULL);
}
