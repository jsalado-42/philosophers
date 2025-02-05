/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalado- <jsalado-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:13:25 by jsalado-          #+#    #+#             */
/*   Updated: 2025/02/05 11:30:38 by jsalado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_print_philosopher(t_philo *ph, char *str)
{
	int		ph_id;
	time_t	time;

	ph_id = ph->id + 1;
	time = get_time() - ph->details->t_start;
	pthread_mutex_lock(&ph->details->mutex[M_PRINT]);
	if (ft_strcmp(str, "died") == 0)
	{
		ft_printf("Philosopher %2i %s at %4li", ph_id, str, time);
	}
	if (!ph_died(ph, 0) && ft_philosopher_finished(ph, 0))
	{
		if (ft_strcmp(str, "has taken the fork") == 0 && time > 9999)
			printf("At %04li, philosopher %.2i %s\n", time, ph_id, str);
		else if (ft_strcmp(str, "has taken the fork") == 0)
			printf("At %04li, philosopher %.2i %s\n", time, ph_id, str);
		if (ft_strcmp(str, "is eating") == 0)
			printf("At %.4li, philosopher %.2i %s\n", time, ph_id, str);
		if (ft_strcmp(str, "is sleeping") == 0)
			printf("At %.4li, philosopher %.2i %s\n", time, ph_id, str);
		if (ft_strcmp(str, "is thinking") == 0)
			printf("At %.4li, philosopher %.2i %s\n", time, ph_id, str);
	}
	pthread_mutex_unlock(&ph->details->mutex[M_PRINT]);
}

int	print_usage(void)
{
	printf("                 ╔══════════════╗\n");
	printf(" ╔═══════════════╣    Usage     ╠═══════════════╗\n");
	printf(" ║               ╚══════════════╝               ║\n");
	printf(" ║ example:\t\t\t\t\t║\n");
	printf(" ║ ./philo \033[36m2\033[0m \033[31m400\033[0m \033[32m200\033[0m");
	printf(" \033[35m200\033[0m \033[33m3\033[0m\t\t\t║\n");
	printf(" ║\t\t\t\t\t\t║\n");
	printf(" ║ explain:\t\t\t\t\t║\n");
	printf(" ║\t     \033[36mav[1]\033[0m - number_of_philosophers\t║\n");
	printf(" ║\t     \033[31mav[2]\033[0m - time_to_die\t\t║\n");
	printf(" ║\t     \033[32mav[3]\033[0m - time_to_eat\t\t║\n");
	printf(" ║\t     \033[35mav[4]\033[0m - time_to_sleep\t\t║\n");
	printf(" ║ \033[33m(optional)av[5]\033[0m - must_eat\t\t\t║\n");
	printf(" ║\t\t\t\t\t\t║\n");
	printf(" ╚══════════════════════════════════════════════╝\n\n");
	return (1);
}

int	ft_error(char *str)
{
	ft_printf("\nError:\n%s\n", str);
	print_usage();
	return (1);
}
