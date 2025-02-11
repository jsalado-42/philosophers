/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalado- <jsalado-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:15:53 by jsalado-          #+#    #+#             */
/*   Updated: 2025/02/05 14:45:14 by jsalado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_init_details_mutexes(t_details **details)
{
	int	i;

	(*details)->mutex = malloc(sizeof(pthread_mutex_t) * ((size_t)M_NUM));
	if ((*details)->mutex == NULL)
		return (1);
	i = 0;
	while (i < M_NUM)
		pthread_mutex_init(&(*details)->mutex[i++], NULL);
	return (0);
}

int	ft_init_details(t_details **dt, int ac, char **av)
{
	(*dt)->philo_nb = ft_atoi(av[1]);
	(*dt)->time_to_die = ft_atoi(av[2]);
	(*dt)->t_eat = ft_atoi(av[3]);
	(*dt)->t_think = ft_atoi(av[4]);
	(*dt)->t_eat = -1;
	if (ac == 6)
		(*dt)->t_eat = ft_atoi(av[5]);
	(*dt)->t_start = get_time();
	(*dt)->t_think = 0;
	if (((*dt)->philo_nb % 2 == 0) && (*dt)->t_eat > (*dt)->t_sleep)
		(*dt)->t_think = (*dt)->t_eat - (*dt)->t_sleep;
	(*dt)->finish = 0;
	(*dt)->died = 0;
	if (ft_init_details_mutexes(dt))
		return (1);
	return (0);
}

int	ft_init_philo(t_philo **philos, t_details *details)
{
	pthread_mutex_t	*fork;
	int				i;

	fork = malloc(sizeof(pthread_mutex_t) * ((size_t)details->philo_nb));
	if (fork == NULL)
		return (1);
	i = 0;
	while (i < details->philo_nb)
		pthread_mutex_init(&fork[i++], NULL);
	i = -1;
	while (++i < details->philo_nb)
	{
		(*philos)[i].id = i;
		(*philos)[i].last_meal = details->t_start;
		(*philos)[i].time_ate = 0;
		(*philos)[i].f[0] = i;
		(*philos)[i].f[1] = (i + 1) % details->philo_nb;
		(*philos)[i].fork = fork;
		(*philos)[i].details = details;
	}
	return (0);
}

int	ft_init_program(t_philo **philo_nb, t_details **dt, int ac, char **av)
{
	*dt = (t_details *)malloc(sizeof(t_details));
	if (!*dt)
		return (1);
	(*dt)->mutex = NULL;
	if (ft_init_details(dt, ac, av) != 0)
		return (1);
	*philo_nb = (t_philo *)malloc(sizeof(t_philo) * (size_t)(*dt)->philo_nb);
	if (!*philo_nb)
		return (1);
	(*philo_nb)->fork = NULL;
	if (ft_init_philo(philo_nb, *dt) != 0)
		return (1);
	return (0);
}
