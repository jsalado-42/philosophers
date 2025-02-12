/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalado- <jsalado-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:00:46 by jsalado-          #+#    #+#             */
/*   Updated: 2025/02/12 14:30:57 by jsalado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_usleep(size_t ms)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < ms)
		usleep(500);
}

void	print_philosopher(char *message, t_philo *philosophers)
{
	size_t	time;
	
	pthread_mutex_lock(&philosophers->data->write_lock);
	time = get_current_time() - philosophers->start_time;
	if (!dead_loop(philosophers))
	printf("%zu %d %s\n", time, philosophers->id, message);
	pthread_mutex_unlock(&philosophers->data->write_lock);
}
