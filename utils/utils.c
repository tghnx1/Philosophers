/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:53:45 by mkokorev          #+#    #+#             */
/*   Updated: 2024/07/09 16:02:56 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

void	print_list(t_philo *head, t_input input)
{
	t_philo	*current;
	int		i;

	i = 0;
	current = head;
	while (i < input.number_of_philosophers)
	{
		printf("ind: %d\n", current->index);
		current = current->right;
		i++;
	}
}

void	nodes_init(t_input input, t_philo	**philos)
{
	int	i;

	i = 0;
	while (i < input.number_of_philosophers)
	{
		philos[i] = (t_philo *)(malloc(sizeof(t_philo)));
		if (!(philos[i]))
			return ;
		else if (i)
		{
			philos[i]->left = philos[i - 1];
			philos[i - 1]->right = philos[i];
		}
		if (i == input.number_of_philosophers - 1)
			philos[0]->left = philos[i];
		philos[i]->right = philos[0];
		philos[i]->index = i;
		philos[i]->time_starving = 0;
		philos[i]->time_eating = 0;
		philos[i]->time_sleeping = 0;
		philos[i]->time_thinking = 0;
		philos[i]->input = input;
		i++;
	}
}

t_philo	**ft_link_philo_def(t_input input)
{
	t_philo	**philos;
	int		i;

	i = 0;
	philos = (t_philo **)malloc(input.number_of_philosophers
			* sizeof(t_philo *));
	if (!(philos))
		return (NULL);
	nodes_init(input, philos);
	return (philos);

}
