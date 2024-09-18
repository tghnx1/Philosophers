/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:06:18 by mkokorev          #+#    #+#             */
/*   Updated: 2024/09/18 13:10:08 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

int	ft_die_check(t_philo *philo, int i)
{
	ft_get_starving_time(philo, i);
	if (philo[i].time_starving > philo[i].input.time_to_die / 1000)
	{
		//printf("time starving: %ld\ntime to die: %ld\n", philo[i].time_starving, philo[i].input.time_to_die / 1000);
		return (1);
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
		printf("%ld %d is thinking\n", ft_timestamp(&philo), philo->number);
		if (!ft_take_forks(philo))
			return (NULL);
		if (!ft_eat(philo))
		{
			//printf("%ld %d time starvinggg: %ld\n", ft_timestamp(&philo), philo->number, philo->time_starving);
			return (NULL);
		}
		//printf("%ld %d time starvinggg: %ld\n", ft_timestamp(&philo), philo->number, philo->time_starving);
		if (!ft_put_forks(philo))
			return (NULL);
		if (!ft_sleep(philo))
			return (NULL);
		//printf("%ld %d time starvinggg: %ld\n", ft_timestamp(&philo), philo->number, philo->time_starving);
	}
	return (NULL);
}

int	ft_eat(t_philo *philo)
{
	if (philo->simutation_is_over)
	{
		pthread_mutex_unlock(&philo->fork[philo->number - 1]);
		printf("%ld %d has put a fork %d cause of death\n", ft_timestamp(&philo), philo->number, philo->number - 1);
		pthread_mutex_unlock(&philo->fork[(philo->number) % philo->input.number_of_philosophers]);
		printf("%ld %d has put a fork %d cause of death\n", ft_timestamp(&philo), philo->number, (philo->number) % philo->input.number_of_philosophers);
		return (0);
	}
	philo->eating_sleeping = 1;
	philo->time_starving = 0;
	printf("%ld %d is eating\n", ft_timestamp(&philo), philo->number);
	usleep(philo->input.time_to_eat);
	philo->time_starving = 0;
	return (1);
}

int	ft_sleep(t_philo *philo)
{
	if (philo->simutation_is_over)
		return (0);
	philo->time_starving = 0;
	philo->woke_up_time = ft_time();
	philo->eating_sleeping = 1;
	printf("%ld %d is sleeping\n", ft_timestamp(&philo), philo->number);
	usleep(philo->input.time_to_sleep);
	philo->eating_sleeping = 0;
	philo->woke_up_time = ft_time();
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
