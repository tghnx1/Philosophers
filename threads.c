/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:56:22 by mkokorev          #+#    #+#             */
/*   Updated: 2024/09/19 19:48:06 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

static int	ft_philo_full(t_philo	*philo, int i)
{
	if (philo[i].ate_num >= philo->input.number_of_times_each_philosopher_must_eat)
		return (1);
	return (0);
}

int	ft_everyone_full(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->input.number_of_times_each_philosopher_must_eat == -1)
		return(0);
	while (i < philo->input.number_of_philosophers)
	{
		if (ft_philo_full(philo, i))
			i++;
		else
			return (0);
	}
	return (1);
}

void *ft_monitor(void *temp)
{
	t_philo *philo;
	int i;
	int die;
	int everyone_full;

	i = 0;
	die = 0;
	philo = (t_philo *)temp;
	while (!philo->simutation_is_over)
	{
		everyone_full = ft_everyone_full(philo);
		if (philo->input.number_of_philosophers == 1)
			return (NULL);
		while (i < philo->input.number_of_philosophers)
		{
			die = ft_die_check(philo, i);
			if (die || everyone_full)
			{
				if (die)
					printf("%ld %d died\n", ft_timestamp(&philo),
						philo[i].number);
				if (!ft_mutex(&philo->simulation_end_mut, "LOCK", philo))
					return (NULL);
				ft_sim_is_over(philo, philo[i].number);
				if (!ft_mutex(&philo->simulation_end_mut, "UNLOCK", philo))
					return (NULL);
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
