/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkokorev <mkokorev@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:12:40 by drabadan          #+#    #+#             */
/*   Updated: 2024/10/05 18:57:08 by mkokorev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// cc *.c ./utils/*.c -pthread

// docker run -it -v ${pwd}:/home/root ubuntu

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_input
{
	int		number_of_philosophers;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		number_of_times_each_philosopher_must_eat;
}	t_input;

typedef struct s_philo
{
	int				number;
	long			time_starving;
	long			time_eating;
	long			time_sleeping;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*simulation_end_mut;
	pthread_mutex_t	*print_mut;
	pthread_mutex_t	*time;
	pthread_mutex_t	*eat;
	pthread_t		*philos;
	int				simutation_is_over;
	t_input			input;
	long			timestart;
	long			start_meal_time;
	int				dead;
	int				eating_sleeping;
	int				ate_num;
	int				full;

}	t_philo;

typedef struct s_fork
{
	int		number;
	long	time_starving;
	long	time_eating;
	long	time_sleeping;
	t_input	input;
}	t_fork;

int		ft_atoi(const char *nptr);
int		ft_parce(int argc, char **argv, t_input *input);
t_philo	*ft_philos_def(t_input input);
void	ft_threads_def(t_philo **phil);
long	ft_time(void);
void	ft_threads_join(t_philo *philo, pthread_t monitor);
void	ft_threads_detach(t_philo *philo);
int		ft_forks_def(t_philo **phil);
void	*ft_dinner(void *temp);
int		ft_eat(t_philo *philo);
int		ft_sleep(t_philo *philo);
int		ft_take_forks(t_philo *philo);
int		ft_put_forks(t_philo *philo);
void	ft_free(t_philo *philo, int code);
int		ft_forks_def(t_philo **phil);
int		ft_mutex_destroy(t_philo **philo);
long	ft_time_start(t_philo *philo);
long	ft_timestamp(t_philo **phil);
int		ft_mutex_def(t_philo **phil);
int		ft_die_check(t_philo *philo, int i);
int		ft_get_starving_time(t_philo *philo, int i);
int		ft_sim_is_over(t_philo *philo, int philo_num);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_mutex(pthread_mutex_t *mutex, char *code, t_philo *philo);
int		ft_mut_printf(t_philo *philo, char *print);
int		ft_check_simul(t_philo *philo);
int		ft_take_forks_sort(t_philo *philo, int second_fork, int first_fork);
int		ft_ate_increment(t_philo *philo);
int		ft_die_check(t_philo *philo, int i);
int		ft_mutex_lock_unlock(pthread_mutex_t *mutex,
			char *code, t_philo *philo);
int		ft_fork_allocate(t_philo *philo, pthread_mutex_t	**forkie);
int		ft_share_mutex(t_philo *philo);
#endif
