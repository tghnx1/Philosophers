/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:47:39 by mkokorev          #+#    #+#             */
/*   Updated: 2024/09/17 18:48:34 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

long ft_time(void)
{
	struct timeval time_stamp;

	if (gettimeofday(&time_stamp, NULL) == -1)
	{
		perror("gettimeofday");
		exit(EXIT_FAILURE);
	}
	return (time_stamp.tv_sec * 1000 + (time_stamp.tv_usec / 1000));
}

long ft_time_start(t_philo *philo)
{
	philo->timestart = ft_time();
	return (ft_time());
}

long ft_timestamp(t_philo **phil)
{
	t_philo *philo;
	long timeend;

	philo = *phil;
	timeend = 0;
	timeend = ft_time();
	return (timeend - philo->timestart);
}

void	ft_get_starving_time(t_philo *philo, int i)
{
	long	time;

	time = ft_time();
	if (philo[i].eating_sleeping)
		philo[i].time_starving = 0;
	else
		philo[i].time_starving = time - philo[i].woke_up_time;
	i++;
}
