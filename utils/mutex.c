/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:04:08 by mkokorev          #+#    #+#             */
/*   Updated: 2024/10/05 18:56:36 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

int	ft_mutex(pthread_mutex_t *mutex, char *code, t_philo *philo)
{
	if (!ft_mutex_lock_unlock(mutex, code, philo))
		return (0);
	if (!ft_strcmp("DESTROY", code))
	{
		if (pthread_mutex_destroy(mutex) != 0)
		{
			ft_free(philo, 111);
			return (0);
		}
		return (1);
	}
	if (!ft_strcmp("INIT", code))
	{
		if (pthread_mutex_init(mutex, NULL) != 0)
		{
			ft_free(philo, 111);
			return (0);
		}
		return (1);
	}
	return (1);
}

int	ft_forks_def(t_philo **phil)
{
	int				i;
	pthread_mutex_t	*fork;
	t_philo			*philo;

	philo = *phil;
	i = 0;
	if (!ft_fork_allocate(philo, &fork))
		return (0);
	while (i < philo->input.number_of_philosophers)
	{
		if (!ft_mutex(&fork[i], "INIT", philo))
			return (0);
		i++;
	}
	i = 0;
	while (i < philo->input.number_of_philosophers)
	{
		philo[i].fork = fork;
		i++;
	}
	return (1);
}

int	ft_mutex_destroy(t_philo **phil)
{
	t_philo	*philo;
	int		i;

	philo = *phil;
	i = 0;
	while (i < philo->input.number_of_philosophers)
	{
		if (!ft_mutex(&philo->fork[i], "DESTROY", philo))
			return (0);
		i++;
	}
	if (!ft_mutex(philo->simulation_end_mut, "DESTROY", philo)
		|| !ft_mutex(philo->print_mut, "DESTROY", philo)
		|| !ft_mutex(philo->time, "DESTROY", philo)
		|| !ft_mutex(philo->eat, "DESTROY", philo))
		return (0);
	return (1);
}

int	ft_other_mut_def(t_philo **phil)
{
	t_philo			*philo;

	philo = *phil;
	philo->simulation_end_mut = malloc(sizeof(pthread_mutex_t));
	philo->print_mut = malloc(sizeof(pthread_mutex_t));
	philo->time = malloc(sizeof(pthread_mutex_t));
	philo->eat = malloc(sizeof(pthread_mutex_t));
	if (!philo->simulation_end_mut || !philo->print_mut
		|| !philo->time || !philo->eat)
		return (0);
	if (!ft_mutex(philo->simulation_end_mut, "INIT", philo)
		|| !ft_mutex(philo->print_mut, "INIT", philo)
		|| !ft_mutex(philo->time, "INIT", philo)
		|| !ft_mutex(philo->eat, "INIT", philo))
		return (0);
	if (!ft_share_mutex(philo))
		return (0);
	return (1);
}

int	ft_mutex_def(t_philo **phil)
{
	if (!ft_forks_def(phil) || !ft_other_mut_def(phil))
		return (0);
	return (1);
}
