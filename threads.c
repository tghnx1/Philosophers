/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:56:22 by mkokorev          #+#    #+#             */
/*   Updated: 2024/07/15 21:23:41 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

void	ft_if_die(t_philo *philo, struct timeval start)
{
	struct timeval		end;
	long				time_passed;

	if (gettimeofday(&end, NULL) == -1)
	{
		perror("gettimeofday");
		exit(EXIT_FAILURE);
	}
	time_passed = 1000000 * (end.tv_sec - start.tv_sec);
	printf("time passed: %ld\n", time_passed);
	printf("philo->input.time_to_die: %d\n", philo->input.time_to_die);
	if (time_passed >= philo->input.time_to_die)
	{
		printf("philo %d died\n", philo->index);
		exit(0);
	}
}

void	ft_eat(t_philo *philo)
{
	write(1, "eating\n", 7);
	printf("philo index: %d\n", philo->index);
	printf("philo left hand: %d\n", philo->left_hand);
	printf("philo right hand: %d\n", philo->right_hand);
	return ;
}

void	*ft_think(void *temp)
{
	t_philo			**philos;
	t_philo			*philo;
	struct timeval	start;
	long			time_passed;

	philos = (t_philo **)temp;
	philo = philos[0];
	if (gettimeofday(&start, NULL) == -1)
	{
		perror("gettimeofday");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		usleep(2000000);
		ft_if_die(philo, start);
		if (!philo->left->right_hand && !philo->right->left_hand)
		{
			philo->left_hand = 1;
			philo->right_hand = 1;
			ft_eat(philo);
			break ;
		}
	}
	return	(NULL);
}

void	ft_threads_def(t_input input, t_philo **philos)
{
	int				i;
	pthread_t		*thread;

	i = 0;
	thread = (pthread_t *)malloc(input.number_of_philosophers
			* sizeof(pthread_t));
	if (!thread)
	{
		perror("memmory allocation failed: ");
		exit(EXIT_FAILURE);
	}
	while (i < input.number_of_philosophers)
	{
		if (pthread_create(&thread[i], NULL,
				ft_think, (void *)&philos[i]) != 0)
		{
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}
		i++;
	}
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
	return ;
}
