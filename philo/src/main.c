/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalado- <jsalado-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:18:34 by jsalado-          #+#    #+#             */
/*   Updated: 2025/02/05 11:40:02 by jsalado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	ft_simulation(t_philo *philos, t_details *details)
{
	int			i;
	pthread_t	*thread;

	thread = malloc(sizeof(pthread_t) * (size_t)details->philo_nb);
	if (!thread)
		return (1);
	i = -1;
	while (++i < details->philo_nb)
	{
		if (pthread_create(&thread[i], NULL, ft_philo_routine, &philos[i]))
		{
			while (i--)
				pthread_join(thread[i], NULL);
			free(thread);
			return (1);
		}
	}
	ft_check_stop_routine(philos, details);
	i = -1;
	while (++i < details->philo_nb)
		if (pthread_join(thread[i], NULL))
			return (1);
	return (destroy_mutexes(philos, details), free(thread), 0);
}

int	main(int ac, char **av)
{
	t_details		*details;
	t_philo			*philo_nb;

	if (ft_check_args(ac, av))
		return (EXIT_FAILURE);
	if (ft_init_program(&philo_nb, &details, ac, av))
	{
		ft_kill_philos(philo_nb, details);
		ft_error(SIM_NOT_INIT);
		return (1);
	}
	if (ft_simulation(philo_nb, details))
	{
		ft_kill_philos(philo_nb, details);
		ft_error(SIM_NOT_INIT);
		return (1);
	}
	ft_kill_philos(philo_nb, details);
	return (0);
}
