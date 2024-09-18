/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:08:26 by mkokorev          #+#    #+#             */
/*   Updated: 2024/09/18 13:11:26 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

int ft_take_forks(t_philo *philo)
{
	if (philo->simutation_is_over)
		return (0);
	//  if philo is even => take right then left
	if (philo->number % 2 == 0)
	{
		// take right:
		pthread_mutex_lock(&philo->fork[philo->number - 1]);
		// ptint it:
		if (!philo->simutation_is_over)
			printf("%ld %d has taken a fork %d\n", ft_timestamp(&philo), philo->number, philo->number - 1);
		// if simulation is over he puts the fork back:
		else
		{
			pthread_mutex_unlock(&philo->fork[philo->number - 1]);
			//printf("%ld %d has put a fork %d cause of death\n", ft_timestamp(&philo), philo->number, philo->number - 1);
			return (0);
		}
		// take left:
		pthread_mutex_lock(&philo->fork[(philo->number) % philo->input.number_of_philosophers]);
		//print it:
		if (!philo->simutation_is_over)
			printf("%ld %d has taken a fork %d\n", ft_timestamp(&philo), philo->number, (philo->number) % philo->input.number_of_philosophers);
		// if simulation is over he puts the fork back:
		else
		{
			pthread_mutex_unlock(&philo->fork[(philo->number) % philo->input.number_of_philosophers]);
			pthread_mutex_unlock(&philo->fork[philo->number - 1]);
			//printf("%ld %d has put a fork %d cause of death\n", ft_timestamp(&philo), philo->number, (philo->number) % philo->input.number_of_philosophers);
			return (0);
		}
	}
	else
	// if philo is odd => take left then right fork
	{
					// take left:
		pthread_mutex_lock(&philo->fork[(philo->number) % philo->input.number_of_philosophers]);
					// print the action:
		if (!philo->simutation_is_over)
			printf("%ld %d has taken a fork %d\n", ft_timestamp(&philo), philo->number, (philo->number) % philo->input.number_of_philosophers);
					// if simulation is over he puts the fork back:
		else
		{
			pthread_mutex_unlock(&philo->fork[(philo->number) % philo->input.number_of_philosophers]);
			//printf("%ld %d has put a fork %d cause of death\n", ft_timestamp(&philo), philo->number, (philo->number) % philo->input.number_of_philosophers);
			return (0);
		}
					// take right:
		pthread_mutex_lock(&philo->fork[philo->number - 1]);
					// print the action:
		if (!philo->simutation_is_over)
			printf("%ld %d has taken a fork %d\n", ft_timestamp(&philo), philo->number, philo->number - 1);
		// if simulation is over he puts the fork back:
		else
		{
			pthread_mutex_unlock(&philo->fork[philo->number - 1]);
			pthread_mutex_unlock(&philo->fork[(philo->number) % philo->input.number_of_philosophers]);
			//printf("%ld %d has put a fork %d cause of death\n", ft_timestamp(&philo), philo->number, philo->number - 1);
			return (0);
		}
	}
	return (1);
}

int ft_put_forks(t_philo *philo)
{
	// put left:
	if (pthread_mutex_unlock(&philo->fork[(philo->number) % philo->input.number_of_philosophers]))
	{
		ft_free(philo, 111);
		perror("mutex unlock:");
		exit(EXIT_FAILURE);
	}
		//printf("%ld %d has put a fork %d\n", ft_timestamp(&philo), philo->number, (philo->number) % philo->input.number_of_philosophers);
	// put right:
	if (pthread_mutex_unlock(&philo->fork[philo->number - 1]))
	{
		ft_free(philo, 111);
		perror("mutex unlock:");
		exit(EXIT_FAILURE);
	}
	//printf("%ld %d has put a fork %d\n", ft_timestamp(&philo), philo->number, philo->number - 1);
	if (philo->simutation_is_over)
		return (0);
	return (1);
}
