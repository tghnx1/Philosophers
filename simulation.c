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

void *ft_dinner(void *temp)
{
	// take the left fork, the right, then eat
	// left:
	t_philo *philo;
	philo = (t_philo *)temp;
	while (!philo->simutation_is_over)
	{
		printf("sim is over: %d\n", philo->simutation_is_over);
		printf("%ld %d is thinking\n", ft_timestamp(), philo->number);
		ft_take_forks(philo);
		ft_eat(philo);
		ft_put_forks(philo);
		ft_sleep(philo);
	}
	return (NULL);
}

void *ft_sleep(t_philo *philo)
{
	printf("%ld %d is sleeping\n", ft_timestamp(), philo->number);
	usleep(philo->input.time_to_sleep);
}

void *ft_eat(t_philo *philo)
{
	printf("%ld %d is eating\n", ft_timestamp(), philo->number);
	usleep(philo->input.time_to_eat);
}
