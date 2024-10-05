/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:06:18 by mkokorev          #+#    #+#             */
/*   Updated: 2024/10/05 17:01:28 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

int	ft_loop_dinner(t_philo *philo)
{
	while (1)
	{
		if (!ft_check_simul(philo))
			return (0);
		if (!ft_take_forks(philo))
			return (0);
		if (!ft_eat(philo))
			return (0);
		if (!ft_put_forks(philo))
			return (0);
		if (!ft_ate_increment(philo))
			return (0);
		if (!ft_sleep(philo))
			return (0);
		usleep(500);
		if (ft_check_simul(philo))
			if (!ft_mut_printf(philo, "is thinking"))
				return (0);
	}
}

void	*ft_dinner(void *temp)
{
	t_philo	*philo;

	philo = (t_philo *)temp;
	philo->timestart = ft_time_start(philo);
	if (philo->input.number_of_philosophers == 1)
	{
		printf("0 1 died\n");
		return (NULL);
	}
	ft_loop_dinner(philo);
	return (NULL);
}

int	ft_eat(t_philo *philo)
{
	if (!ft_check_simul(philo))
	{
		pthread_mutex_unlock(&philo->fork[philo->number - 1]);
		pthread_mutex_unlock(&philo->fork[(philo->number)
			% philo->input.number_of_philosophers]);
		return (0);
	}
	if (!ft_mutex(philo->time, "LOCK", philo))
		return (0);
	philo->start_meal_time = ft_time();
	if (!ft_mutex(philo->time, "UNLOCK", philo))
		return (0);
	if (!ft_mut_printf(philo, "is eating"))
		return (0);
	usleep(philo->input.time_to_eat);
	return (1);
}

int	ft_sleep(t_philo *philo)
{
	if (!ft_check_simul(philo))
		return (0);
	if (!ft_mut_printf(philo, "is sleeping"))
		return (0);
	usleep(philo->input.time_to_sleep);
	return (1);
}

int	ft_sim_is_over(t_philo *philo, int philo_num)
{
	int	i;

	i = 0;
	if (!ft_mutex(philo->simulation_end_mut, "LOCK", philo))
		return (0);
	while (i < philo->input.number_of_philosophers)
	{
		philo[i].simutation_is_over = philo_num;
		i++;
	}
	if (!ft_mutex(philo->simulation_end_mut, "UNLOCK", philo))
		return (0);
	return (1);
}
