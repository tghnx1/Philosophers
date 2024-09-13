/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:12:40 by drabadan          #+#    #+#             */
/*   Updated: 2024/09/12 14:50:11 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
} t_input;

typedef struct s_philo
{
	int number;
	int time_starving;
	int time_eating;
	int time_sleeping;
	pthread_mutex_t *fork;
	pthread_t *philos;
	int simutation_is_over;
	t_input input;

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
void ft_threads_def(t_philo *philo);
long ft_timestamp(void);
void ft_threads_join(t_philo *philo, pthread_t monitor);
void ft_threads_detach(t_philo *philo);
void ft_forks_def(t_philo **phil);
void *ft_dinner(void *temp);
void *ft_eat(t_philo *philo);
void *ft_sleep(t_philo *philo);
void ft_take_forks(t_philo *philo);
void ft_put_forks(t_philo *philo);
void ft_free(t_philo *philo, int code);
#endif
