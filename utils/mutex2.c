/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 17:38:00 by mkokorev          #+#    #+#             */
/*   Updated: 2024/10/05 17:38:00 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

int	ft_mutex_lock_unlock(pthread_mutex_t *mutex, char *code, t_philo *philo)
{
	if (!ft_strcmp("UNLOCK", code))
	{
		if (pthread_mutex_unlock(mutex))
		{
			ft_free(philo, 111);
			return (0);
		}
	}
	else if (!ft_strcmp("LOCK", code))
	{
		if (pthread_mutex_lock(mutex))
		{
			ft_free(philo, 111);
			return (0);
		}
	}
	return (1);
}

int	ft_fork_allocate(t_philo *philo, pthread_mutex_t	**forkie)
{
	pthread_mutex_t	*fork;

	fork = (pthread_mutex_t *)malloc
		(philo->input.number_of_philosophers * sizeof(pthread_mutex_t));
	if (!fork)
	{
		ft_free(philo, 101);
		printf("fork allocate error\n");
		return (0);
	}
	*forkie = fork;
	return (1);
}

int	ft_share_mutex(t_philo *philo)
{
	int	i;

	i = 1;
	while (i < philo->input.number_of_philosophers)
	{
		philo[i].simulation_end_mut = philo->simulation_end_mut;
		philo[i].print_mut = philo->print_mut;
		philo[i].time = philo->time;
		philo[i].eat = philo->eat;
		i++;
	}
	return (1);
}
