/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalado- <jsalado-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:15:10 by jsalado-          #+#    #+#             */
/*   Updated: 2025/02/04 15:34:07 by jsalado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*ft_philo_routine(void *args)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)args;
	if (philosopher->id % 2)
	{
		ft_print_philosopher(philosopher, "is thinking");
		ft_sleep(philosopher->details->t_eat);
	}
	while (1)
	{
		if (ph_died(philosopher, 0))
			break ;
		if (ft_eating(philosopher))
			break ;
		ft_print_philosopher(philosopher, "is thinking");
		ft_sleep(philosopher->details->t_think);
	}
	return (NULL);
}
