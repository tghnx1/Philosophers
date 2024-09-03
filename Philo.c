/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:31:40 by mkokorev          #+#    #+#             */
/*   Updated: 2024/08/23 16:44:52 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_input	input;

	if (!ft_parce(argc, argv, &input))
		return (0);
	write(1, "kek\n", 4);
	philo = ft_philos_def(input);
	if (!philo)
		return (0);
	philo->input = input;
	philo->fork = ft_forks_def(philo->input);
	if (!philo->fork)
		return (0);
	//ft_time_start();
	ft_threads_def(philo);
	//ft_threads_detach(input, thread);
	free(philo);
	return (0);
}
