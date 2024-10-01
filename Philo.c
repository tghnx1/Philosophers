/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:31:40 by mkokorev          #+#    #+#             */
/*   Updated: 2024/10/01 17:02:23 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_input	input;

	if (!ft_parce(argc, argv, &input))
		return (0);
	philo = ft_philos_def(input);
	if (!philo)
		return (0);
	if (!ft_mutex_def(&philo))
		return (0);
	for (int i = 0; i < 4; i++)
	{
		printf("Philo %i, print mutex %p\n", i, &philo[i].print_mut);
		printf("Philo %i, sim end mutex %p\n", i, &philo[i].simulation_end_mut);
		printf("Philo %i, time mutex %p\n", i, &philo[i].time);
		// for (int j = 0; j < 4; j++)
	// {
		// printf("Philo %i, fork %i, mutex %p\n", i, j, &philo[i].fork[j]);
	// }
	}
	exit(0);
	if (!philo->fork)
		return (0);
	ft_threads_def(&philo);
	//printf("WE ARE OUTSIDE!!\n");
	if (!ft_mutex_destroy(&philo))
		return (0);
	ft_free(philo, 111);
	return (0);
}
