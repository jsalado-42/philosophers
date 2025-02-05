/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalado- <jsalado-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:13:00 by jsalado-          #+#    #+#             */
/*   Updated: 2025/02/05 11:59:02 by jsalado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	take_fork(char s, int a, int b)
{
	if (s == 'M')
	{
		if (a > b)
			return (a);
		return (b);
	}
	else
	{
		if (a < b)
			return (a);
		return (b);
	}
}

void	ft_finish_eating(t_philo *ph)
{
	pthread_mutex_unlock(&ph->fork[take_fork('M', ph->f[0], ph->f[1])]);
	pthread_mutex_unlock(&ph->fork[take_fork('m', ph->f[0], ph->f[1])]);
	ft_print_philosopher(ph, IS_SLEEPING);
	ft_sleep(ph->details->t_think);
}

void	ft_sleep(time_t ms)
{
	time_t	time;

	time = get_time();
	while (get_time() - time < ms)
		usleep(ms * 10);
}
