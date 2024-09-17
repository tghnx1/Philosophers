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
		// printf("time starving: %ld\n", philo[i].time_starving);
		if (philo[i].time_starving * 1000 > philo[i].input.time_to_die)
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
		// printf("threads: sim is over: %d\n", philo->simutation_is_over);
		// printf("time to eat: %ld\n", philo->input.time_to_eat);
		// printf("last meal took at: %ld\n", philo->finished_meal_time);
		// printf("starvation ttime: %ld\n", philo->time_starving * 1000);
		// printf("time to die: %ld\n", philo->input.time_to_die);
		printf("%ld %d is thinking\n", ft_timestamp(&philo), philo->number);
		if (!ft_take_forks(philo))
			return (NULL);
		if (!ft_eat(philo))
			return (NULL);
		if (!ft_put_forks(philo))
			return (NULL);
		if (!ft_sleep(philo))
			return (NULL);
	}
	return (NULL);
}

int ft_sleep(t_philo *philo)
{
	if (philo->simutation_is_over)
		return (0);
	printf("%ld %d is sleeping\n", ft_timestamp(&philo), philo->number);
	usleep(philo->input.time_to_sleep);
	return (1);
}

int ft_eat(t_philo *philo)
{
	if (philo->simutation_is_over)
	{
		pthread_mutex_unlock(&philo->fork[philo->number - 1]);
		printf("%ld %d has put a fork %d cause of death\n", ft_timestamp(&philo), philo->number, philo->number - 1);
		pthread_mutex_unlock(&philo->fork[(philo->number) % philo->input.number_of_philosophers]);
		printf("%ld %d has put a fork %d cause of death\n", ft_timestamp(&philo), philo->number, (philo->number) % philo->input.number_of_philosophers);
		return (0);
	}
	printf("%ld %d is eating\n", ft_timestamp(&philo), philo->number);
	philo->finished_meal_time = ft_time();
	usleep(philo->input.time_to_eat);
	philo->finished_meal_time = ft_time();
	return (1);
}

void ft_sim_is_over(t_philo *philo, int philo_num)
{
	int i;

	i = 0;
	while (i < philo->input.number_of_philosophers)
	{
		philo[i].simutation_is_over = philo_num;
		i++;
	}
}
