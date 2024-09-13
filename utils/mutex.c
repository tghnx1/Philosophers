/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:04:08 by mkokorev          #+#    #+#             */
/*   Updated: 2024/09/12 15:04:08 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

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

void ft_mutex_destroy(t_philo **phil)
{
	t_philo *philo;
	int i;

	philo = *phil;
	i = 0;
	while (i < philo->input.number_of_philosophers)
	{
		if (pthread_mutex_destroy(&philo->fork[i]))
		{
			ft_free(philo, 111);
			perror("mutex destroy:");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	if (pthread_mutex_destroy(&philo->simulation_end_mut))
	{
		ft_free(philo, 111);
		perror("mutex destroy:");
		exit(EXIT_FAILURE);
	}
}

void ft_other_mut_def(t_philo **phil)
{
	int i;
	pthread_mutex_t simulation_mut;
	pthread_mutex_t die_mut;
	t_philo *philo;

	philo = *phil;
	if (pthread_mutex_init(&simulation_mut, NULL) || pthread_mutex_init(&die_mut, NULL))
	{
		ft_free(philo, 111);
		perror("mutex init:");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < philo->input.number_of_philosophers)
	{
		philo[i].simulation_end_mut = simulation_mut;
		i++;
	}
}
void ft_mutex_def(t_philo **phil)
{
	ft_forks_def(phil);
	ft_other_mut_def(phil);
}
