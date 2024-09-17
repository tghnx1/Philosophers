/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:31:40 by mkokorev          #+#    #+#             */
/*   Updated: 2024/09/16 14:37:31 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

int main(int argc, char **argv)
{
	t_philo *philo;
	t_input input;

	if (!ft_parce(argc, argv, &input))
		return (0);
	philo = ft_philos_def(input);
	if (!philo)
		return (0);
	ft_mutex_def(&philo);
	if (!philo->fork)
		return (0);
	ft_threads_def(&philo);
	printf("WE ARE OUTSIDE!!\n");
	ft_mutex_destroy(&philo);
	ft_free(philo, 111);
	return (0);
}
