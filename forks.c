/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:08:26 by mkokorev          #+#    #+#             */
/*   Updated: 2024/09/12 13:08:26 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

void ft_take_forks(t_philo *philo)
{
	// if philo is even => take right then left
	if (philo->number % 2 == 0)
	{
		// take right:
		// TODO: ft_mutex_lock(philo->fork[philo->number - 1])
		pthread_mutex_lock(&philo->fork[philo->number - 1]);
		printf("%ld %d has taken a fork %d\n", ft_timestamp(), philo->number, philo->number - 1);
		// take left:
		pthread_mutex_lock(&philo->fork[(philo->number) % philo->input.number_of_philosophers]);
		printf("%ld %d has taken a fork %d\n", ft_timestamp(), philo->number, (philo->number) % philo->input.number_of_philosophers);
	}
	else
	// if philo is odd => take left then right fork
	{
		// take left:
		pthread_mutex_lock(&philo->fork[(philo->number) % philo->input.number_of_philosophers]);
		printf("%ld %d has taken a fork %d\n", ft_timestamp(), philo->number, (philo->number) % philo->input.number_of_philosophers);
		// take right:
		pthread_mutex_lock(&philo->fork[philo->number - 1]);
		printf("%ld %d has taken a fork %d\n", ft_timestamp(), philo->number, philo->number - 1);
	}
	return;
}

void ft_put_forks(t_philo *philo)
{
	// put left:
	pthread_mutex_unlock(&philo->fork[(philo->number) % philo->input.number_of_philosophers]);
	printf("%ld %d has put a fork %d\n", ft_timestamp(), philo->number, (philo->number) % philo->input.number_of_philosophers);
	// put right:
	pthread_mutex_unlock(&philo->fork[philo->number - 1]);
	printf("%ld %d has put a fork %d\n", ft_timestamp(), philo->number, philo->number - 1);
	return;
}
