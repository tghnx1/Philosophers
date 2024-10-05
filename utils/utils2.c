/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 17:01:08 by mkokorev          #+#    #+#             */
/*   Updated: 2024/10/05 17:01:08 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

int	ft_die_check(t_philo *philo, int i)
{
	if (!ft_mutex(philo[i].time, "LOCK", philo))
		return (0);
	ft_get_starving_time(philo, i);
	if (!ft_mutex(philo[i].time, "UNLOCK", philo))
		return (0);
	if (philo[i].time_starving > philo[i].input.time_to_die / 1000)
		return (1);
	return (0);
}

int	ft_ate_increment(t_philo *philo)
{
	if (!ft_mutex(philo->eat, "LOCK", philo))
		return (0);
	philo->ate_num++;
	if (philo->ate_num
		>= philo->input.number_of_times_each_philosopher_must_eat)
		philo->full = 1;
	if (!ft_mutex(philo->eat, "UNLOCK", philo))
		return (0);
	return (1);
}
