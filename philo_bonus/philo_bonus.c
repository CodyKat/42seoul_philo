/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 23:37:50 by jaemjeon          #+#    #+#             */
/*   Updated: 2022/08/04 22:51:08 by jaemjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_odd_loop(t_philo *info_philo)
{
	void	(*philo_eat)(t_philo *);

	if (info_philo->info_union->has_optional_arg == TRUE)
		philo_eat = philo_eat_with_option;
	else
		philo_eat = philo_eat_with_no_option;
	usleep(1000);
	while (1)
	{
		pick_up_forks(info_philo);
		philo_eat(info_philo);
		philo_sleep(info_philo);
		philo_think(info_philo);
		usleep(300);
	}
}

void	philo_even_loop(t_philo *info_philo)
{
	void	(*philo_eat)(t_philo *);

	if (info_philo->info_union->has_optional_arg == TRUE)
		philo_eat = philo_eat_with_option;
	else
		philo_eat = philo_eat_with_no_option;
	while (1)
	{
		pick_up_forks(info_philo);
		philo_eat(info_philo);
		philo_sleep(info_philo);
		philo_think(info_philo);
	}
}

void	*philo_check_dead_loop(void *info_parameter)
{
	t_philo	*info_philo;
	int		sem_index;
	sem_t	*sem_time_last_meal;

	info_philo = (t_philo *)info_parameter;
	sem_index = info_philo->my_id - 1;
	sem_time_last_meal = \
		info_philo->info_union->sem_each_philo_time_last_meal[sem_index];
	while (1)
	{
		sem_wait(sem_time_last_meal);
		if (info_philo->info_union->time_to_die <= \
				get_cur_time() - info_philo->time_of_last_meal)
		{
			sem_wait(info_philo->info_union->voice);
			printf("%zu %zu died\n", \
					get_time_stamp(info_philo->info_union), info_philo->my_id);
			sem_post(info_philo->info_union->dead_flag);
			sem_post(sem_time_last_meal);
		}
		sem_post(sem_time_last_meal);
		usleep(1000);
	}
}

void	philo_process(t_philo *info_philo)
{
	pthread_t	philo_thread;
	void		(*my_loop)(t_philo *);

	if (info_philo->my_id % 2 == 0)
		my_loop = philo_even_loop;
	else
		my_loop = philo_odd_loop;
	sem_wait(info_philo->info_union->start_key);
	sem_post(info_philo->info_union->start_key);
	pthread_create(&philo_thread, NULL, philo_check_dead_loop, info_philo);
	pthread_detach(philo_thread);
	my_loop(info_philo);
}