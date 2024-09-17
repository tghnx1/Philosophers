/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:56:22 by mkokorev          #+#    #+#             */
/*   Updated: 2024/09/17 18:47:26 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

void *ft_monitor(void *temp)
{
	t_philo *philo;
	int i;

	i = 0;
	philo = (t_philo *)temp;
	while (!philo->simutation_is_over)
	{
		while (i < philo->input.number_of_philosophers)
		{
			if (ft_die_check(philo, i))
			{
				printf("%ld %d died\ntime starving = %ld\n", ft_timestamp(&philo), philo[i].number, philo->time_starving);
				pthread_mutex_lock(&philo->simulation_end_mut);
				ft_sim_is_over(philo, philo[i].number);
				pthread_mutex_unlock(&philo->simulation_end_mut);
				return (NULL);
			}
			else
				i++;
		}
		i = 0;
	}
	return (NULL);
}

void ft_threads_def(t_philo **phil)
{
	int i;
	pthread_t *philos;
	pthread_t monitor;
	t_philo *philo;

	philo = *phil;
	i = 0;
	philos = (pthread_t *)malloc((philo->input.number_of_philosophers) * sizeof(pthread_t));
	if (!philos)
	{
		ft_free(philo, 011);
		perror("threads memory allocation failed:");
		exit(EXIT_FAILURE);
	}
	philo->philos = philos;
	while (i < philo->input.number_of_philosophers)
	{
		if (pthread_create(&philo->philos[i], NULL,
						   ft_dinner, (void *)&philo[i]) != 0)
		{
			perror("pthread_create error:");
			ft_free(philo, 111);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	// monitoring thread:
	if (pthread_create(&monitor, NULL,
					   ft_monitor, (void *)philo) != 0)
	{
		ft_free(philo, 111);
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}
	ft_threads_join(philo, monitor);
	return;
}
