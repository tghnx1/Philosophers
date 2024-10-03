/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:04:08 by mkokorev          #+#    #+#             */
/*   Updated: 2024/10/03 11:47:10 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

int ft_mutex(pthread_mutex_t *mutex, char *code, t_philo *philo)
{
	if (!ft_strcmp("UNLOCK", code))
	{
		if (pthread_mutex_unlock(mutex))
		{
			ft_free(philo, 111);
			// printf("Mutex unlock error :(\n");
			return (0);
		}
		// printf("%ld mutex unlocked: %p\n", ft_timestamp(&philo), mutex);
		return (1);
	}
	if (!ft_strcmp("LOCK", code))
	{
		if (pthread_mutex_lock(mutex))
		{
			ft_free(philo, 111);
			// printf("Mutex lock error :(\n");
			return (0);
		}
		// printf("%ld mutex locked: %p\n", ft_timestamp(&philo), mutex);
		return (1);
	}
	if (!ft_strcmp("DESTROY", code))
	{
		if (pthread_mutex_destroy(mutex) != 0)
		{
			ft_free(philo, 111);
			// ft_mut_printf(philo, "Mutex destroy error :(\n");
			return (0);
		}
		// printf("%ld destroyed\n", ft_timestamp(&philo));
		return (1);
	}
	if (!ft_strcmp("INIT", code))
	{
		if (pthread_mutex_init(mutex, NULL) != 0)
		{
			ft_free(philo, 111);
			// printf("Mutex init error :(\n");
			return (0);
		}
		// printf("initiated\n");
		return (1);
	}
	return (0);
}

int ft_forks_def(t_philo **phil)
{
	int i;
	pthread_mutex_t *fork;
	t_philo *philo;

	philo = *phil;
	i = 0;
	fork = (pthread_mutex_t *)malloc(philo->input.number_of_philosophers * sizeof(pthread_mutex_t));
	if (!fork)
	{
		ft_free(philo, 101);
		printf("fork allocate error\n");
		return (0);
	}
	while (i < philo->input.number_of_philosophers)
	{
		if (!ft_mutex(&fork[i], "INIT", philo))
			return (0);
		i++;
	}
	i = 0;
	while (i < philo->input.number_of_philosophers)
	{
		philo[i].fork = fork;
		i++;
	}
	return (1);
}

int ft_mutex_destroy(t_philo **phil)
{
	t_philo *philo;
	int i;

	philo = *phil;
	i = 0;
	while (i < philo->input.number_of_philosophers)
	{
		if (!ft_mutex(&philo->fork[i], "DESTROY", philo))
			return (0);
		i++;
	}
	if (!ft_mutex(philo->simulation_end_mut, "DESTROY", philo) ||
		!ft_mutex(philo->print_mut, "DESTROY", philo) ||
		!ft_mutex(philo->time, "DESTROY", philo) ||
		!ft_mutex(philo->eat, "DESTROY", philo))
		return (0);
	return (1);
}

int ft_other_mut_def(t_philo **phil)
{
	int i;
	t_philo *philo;
	pthread_mutex_t *simulation_mut;
	pthread_mutex_t *print;
	pthread_mutex_t *time;
	pthread_mutex_t *eat;

	philo = *phil;
	simulation_mut = malloc(sizeof(pthread_mutex_t));
	print = malloc(sizeof(pthread_mutex_t));
	time = malloc(sizeof(pthread_mutex_t));
	eat = malloc(sizeof(pthread_mutex_t));
	if (!simulation_mut || !print || !time || !eat)
		return (0);
	if (!ft_mutex(simulation_mut, "INIT", philo) || !ft_mutex(print, "INIT", philo) || !ft_mutex(time, "INIT", philo) || !ft_mutex(eat, "INIT", philo))
		return (0);
	i = 0;
	while (i < philo->input.number_of_philosophers)
	{
		philo[i].simulation_end_mut = simulation_mut;
		philo[i].print_mut = print;
		philo[i].time = time;
		philo[i].eat = eat;
		i++;
	}
	// for (int i = 0; i < 4; i++)
	// {
	// 	printf("Philo %i, mutex initialized %p\n", i, &philo[i].print_mut);
	// }
	return (1);
}

int ft_mutex_def(t_philo **phil)
{
	if (!ft_forks_def(phil) || !ft_other_mut_def(phil))
		return (0);
	return (1);
}
