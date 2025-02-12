/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalado- <jsalado-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:42:37 by jsalado-          #+#    #+#             */
/*   Updated: 2025/02/12 14:31:14 by jsalado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	routines(t_philo *philosophers)
{
	pthread_mutex_lock(philosophers->r_fork);
	print_philosopher(HAS_TAKEN_FORK, philosophers);
	if (philosophers->data->total_philosophers == 1)
	{
		ft_usleep(philosophers->time_to_die);
		pthread_mutex_unlock(philosophers->r_fork);
		return ;
	}
	pthread_mutex_lock(philosophers->l_fork);
	print_philosopher(HAS_TAKEN_FORK, philosophers);
	print_philosopher(IS_EATING, philosophers);
	pthread_mutex_lock(&philosophers->data->meal_lock);
	philosophers->last_meal = get_current_time();
	philosophers->meals_eaten++;
	pthread_mutex_unlock(&philosophers->data->meal_lock);
	ft_usleep(philosophers->time_to_eat);
	pthread_mutex_unlock(philosophers->r_fork);
	pthread_mutex_unlock(philosophers->l_fork);
	print_philosopher(IS_SLEEPING, philosophers);
	ft_usleep(philosophers->time_to_sleep);
	print_philosopher(IS_THINKING, philosophers);
}

void	*p_routine(void *philosophers)
{
	t_philo	*current_philosophers;

	current_philosophers = philosophers;
	if (current_philosophers->id % 2 == 0)
		ft_usleep(1);
	while (!dead_loop(philosophers))
		routines(philosophers);
	return (philosophers);
}