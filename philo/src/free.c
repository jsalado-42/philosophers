/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalado- <jsalado-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:15:32 by jsalado-          #+#    #+#             */
/*   Updated: 2025/02/05 13:33:07 by jsalado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_kill_philos(t_philo *philos, t_details *details)
{
	if (details && details->mutex)
		free(details->mutex);
	if (details)
		free(details);
	if (philos && philos->fork)
		free(philos->fork);
	if (philos)
		free(philos);
	return ;
}

void	destroy_mutexes(t_philo *philos, t_details *details)
{
	int	i;

	i = 0;
	while (i < philos->details->philo_nb)
		pthread_mutex_destroy(&philos->fork[i++]);
	i = 0;
	while (i < M_NUM)
		pthread_mutex_destroy(&details->mutex[i++]);
}
