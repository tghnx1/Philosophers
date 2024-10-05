/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:56:22 by mkokorev          #+#    #+#             */
/*   Updated: 2024/10/05 17:37:19 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

int	ft_everyone_full(t_philo *philo)
{
	int	i;

	if (philo->input.number_of_times_each_philosopher_must_eat == -1)
		return (0);
	i = 0;
	if (!ft_mutex(philo->eat, "LOCK", philo))
		return (0);
	while (i < philo->input.number_of_philosophers)
	{
		if (philo[i].full)
			i++;
		else
		{
			ft_mutex(philo->eat, "UNLOCK", philo);
			return (0);
		}
	}
	if (!ft_mutex(philo->eat, "UNLOCK", philo))
		return (0);
	return (1);
}

int	ft_monitoring_loop(t_philo *philo, int everyone_full, int i, int die)
{
	while (1)
	{
		if (!ft_check_simul(philo))
			break ;
		everyone_full = ft_everyone_full(philo);
		while (i < philo->input.number_of_philosophers)
		{
			die = ft_die_check(philo, i);
			if (die || everyone_full)
			{
				if (die)
				{
					if (!ft_mut_printf(&philo[i], "died"))
						return (0);
				}
				ft_sim_is_over(philo, philo[i].number);
				return (0);
			}
			else
				i++;
		}
		i = 0;
	}
	return (1);
}

void	*ft_monitor(void *temp)
{
	t_philo	*philo;
	int		i;
	int		die;
	int		everyone_full;

	i = 0;
	die = 0;
	everyone_full = 0;
	philo = (t_philo *)temp;
	if (philo->input.number_of_philosophers == 1)
		return (NULL);
	ft_monitoring_loop(philo, everyone_full, i, die);
	return (NULL);
}

int	ft_threads_create(t_philo *philo, pthread_t	*monitor)
{
	int	i;

	i = 0;
	while (i < philo->input.number_of_philosophers)
	{
		if (pthread_create(&philo->philos[i], NULL,
				ft_dinner, (void *)&philo[i]) != 0)
		{
			ft_free(philo, 111);
			printf("threads create failed\n");
			return (0);
		}
		i++;
	}
	if (pthread_create(monitor, NULL,
			ft_monitor, (void *)philo) != 0)
	{
		ft_free(philo, 111);
		printf("monitor thread create failed\n");
		return (0);
	}
	return (1);
}

void	ft_threads_def(t_philo **phil)
{
	pthread_t	*philos;
	pthread_t	monitor;
	t_philo		*philo;

	philo = *phil;
	philos = (pthread_t *)malloc((philo->input.number_of_philosophers)
			* sizeof(pthread_t));
	if (!philos)
	{
		ft_free(philo, 011);
		printf("threads memory allocation failed\n");
		return ;
	}
	philo->philos = philos;
	if (!ft_threads_create(philo, &monitor))
		return ;
	ft_threads_join(philo, monitor);
	return ;
}
