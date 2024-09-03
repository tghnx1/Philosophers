/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:53:45 by mkokorev          #+#    #+#             */
/*   Updated: 2024/08/23 16:08:43 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

t_philo	*ft_philos_def(t_input input)
{
	t_philo	*philo;
	int		i;

	i = 1;
	philo = (t_philo *)malloc(input.number_of_philosophers
			* sizeof(t_philo));
	if (!(philo))
		return (NULL);
	while (i <= input.number_of_philosophers)
	{
		philo[i - 1].number = i;
		i++;
	}
	philo->time_eating = 0;
	philo->time_sleeping = 0;
	philo->time_eating = 0;
	return (philo);

}

void	ft_threads_join(t_input input, pthread_t	*thread)
{
	int	i;

	i = 0;
	while (i < input.number_of_philosophers)
	{
		if (pthread_join(thread[i], NULL) != 0)
		{
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	free(thread);
	thread = NULL;
}

void	ft_threads_detach(t_input input, pthread_t	*thread)
{
	int	i;

	i = 0;
	while (i < input.number_of_philosophers)
	{
		write(1, "detaching\n", 10);
		if (!pthread_detach(thread[i]))
		{
			perror("pthread_detach");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

pthread_mutex_t	*ft_forks_def(t_input input)
{
	int				i;
	pthread_mutex_t	*fork;

	i = 0;
	fork = (pthread_mutex_t *)malloc(input.number_of_philosophers
			* sizeof(pthread_mutex_t));
	while (i < input.number_of_philosophers)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
	return (fork);
}
