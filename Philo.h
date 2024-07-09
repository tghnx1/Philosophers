/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:12:40 by drabadan          #+#    #+#             */
/*   Updated: 2024/07/09 16:01:12 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_input
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
}		t_input;

typedef struct s_philo
{
	int				index;
	int				time_starving;
	int				time_eating;
	int				time_sleeping;
	int				time_thinking;
	int				left_hand;
	int				right_hand;
	t_input			input;
	struct s_philo	*left;
	struct s_philo	*right;

}		t_philo;

int		ft_atoi(const char *nptr);
int		ft_parce(int argc, char **argv, t_input *input);
t_philo	**ft_link_philo_def(t_input input);
void	print_list(t_philo *head, t_input input);
void	ft_threads_def(t_input input, t_philo **philos);
void	*free_philos(t_philo *head, int num);

#endif
