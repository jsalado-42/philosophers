/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalado- <jsalado-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:25:59 by jsalado-          #+#    #+#             */
/*   Updated: 2025/02/12 14:39:58 by jsalado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_arguments(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
			if (av[i][j] < '0' || av[i][j] > '9')
				return (EXIT_FAILURE);
	}
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > 200 || ft_atoi(av[2]) == 0
		|| ft_atoi(av[3]) == 0 || ft_atoi(av[4]) == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void init_structs(t_data *data, t_philo *philos, char **av, int i)
{
	data->is_dead = 0;
	data->total_philosophers = ft_atoi(av[1]);
	data->necessary_meals = -1;
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	while (++i < data->total_philosophers)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = get_current_time();
		philos[i].start_time = get_current_time();
		philos[i].time_to_die = ft_atoi(av[2]);
		philos[i].time_to_eat = ft_atoi(av[3]);
		philos[i].time_to_sleep = ft_atoi(av[4]);
		philos[i].l_fork = &data->forks[i];
		if (i == 0)
			philos[i].r_fork = &data->forks[data->total_philosophers - 1];
		else
			philos[i].r_fork = &data->forks[i - 1];
		philos[i].data = data;
	}
}

static void	destroy_mutex(t_philo *philosophers, int flag)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&philosophers->data->write_lock);
	pthread_mutex_destroy(&philosophers->data->meal_lock);
	pthread_mutex_destroy(&philosophers->data->dead_lock);
	while (++i < philosophers->data->total_philosophers)
		pthread_mutex_destroy(&philosophers->data->forks[i]);
	if (flag == 1)
		printf(E_THREAD_CREATION);
	if (flag == 2)
		printf(E_THREAD_CREATION_PHILO);
	if (flag == 3)
		printf(E_THREAD_JOINING);
	if (flag == 1)
		printf(E_THREAD_JOINING_PHILO);
}

static void	threads(t_philo *ps)
{
	pthread_t	waiter;
	int			i;

	i = -1;
	if (pthread_create(&waiter, NULL, &waiting, ps) != 0)
		destroy_mutex(ps, 1);
	while (++i < ps->data->total_philosophers)
		if (pthread_create(&ps[i].thread, NULL, &p_routine, &ps[i]) != 0)
			destroy_mutex(ps, 2);
	i = -1;
	while (++i < ps->data->total_philosophers)
		if (pthread_join(ps[i].thread, NULL) != 0)
			destroy_mutex(ps, 3);
	if (pthread_join(waiter, NULL) != 0)
		destroy_mutex(ps, 4);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	philosophers[PHIL_MAX];

	if (ac < 5 || ac > 6 || check_arguments(av) == 1)
		return (printf(E_ARGS_NUMBER_INVALID), EXIT_FAILURE);
	init_structs(&data, philosophers, av, -1);
	if (ac == 6)
		data.necessary_meals = ft_atoi(av[5]);
	threads(philosophers);
	destroy_mutex(philosophers, 0);		
}