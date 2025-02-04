/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalado- <jsalado-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:13:57 by jsalado-          #+#    #+#             */
/*   Updated: 2025/02/04 15:33:56 by jsalado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_isdigitstr(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (!str[i])
		return (1);
	return (0);
}

void	ft_check_stop_routine(t_philo *philosophers, t_details *details)
{
	int		i;
	time_t	last_meal;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&details->mutex[M_EATING]);
		last_meal = philosophers[i].last_meal;
		pthread_mutex_unlock(&details->mutex[M_EATING]);
		if (last_meal && ft_are_done(philosophers, details))
		{
			ft_philosopher_finished(philosophers, 1);
			break ;
		}
		if (last_meal && get_time() - last_meal > details->time_to_die)
		{
			ph_died(philosophers, 1);
			ft_print_philosopher(&philosophers[i], "died");
			break ;
		}
		i = (i + 1) % details->philo_nb;
		usleep(200);
	}
	return ;
}

int	ft_are_done(t_philo *number_of_philosophers, t_details *details)
{
	int	i;
	int	done;
	int	time_ate;

	if (details->eating == -1)
		return (0);
	i = -1;
	done = -1;
	while (++i < details->philo_nb)
	{
		pthread_mutex_lock(&number_of_philosophers->details->mutex[M_EATING]);
		time_ate = number_of_philosophers[i].time_ate;
		pthread_mutex_unlock(&number_of_philosophers->details->mutex[M_EATING]);
		if (time_ate >= details->eating)
			if (++done == details->philo_nb - 1)
				return (1);
		usleep(50);
	}
	return (0);
}

int	ft_check_args(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (ft_error("Invalid arguments"));
	if ((ac == 6 && ft_atoi(av[5]) == 0) || ft_atoi(av[1]) == 0)
		return (1);
	while (ac-- > 1)
	{
		if (!ft_isdigitstr(av[ac]))
			return (ft_error("Invalid number type"));
		if (ft_atoi(av[ac]) < 0 || ft_atoi(av[ac]) > INT_MAX)
			return (ft_error("Invalid number type"));
	}
	return (0);
}
