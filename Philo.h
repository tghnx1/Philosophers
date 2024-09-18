/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:12:40 by drabadan          #+#    #+#             */
/*   Updated: 2024/09/18 16:00:38 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// cc *.c ./utils/*.c -pthread

// docker run -it -v ${pwd}:/home/root ubuntu

// when philos are full and algoritm of avoiding the death are left, and don't print additionalstupid stuff to the terminal

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_input
{
	int number_of_philosophers;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
} t_input;

typedef struct s_philo
{
	int number;
	long time_starving;
	long time_eating;
	long time_sleeping;
	pthread_mutex_t *fork;
	pthread_mutex_t simulation_end_mut;
	pthread_t *philos;
	int simutation_is_over;
	t_input input;
	long timestart;
	long woke_up_time;
	int dead;
	int eating_sleeping;
	int ate_num;
	int full;

} t_philo;

typedef struct s_fork
{
	int number;
	long time_starving;
	long time_eating;
	long time_sleeping;
	t_input input;

} t_fork;

int ft_atoi(const char *nptr);
int ft_parce(int argc, char **argv, t_input *input);
t_philo *ft_philos_def(t_input input);
void ft_threads_def(t_philo **phil);
long ft_time(void);
void ft_threads_join(t_philo *philo, pthread_t monitor);
void ft_threads_detach(t_philo *philo);
void ft_forks_def(t_philo **phil);
void *ft_dinner(void *temp);
int ft_eat(t_philo *philo);
int ft_sleep(t_philo *philo);
int ft_take_forks(t_philo *philo);
int ft_put_forks(t_philo *philo);
void ft_free(t_philo *philo, int code);
void ft_forks_def(t_philo **phil);
void ft_mutex_destroy(t_philo **philo);
long ft_time_start(t_philo *philo);
long ft_timestamp(t_philo **phil);
void ft_mutex_def(t_philo **phil);
int ft_die_check(t_philo *philo, int i);
void ft_get_starving_time(t_philo *philo, int i);
void ft_sim_is_over(t_philo *philo, int philo_num);

#endif
