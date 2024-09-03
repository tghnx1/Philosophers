/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:55:21 by mkokorev          #+#    #+#             */
/*   Updated: 2024/08/23 16:36:45 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

int	ft_arg_check(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
	{
		printf("invalid number of arguments\n");
		return (0);
	}
	i = 1;
	j = 0;
	while (i < argc)
	{
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
			{
				printf("invalid argument(s)\n");
				return (0);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

int	ft_parce(int argc, char **argv, t_input *input)
{

	if (!ft_arg_check(argc, argv))
		return (0);
	input->number_of_philosophers = ft_atoi(&argv[1][0]);
	input->time_to_die = ft_atoi(&argv[2][0]);
	input->time_to_eat = ft_atoi(&argv[3][0]);
	input->time_to_sleep = ft_atoi(&argv[4][0]);
	if (argc == 6)
		input->number_of_times_each_philosopher_must_eat = ft_atoi(&argv[5][0]);
	else
		input->number_of_times_each_philosopher_must_eat = -1;
	return (1);
}
