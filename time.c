/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:47:39 by mkokorev          #+#    #+#             */
/*   Updated: 2024/09/11 13:45:19 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

long ft_timestamp(void)
{
	struct timeval time_stamp;

	if (gettimeofday(&time_stamp, NULL) == -1)
	{
		perror("gettimeofday");
		exit(EXIT_FAILURE);
	}
	return (time_stamp.tv_sec * 1000 + (time_stamp.tv_usec / 1000));
}
