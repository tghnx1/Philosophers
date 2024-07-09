/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:56:22 by mkokorev          #+#    #+#             */
/*   Updated: 2024/07/09 16:05:19 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

void	*ft_eating(void *temp)
{
	t_philo	**philos;
	t_philo	*head;

	philos = (t_philo **)temp;
	head = philos[0];
	printf("thr X: %d\n", head->index);
	printf("philo num: %d\n", head->input.number_of_philosophers);
	return	NULL;
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
		if (pthread_create(&thread[i], NULL, ft_eating, (void *)&philos[i]) != 0)
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
}
