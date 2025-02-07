/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalado- <jsalado-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:50:39 by jsalado-          #+#    #+#             */
/*   Updated: 2025/02/05 11:51:10 by jsalado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ph_died(t_philo *philosopher, int n)
{
	pthread_mutex_lock(&philosopher->details->mutex[M_DIED]);
	if (n)
		philosopher->details->died = 1;
	if (philosopher->details->died)
	{
		pthread_mutex_unlock(&philosopher->details->mutex[M_DIED]);
		return (1);
	}
	pthread_mutex_unlock(&philosopher->details->mutex[M_DIED]);
	return (0);
}

int	ft_philosopher_finished(t_philo *philosopher, int n)
{
	pthread_mutex_lock(&philosopher->details->mutex[M_FINISHED]);
	if (n)
		philosopher->details->finish = 1;
	if (philosopher->details->finish)
	{
		pthread_mutex_unlock(&philosopher->details->mutex[M_FINISHED]);
		return (1);
	}
	pthread_mutex_unlock(&philosopher->details->mutex[M_FINISHED]);
	return (0);
}

int	ft_eating(t_philo *ph)
{
	pthread_mutex_lock(&ph->fork[take_fork('m', ph->f[0], ph->f[1])]);
	ft_print_philosopher(ph, HAS_TAKEN_FORK);
	if (ph->f[0] == ph->f[1])
	{
		pthread_mutex_unlock(&ph->fork[take_fork('m', ph->f[0], ph->f[1])]);
		return (1);
	}
	pthread_mutex_lock(&ph->fork[take_fork('M', ph->f[0], ph->f[1])]);
	ft_print_philosopher(ph, HAS_TAKEN_FORK);
	ft_print_philosopher(ph, IS_EATING);
	pthread_mutex_lock(&ph->details->mutex[M_EATING]);
	ph->last_meal = get_time();
	ph->time_ate++;
	pthread_mutex_unlock(&ph->details->mutex[M_EATING]);
	if (ft_philosopher_finished(ph, 0))
		return (ft_finish_eating(ph), 1);
	ft_sleep(ph->details->eating);
	ft_finish_eating(ph);
	return (0);
}
