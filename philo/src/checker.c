/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalado- <jsalado-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:30:31 by jsalado-          #+#    #+#             */
/*   Updated: 2025/02/12 14:30:44 by jsalado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_necessary_meals(t_philo *philosophers)
{
	int	i;
	int	philosophers_finished_eating;

	i = 0;
	philosophers_finished_eating = 0;
	if (philosophers->data->necessary_meals == -1)
		return (EXIT_SUCCESS);
	while (i < philosophers->data->total_philosophers)
	{
		pthread_mutex_lock(&philosophers->data->meal_lock);
		if (philosophers[i].meals_eaten >= philosophers->data->necessary_meals)
			philosophers_finished_eating++;
		pthread_mutex_unlock(&philosophers->data->meal_lock);
		i++;
	}
	if (philosophers_finished_eating == philosophers->data->total_philosophers)
	{
		pthread_mutex_lock(&philosophers->data->dead_lock);
		philosophers->data->is_dead = 1;
		pthread_mutex_unlock(&philosophers->data->dead_lock);
		return (1);
	}
	return (0);
}
