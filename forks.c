/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:08:26 by mkokorev          #+#    #+#             */
/*   Updated: 2024/10/05 16:35:25 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

int	ft_check_simul(t_philo *philo)
{
	if (!ft_mutex(philo->simulation_end_mut, "LOCK", philo))
		return (0);
	if (philo->simutation_is_over)
	{
		ft_mutex(philo->simulation_end_mut, "UNLOCK", philo);
		return (0);
	}
	if (!ft_mutex(philo->simulation_end_mut, "UNLOCK", philo))
		return (0);
	return (1);
}

int	ft_take_first_fork(t_philo *philo, int first_fork)
{
	if (!ft_mutex(&philo->fork[first_fork], "LOCK", philo))
		return (0);
	if (ft_check_simul(philo))
	{
		if (!ft_mut_printf(philo, "has taken a fork"))
			return (0);
	}
	else
	{
		ft_mutex(&philo->fork[first_fork], "UNLOCK", philo);
		return (0);
	}
	return (1);
}

int	ft_take_forks_sort(t_philo *philo, int second_fork, int first_fork)
{
	if (!ft_take_first_fork(philo, first_fork))
		return (0);
	usleep(500);
	if (!ft_mutex(&philo->fork[second_fork], "LOCK", philo))
		return (0);
	if (ft_check_simul(philo))
	{
		if (!ft_mut_printf(philo, "has taken a fork"))
			return (0);
	}
	else
	{
		ft_mutex(&philo->fork[first_fork], "UNLOCK", philo);
		ft_mutex(&philo->fork[second_fork], "UNLOCK", philo);
		return (0);
	}
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
	if (philo->number % 2 == 0)
	{
		if (!ft_take_forks_sort(philo, left_fork, right_fork))
			return (0);
	}
	else
	{
		if (!ft_take_forks_sort(philo, right_fork, left_fork))
			return (0);
	}
	return (1);
}

int	ft_put_forks(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = (philo->number) % philo->input.number_of_philosophers;
	right_fork = philo->number - 1;
	if (!ft_mutex(&philo->fork[left_fork], "UNLOCK", philo))
		return (0);
	if (!ft_mutex(&philo->fork[right_fork], "UNLOCK", philo))
		return (0);
	if (!ft_check_simul(philo))
		return (0);
	return (1);
}
