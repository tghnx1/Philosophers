/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:31:40 by mkokorev          #+#    #+#             */
/*   Updated: 2024/10/04 16:00:43 by mkokorev         ###   ########.fr       */
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
	if (!philo->fork)
		return (0);
	ft_threads_def(&philo);
	ft_mutex_destroy(&philo);
	ft_free(philo, 111);
	return (0);
}
