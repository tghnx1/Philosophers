/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:31:40 by mkokorev          #+#    #+#             */
/*   Updated: 2024/07/15 20:28:35 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

int	main(int argc, char **argv)
{
	t_input	input;
	t_philo	**philos;
	t_philo	*head;

	if (!ft_parce(argc, argv, &input))
		return (0);
	philos = ft_link_philo_def(input);
	head = philos[0];
	//print_list(head, input);
	ft_threads_def(input, philos);
	free(philos);
	free_philos(head, input.number_of_philosophers);  //at the end
	return (0);
}
