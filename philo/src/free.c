/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalado- <jsalado-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:15:32 by jsalado-          #+#    #+#             */
/*   Updated: 2025/02/04 15:34:44 by jsalado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	destroy_mutexes(t_philo *number_of_philosophers, t_details *details)
{
	int	i;

	i = 0;
	while (i < number_of_philosophers->details->philo_nb)
		pthread_mutex_destroy(&number_of_philosophers->fork[i++]);
	i = 0;
	while (i < M_NUM)
		pthread_mutex_destroy(&details->mutex[i++]);
}

void	ft_kill_philos(t_philo *number_of_philosophers, t_details *details)
{
	if (details && details->mutex)
		free(details->mutex);
	if (details)
		free(details);
	if (number_of_philosophers && number_of_philosophers->fork)
		free(number_of_philosophers->fork);
	if (number_of_philosophers)
		free(number_of_philosophers);
	return ;
}
