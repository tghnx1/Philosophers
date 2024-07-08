/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:31:40 by mkokorev          #+#    #+#             */
/*   Updated: 2024/07/08 21:33:39 by mkokorev         ###   ########.fr       */
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

void	ft_threads_def(t_input input)
{
	int			i;
	pthread_t	*thread;
	t_philo		*philo;

	i = 0;
	thread = (pthread_t *)malloc(input.number_of_philosophers
			* sizeof(pthread_t));
	while (i < input.number_of_philosophers)
	{
		if (pthread_create(&thread[i], NULL, ft_eating(input, philo),
				(void *)&my_mutex) != 0)
		{
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_input	input;

	if (!ft_parce(argc, argv, &input))
		return (0);
	ft_threads_def(input);
	printf("num: %d\n", input.number_of_philosophers);
	printf("num: %d\n", input.time_to_die);
	printf("num: %d\n", input.time_to_eat);
	printf("num: %d\n", input.time_to_sleep);
	printf("num: %d\n", input.number_of_times_each_philosopher_must_eat);
	return (0);
}
