/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:54:04 by mkokorev          #+#    #+#             */
/*   Updated: 2024/07/09 15:57:49 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Philo.h"

void	*free_philos(t_philo *head, int num)
{
	int		i;
	t_philo	*current;
	t_philo	*temp;

	if (!head)
		return (NULL);
	i = 0;
	current = head;
	while (i < num)
	{
		temp = current;
		current = current->right;
		free(temp);
		temp = NULL;
		i++;
	}
	return (NULL);
}

