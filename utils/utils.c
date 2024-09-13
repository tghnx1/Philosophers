/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:53:45 by mkokorev          #+#    #+#             */
/*   Updated: 2024/09/12 14:56:44 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

t_philo *ft_philos_def(t_input input)
{
	t_philo *philo;
	int i;

	i = 0;
	philo = (t_philo *)malloc((input.number_of_philosophers) * sizeof(t_philo));
	if (!(philo))
		return (NULL);
	while (i < input.number_of_philosophers)
	{
		philo[i].number = i + 1;
		philo[i].input = input;
		philo[i].time_eating = 0;
		philo[i].time_sleeping = 0;
		philo[i].time_eating = 0;
		philo[i].simutation_is_over = 0;
		i++;
	}
	return (philo);
}

void ft_threads_join(t_philo *philo, pthread_t monitor)
{
	int i;

	i = 0;
	while (i < philo->input.number_of_philosophers)
	{
		if (pthread_join(philo->philos[i], NULL) != 0)
		{
			perror("pthread_join");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	if (pthread_join(monitor, NULL) != 0)
	{
		perror("pthread_join");
		exit(EXIT_FAILURE);
	}
}

void ft_threads_detach(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->input.number_of_philosophers)
	{
		write(1, "detaching\n", 10);
		if (!pthread_detach(philo->philos[i]))
		{
			perror("pthread_detach");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void ft_forks_def(t_philo **phil)
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
		perror("fork allocate:");
		exit(EXIT_FAILURE);
	}
	while (i < philo->input.number_of_philosophers)
	{
		if (pthread_mutex_init(&fork[i], NULL) != 0)
		{
			ft_free(philo, 111);
			perror("mutex init:");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	while (i < philo->input.number_of_philosophers)
	{
		philo[i].fork = fork;
		i++;
	}
	return;
}
