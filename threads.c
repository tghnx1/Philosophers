/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:56:22 by mkokorev          #+#    #+#             */
/*   Updated: 2024/08/23 17:07:16 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

int	ft_if_die(t_philo *philo, struct timeval start)
{
	struct timeval		end;
	long				time_passed;

	if (gettimeofday(&end, NULL) == -1)
	{
		perror("gettimeofday");
		exit(EXIT_FAILURE);
	}
	time_passed = 1000000 * (end.tv_sec - start.tv_sec);
	return (1);
}

void	*ft_eat(t_philo *philo)
{
	printf("philo number: %d\n", philo->number);
	//take the left fork, the right, then eat
	//left:
	pthread_mutex_lock(&philo->fork[3]);
	printf("%ld %d is eating\n", ft_timestamp(), philo->number);
	return (NULL);
}

void	*ft_think(void *temp)
{
	t_philo	*philo;
	long	time_to_think;
	long	timestamp;

	philo = (t_philo *)temp;
	timestamp = ft_timestamp();
	printf("%ld %d is thinking\n", timestamp, philo->number);
	time_to_think = philo->input.time_to_eat / 2;
	usleep(time_to_think);
	if (!ft_eat(philo))
		return (NULL);
	return (NULL);
}

void	ft_threads_def(t_philo *philo)
{
	int			i;
	pthread_t	*thread;

	i = 0;
	thread = (pthread_t *)malloc((philo->input.number_of_philosophers)
			* sizeof(pthread_t));
	if (!thread)
	{
		perror("memmory allocation failed: ");
		exit(EXIT_FAILURE);
	}
	while (i < philo->input.number_of_philosophers)
	{
		if (pthread_create(&thread[i], NULL,
				ft_think, (void *)&philo[i]) != 0)
		{
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	ft_threads_join(philo->input, thread);
	return ;
}
