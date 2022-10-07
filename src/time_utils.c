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
 ** TODO
 ** Handle 'gettimeofday' errors cause they are
 ** triggerable from the user's side.
 **
 ** @return         The elapsed time since EPOCH in millisecond.
 */

unsigned long	ft_abs_time(void)
{
	struct timeval	time;
	unsigned long	s;
	unsigned long	u;

	if (gettimeofday (&time, NULL) == -1)
	{
		write (2, "Error: 'gettimeofday' fail.\n", 28);
		return (FAILURE);
	}
	s = time.tv_sec * 1000;
	u = time.tv_usec / 1000;
	return (s + u);
}

/*
 ** @brief          Return the time elapsed since simulation start.
 **
 ** @param[in]      philo the simulation's struct.
 ** @return         The time elapsed since simulation start in millisecond.
 */

unsigned long	ft_rel_time(unsigned long begin)
{
	unsigned long	abs_time;

	abs_time = ft_abs_time ();
	if (abs_time == FAILURE)
		return (FAILURE);
	return (abs_time - begin);
}

/*
 ** @brief          Millisecond sleep.
 **
 ** Like 'usleep' function but millisecond instead of microsecond.
 **
 ** @param[in]      philo the simulation's struct.
 ** @param[in]      duration the sleep duration in millisecond.
 */

void	ft_msleep(t_philo *philo, unsigned long msec)
{
	const unsigned long	toreach = ft_rel_time (philo->data->simbegin) + msec;
	unsigned long		current;

	while (1)
	{
		current = ft_rel_time (philo->data->simbegin);
		if (current >= toreach)
			return ;
		usleep(10);
	}
}
