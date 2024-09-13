/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:06:18 by mkokorev          #+#    #+#             */
/*   Updated: 2024/09/12 13:06:18 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

int ft_die_check(t_philo *philo)
{
	int i;

	i = 0;
	ft_get_starving_time(philo);
	while (i < philo->input.number_of_philosophers)
	{
		printf("time starving: %ld\n", philo[i].time_starving);
		if (philo[i].time_starving > philo[i].input.time_to_die)
			return (1);
		i++;
	}
	return (0);
}

void *ft_dinner(void *temp)
{
	t_philo *philo;

	philo = (t_philo *)temp;
	philo->timestart = ft_time_start(philo);
	while (!philo->simutation_is_over)
	{
		printf("sim is over: %d\n", philo->simutation_is_over);
		printf("%ld %d is thinking\n", ft_timestamp(&philo), philo->number);
		ft_take_forks(philo);
		ft_eat(philo);
		ft_put_forks(philo);
		ft_sleep(philo);
	}
	return (NULL);
}

void *ft_sleep(t_philo *philo)
{
	printf("%ld %d is sleeping\n", ft_timestamp(&philo), philo->number);
	usleep(philo->input.time_to_sleep);
}

void *ft_eat(t_philo *philo)
{
	printf("%ld %d is eating\n", ft_timestamp(&philo), philo->number);
	usleep(philo->input.time_to_eat);
	philo->finished_meal_time = ft_time();
}
