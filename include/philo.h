/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 15:13:34 by cvidon            #+#    #+#             */
/*   Updated: 2022/08/08 18:01:08 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* portability */
# define _DEFAULT_SOURCE
# define _GNU_SOURCE
# define _BSD_SOURCE

/*
 ** =========[ Includes ]==========
 */

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

/*
 ** =========[ Enum ]==============
 */

/* Simulator's mutexes */

typedef enum e_mutexes
{
	PRINT,
	MEALS,
	DONE,
	DIED,
	M_NUM
}	t_mutexes;

/* Booleans */

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

/* Exit codes */

typedef enum e_exit
{
	SUCCESS,
	FAILURE
}	t_exit;

/*
 ** =========[ Structures ]========
 */

/*
 ** @brief      Simulator's data.
 **
 ** @var        philo_nb the number of philosophers.
 ** @var        time_die the philosophers time to die (in ms).
 ** @var        time_eat the philosophers time to eat (in ms).
 ** @var        time_slp the philosophers time to sleep (in ms).
 ** @var        time_thk the philosophers time to think (in ms).
 ** @var        must_eat the maximum number of times each philo must eat.
 **
 ** @var        simbegin the Epoch time when the simulation starts.
 ** @var        done is true when all philos ate must_eat times, sim stops.
 ** @var        died is true when one philo died, simulation stops.
 ** @var        mutex an array of mutexes for the simulation operations.
 */

typedef struct s_data
{
	int					philo_nb;
	int					time_die;
	int					time_eat;
	int					time_slp;
	int					time_thk;
	int					must_eat;

	unsigned long		simbegin;
	int					done;
	int					died;
	pthread_mutex_t		*mutex;

}					t_data;

/*
 ** @brief      Simulation's data.
 **
 ** @var        id the name of the philosopher.
 ** @var        last_meal the Epoch time of the last meal eaten.
 ** @var        meals_counter the number of meals eaten.
 ** @var        fork a mutex that symbolize one fork from philos dining problem.
 ** @var        data the access to s_data parameters.
 */

typedef struct s_philo
{
	int					id;
	unsigned long		last_meal;
	int					meals_counter;
	int					lfork;
	int					rfork;
	pthread_mutex_t		*fork;
	t_data				*data;

}				t_philo;

/*
 ** =========[ Prototypes ]========
 */

/*
 ** utils.c
 */

long			ft_atol(char const *str);
int				ft_min(int a, int b);
int				ft_max(int a, int b);

/*
 ** sim_utils.c
 */

void			ft_print(t_philo *philo, char const *const a);
void			ft_died(t_data *data);
void			ft_done(t_data *data);
int				ft_check_died(t_philo *philo);
int				ft_check_done(t_philo *philo);

/*
 ** time_utils.c
 */

unsigned long	ft_abs_time(void);
unsigned long	ft_rel_time(unsigned long begin);
void			ft_msleep(unsigned long msec);

/*
 ** simulation.c
 **
 ** @brief      Define each philosopher (threads) life cycle.
 */

/* int  		ft_start_eating(t_philo *philo); */
/* int  		ft_finish_eating(t_philo *philo); */
/* int  		ft_eating(t_philo *philo); */
void			*ft_simulation(void *arg);

/*
 ** simulator.c
 **
 ** @brief      Generate, manage and destroy the simulation required threads.
 */

/* void 		ft_destroy_mutexes(t_philo *philo, t_data *data) */
/* bool 		ft_are_done(t_philo *philo, t_data *data) */
/* int  		ft_monitor(t_philo *philo, t_data *data) */
int				ft_simulator(t_philo *philo, t_data *data);

/*
 ** init.c
 **
 ** @brief      Initialize the C structures.
 */

int				ft_init_philo(t_philo **philo, t_data *data);
int				ft_init_data_mutexes(t_data **data);
int				ft_init_data(t_data **data, int ac, char const *const *av);
int				ft_init(t_philo **p, t_data **d, int ac, char const *const *av);

/*
 ** checkargs.c
 **
 ** @brief      Protect and make sure the user given parameters are valid.
 */

/* bool			ft_is_numeric(char const *str) */
int				ft_check_args(int ac, char const *const *argv);

/*
 ** main.c
 */

/* void			ft_clear_memory(t_philo *philo, t_data *data) */
/* bool			ft_edgecases(int ac, char const *const *argv) */
int				main(int ac, char const *const *argv);

#endif
