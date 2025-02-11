/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalado- <jsalado-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:15:10 by jsalado-          #+#    #+#             */
/*   Updated: 2025/02/05 14:37:42 by jsalado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*ft_routine(void *args)
{
	t_philo	*philosophers;

	philosophers = (t_philo *)args;
	if (philosophers->id % 2)
	{
		ft_print_philosopher(philosophers, IS_THINKING);
		ft_sleep(philosophers->details->t_eat);
	}
	while (1)
	{
		if (ph_died(philosophers, 0))
			break ;
		if (ft_eating(philosophers))
			break ;
		ft_print_philosopher(philosophers, IS_THINKING);
		ft_sleep(philosophers->details->t_think);
	}
	return (NULL);
}
