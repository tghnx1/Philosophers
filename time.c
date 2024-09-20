/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:47:39 by mkokorev          #+#    #+#             */
/*   Updated: 2024/09/20 18:39:26 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

long	ft_time(void)
{
	struct timeval	time_stamp;

	if (gettimeofday(&time_stamp, NULL) == -1)
		return (-1);
	return (time_stamp.tv_sec * 1000 + (time_stamp.tv_usec / 1000));
}

long	ft_time_start(t_philo *philo)
{
	// if (!ft_mutex(&philo->time, "LOCK", philo))
	// 	return (0);
	philo->timestart = ft_time();
	// if (!ft_mutex(&philo->time, "UNLOCK", philo))
	// 	return (0);
	return (philo->timestart);
}

long	ft_timestamp(t_philo **phil)
{
	t_philo	*philo;
	long	timeend;
	long	timestamp;

	philo = *phil;
	timeend = 0;
	// if (!ft_mutex(&philo->time, "LOCK", philo))
	// 	return (0);
	timeend = ft_time();
	timestamp = timeend - philo->timestart;
	// if (!ft_mutex(&philo->time, "UNLOCK", philo))
	// 	return (0);
	return (timestamp);
}

int	ft_get_starving_time(t_philo *philo, int i)
{
	long	time;

	time = ft_time();
	if (time == -1)
	{
		ft_free(philo, 111);
		return (-1);
	}
	philo[i].time_starving = time - philo[i].start_meal_time;
	return (1);
}
