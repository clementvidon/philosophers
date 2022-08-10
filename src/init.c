/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 14:58:08 by cvidon            #+#    #+#             */
/*   Updated: 2022/08/08 18:17:02 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 ** @brief      Init s_philo an array of philosophers.
 **
 ** @param[in]	philo a pointer to s_philo struct set to NULL.
 ** @param[in]	data a pointer to an initialized s_data struct.
 ** @return		0 if everything went well, otherwise 1.
 */

int	ft_init_philo(t_philo **philo, t_data *data)
{
	pthread_mutex_t	*fork;
	int				i;

	fork = malloc (sizeof (pthread_mutex_t) * ((size_t)data->philo_nb));
	if (fork == NULL)
		return (FAILURE);
	i = 0;
	while (i < data->philo_nb)
		pthread_mutex_init (&fork[i++], NULL);
	i = 0;
	while (i < data->philo_nb)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].meals_counter = 0;
		(*philo)[i].last_meal = ft_abs_time ();
		(*philo)[i].fork = fork;
		(*philo)[i].data = data;
		i++;
	}
	return (SUCCESS);
}

/*
 ** @brief      Init s_data the simulator's mutexes.
 **
 ** To make it very easy to add a mutex without losing readability despite the
 ** array, the amount of mutexes and their name is definied in the header file.
 **
 ** @param[in]	data a pointer to an initialized s_data struct.
 ** @return		0 if everything went well, otherwise 1.
 */

int	ft_init_data_mutexes(t_data **data)
{
	pthread_mutex_t	*mutex;
	int				i;

	mutex = malloc (sizeof (pthread_mutex_t) * ((size_t)M_NUM));
	if (mutex == NULL)
		return (FAILURE);
	i = 0;
	while (i < M_NUM)
		pthread_mutex_init (&mutex[i++], NULL);
	(*data)->mutex = mutex;
	return (SUCCESS);
}

/*
 ** @brief      Init s_data the simulator's data.
 **
 ** @param[in]	data a pointer to s_data struct set to NULL.
 ** @param[in]	ac the number of arguments given at program start.
 ** @param[in]	av the arguments given at program start.
 ** @return		0 if everything went well, otherwise 1.
 */

int	ft_init_data(t_data **data, int ac, char **av)
{
	(*data)->simstart = ft_abs_time ();
	if ((*data)->simstart == FAILURE)
		return (FAILURE);
	(*data)->philo_nb = (int)ft_atol (av[1]);
	(*data)->time_die = (int)ft_atol (av[2]);
	(*data)->time_eat = (int)ft_atol (av[3]);
	(*data)->time_slp = (int)ft_atol (av[4]);
	if (ac == 5)
		(*data)->must_eat = -1;
	if (ac == 6)
		(*data)->must_eat = (int)ft_atol (av[5]);
	(*data)->createko = false;
	(*data)->done = false;
	(*data)->died = false;
	if (ft_init_data_mutexes (data))
		return (FAILURE);
	return (SUCCESS);
}

/*
 ** @brief		Initialize the structs.
 **
 ** @param[in]	philo a pointer to s_philo struct set to NULL.
 ** @param[in]	data a pointer to s_data struct set to NULL.
 ** @param[in]	ac the number of arguments given at program start.
 ** @param[in]	av the arguments given at program start.
 ** @return		0 if everything went well, otherwise 1.
 */

int	ft_init(t_philo **philo, t_data **data, int ac, char **av)
{
	*data = (t_data *)malloc (sizeof (t_data));
	if (*data == NULL)
		return (FAILURE);
	(*data)->mutex = NULL;
	if (ft_init_data (data, ac, av) != SUCCESS)
		return (FAILURE);
	*philo = (t_philo *)malloc (sizeof (t_philo) * (size_t)(*data)->philo_nb);
	if (*philo == NULL)
		return (FAILURE);
	(*philo)->fork = NULL;
	if (ft_init_philo (philo, *data) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
