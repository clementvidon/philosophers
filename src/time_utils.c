/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 17:46:49 by cvidon            #+#    #+#             */
/*   Updated: 2022/08/08 18:00:42 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 ** @brief          Return the elapsed time since EPOCH.
 **
 ** @return         the elapsed time since EPOCH in millisecond.
 */

unsigned long	ft_abs_time(void)
{
	struct timeval	time;
	unsigned long	s;
	unsigned long	u;

	if (gettimeofday (&time, NULL) == -1)
	{
		dprintf (2, "Error: 'gettimeofday' fail.\n");
		return (FAILURE);
	}
	s = (unsigned long)(time.tv_sec * 1000);
	u = (unsigned long)(time.tv_usec / 1000);
	return (s + u);
}

/*
 ** @brief          Return the time elapsed since simulation start.
 **
 ** @return         the time elapsed since simulation start in millisecond.
 */

unsigned long	ft_rel_time(t_philo *philo)
{
	unsigned long	abs_time;

	abs_time = ft_abs_time ();
	if (abs_time == FAILURE)
		return (FAILURE);
	return (abs_time - philo->data->simstart);
}

/*
 ** @brief          Millisecond sleep.
 **
 ** Like 'usleep' function but millisecond instead of microsecond.
 */

void	ft_msleep(t_philo *philo, long duration)
{
	long	start;
	long	current;

	start = (long) ft_abs_time ();
	if (start == FAILURE)
		return ;
	while (1)
	{
		current = (long) ft_abs_time () - start;
		if (current >= duration)
			break ;
		if (duration - current > 1000)
			usleep (100);
		else
			usleep ((unsigned int)((duration - current) / 10));
		pthread_mutex_lock (&philo->data->mutex[DIED]);
		if (philo->data->died)
			return ((void)pthread_mutex_unlock (&philo->data->mutex[DIED]));
		pthread_mutex_unlock (&philo->data->mutex[DIED]);
		pthread_mutex_lock (&philo->data->mutex[DONE]);
		if (philo->data->done)
			return ((void)pthread_mutex_unlock (&philo->data->mutex[DONE]));
		pthread_mutex_unlock (&philo->data->mutex[DONE]);
	}
}
