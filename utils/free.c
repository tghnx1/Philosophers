/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:46:53 by mkokorev          #+#    #+#             */
/*   Updated: 2024/09/12 14:46:53 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

void ft_free(t_philo *philo, int code)
{
	if (code == 111)
	{
		free(philo->philos);
		free(philo->fork);
		free(philo);
	}
	else if (code == 011)
	{
		free(philo->fork);
		free(philo);
	}
	else if (code == 101)
	{
		free(philo->philos);
		free(philo);
	}
}
