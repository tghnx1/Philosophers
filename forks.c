/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:08:26 by mkokorev          #+#    #+#             */
/*   Updated: 2024/10/01 13:50:17 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

int	ft_check_simul(t_philo *philo)
{
	if (!ft_mutex(&philo->simulation_end_mut, "LOCK", philo))
		return (0);
	if (philo->simutation_is_over)
	{
		ft_mutex(&philo->simulation_end_mut, "UNLOCK", philo);
		return (0);
	}
	if (!ft_mutex(&philo->simulation_end_mut, "UNLOCK", philo))
		return (0);
	return (1);
}

int	ft_take_forks(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = (philo->number) % philo->input.number_of_philosophers;
	right_fork = philo->number - 1;
	if (!ft_check_simul(philo))
		return (0);
	//  if philo is even => take right then left
	if (philo->number % 2 == 0)
	{
		// take right:
		if (!ft_mutex(&philo->fork[right_fork], "LOCK", philo))
			return (0);
		// ptint it:
		if (!philo->simutation_is_over)
		{
			if (!ft_mut_printf(philo, "has taken a fork"))
				return (0);
		}
		// if simulation is over he puts the fork back:
		else
		{
			ft_mutex(&philo->fork[right_fork], "UNLOCK", philo);
			return (0);
			//printf("%ld %d has put a fork %d cause of death\n", ft_timestamp(&philo), philo->number, philo->number - 1);
		}
		usleep(500);
		// take left:
		if (!ft_mutex(&philo->fork[left_fork], "LOCK", philo))
			return (0);
		//print it:
		if (!philo->simutation_is_over)
		{
			if (!ft_mut_printf(philo, "has taken a fork"))
				return (0);
		}
		// if simulation is over he puts the fork back:
		else
		{
			ft_mutex(&philo->fork[left_fork], "UNLOCK", philo);
			ft_mutex(&philo->fork[right_fork], "UNLOCK", philo);
			return (0);
			//printf("%ld %d has put a fork %d cause of death\n", ft_timestamp(&philo), philo->number, left_fork);
		}
	}
	else
	// if philo is odd => take left then right fork
	{
					// take left:
		if (!ft_mutex(&philo->fork[left_fork], "LOCK", philo))
				return (0);
					// print the action:
		if (!philo->simutation_is_over)
		{
			if (!ft_mut_printf(philo, "has taken a fork"))
				return (0);
		}
					// if simulation is over he puts the fork back:
		else
		{
			ft_mutex(&philo->fork[left_fork], "UNLOCK", philo);
			//printf("%ld %d has put a fork %d cause of death\n", ft_timestamp(&philo), philo->number, left_fork);
			return (0);
		}
		usleep(500);
					// take right:
		if (!ft_mutex(&philo->fork[right_fork], "LOCK", philo))
			return (0);
					// print the action:
		if (!philo->simutation_is_over)
		{
			if (!ft_mut_printf(philo, "has taken a fork"))
				return (0);
		}
		// if simulation is over he puts the fork back:
		else
		{
			ft_mutex(&philo->fork[right_fork], "UNLOCK", philo);
			ft_mutex(&philo->fork[left_fork], "UNLOCK", philo);
			//printf("%ld %d has put a fork %d cause of death\n", ft_timestamp(&philo), philo->number, right_fork);
			return (0);
		}
	}
	return (1);
}

int	ft_put_forks(t_philo *philo)
{
	// put left:
	if (!ft_mutex(&philo->fork[(philo->number) % philo->input.number_of_philosophers], "UNLOCK", philo))
		return (228);
		printf("%ld %d has put a fork %d\n", ft_timestamp(&philo), philo->number, (philo->number) % philo->input.number_of_philosophers);
	// put right:
	if (!ft_mutex(&philo->fork[philo->number - 1], "UNLOCK", philo))
		return (228);
	printf("%ld %d has put a fork %d\n", ft_timestamp(&philo), philo->number, philo->number - 1);
	if (philo->simutation_is_over)
		return (0);
	return (1);
}
