/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalado- <jsalado-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:18:34 by jsalado-          #+#    #+#             */
/*   Updated: 2025/02/04 14:03:13 by jsalado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

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

static int	ft_isdigitstr(char *str)
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

static int	ft_check_args(int ac, char **av)
{
	if (ac < 5 ||  ac > 6)
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

time_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		ft_error("\ngettimeofday()\n");
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_philosopher_died(t_philosopher *philosopher, int n)
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

int	ft_philosopher_finished(t_philosopher *philosopher, int n)
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

void	ft_print_philosopher(t_philosopher *philosopher, char *str)
{
	int		philosopher_id;
	time_t	time;

	philosopher_id = philosopher->id + 1;
	time = get_time() - philosopher->details->t_start;
	pthread_mutex_lock(&philosopher->details->mutex[M_PRINT]);
	if (ft_strcmp(str, "died") == 0)
	{
		ft_printf("Philosopher %2i %s at %4li", philosopher_id, str, time);
	}
	if (!ft_philosopher_died(philosopher, 0) && !ft_philosopher_finished(philosopher, 0))
	{
		if (ft_strcmp(str, "has taken the fork") == 0 && time > 9999)
			printf("At %04li, philosopher %.2i %s\n", time, philosopher_id, str);
		else if (ft_strcmp(str, "has taken the fork") == 0)
			printf("At %04li, philosopher %.2i %s\n", time, philosopher_id, str);
		if (ft_strcmp(str, "is eating") == 0)
			printf("At %.4li, philosopher %.2i %s\n", time, philosopher_id, str);
		if (ft_strcmp(str, "is sleeping") == 0)
			printf("At %.4li, philosopher %.2i %s\n", time, philosopher_id, str);
		if (ft_strcmp(str, "is thinking") == 0)
			printf("At %.4li, philosopher %.2i %s\n", time, philosopher_id, str);
	}
	pthread_mutex_unlock(&philosopher->details->mutex[M_PRINT]);
}

void	ft_sleep(time_t ms)
{
	time_t	time;

	time = get_time();
	while (get_time() - time < ms)
		usleep(ms * 10);
}

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



int	ft_are_done(t_philosopher *number_of_philosophers, t_details *details)
{
	int	i;
	int	done;
	int	time_ate;

	if (details->eating == -1)
		return (0);
	i = -1;
	done = -1;
	while (++i < details->number_of_philosophers)
	{
		pthread_mutex_lock(&number_of_philosophers->details->mutex[M_EATING]);
		time_ate = number_of_philosophers[i].time_ate;
		pthread_mutex_unlock(&number_of_philosophers->details->mutex[M_EATING]);
		if (time_ate >= details->eating)
			if (++done == details->number_of_philosophers - 1)
				return (1);
		usleep(50);
	}
	return (0);
}

void	ft_finish_eating(t_philosopher *philosopher)
{
	pthread_mutex_unlock(&philosopher->fork[take_fork('M', philosopher->f[0], philosopher->f[1])]);
	pthread_mutex_unlock(&philosopher->fork[take_fork('m', philosopher->f[0], philosopher->f[1])]);
	ft_print_philosopher(philosopher, "is sleeping");
	ft_sleep(philosopher->details->time_to_think);
}

int	ft_eating(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->fork[take_fork('m', philosopher->f[0], philosopher->f[1])]);
	ft_print_philosopher(philosopher, "has taken a fork");
	if (philosopher->f[0] == philosopher->f[1])
	{
		pthread_mutex_unlock(&philosopher->fork[take_fork('m', philosopher->f[0], philosopher->f[1])]);
		return (1);
	}
	pthread_mutex_lock(&philosopher->fork[take_fork('M', philosopher->f[0], philosopher->f[1])]);
	ft_print_philosopher(philosopher, "has taken a fork");
	ft_print_philosopher(philosopher, "is eating");
	pthread_mutex_lock(&philosopher->details->mutex[M_EATING]);
	philosopher->last_meal = get_time();
	philosopher->time_ate++;
	pthread_mutex_unlock(&philosopher->details->mutex[M_EATING]);
	if (ft_philosopher_finished(philosopher, 0))
		return (ft_finish_eating(philosopher), 1);
	ft_sleep(philosopher->details->eating);
	return (ft_finish_eating(philosopher), 0);
}


void	*ft_philosopher_routine(void *args)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)args;
	if (philosopher->id % 2)
	{
		ft_print_philosopher(philosopher, "is thinking");
		ft_sleep(philosopher->details->time_to_eat);
	}
	while (1)
	{
		if (ft_philosopher_died(philosopher, 0))
			break ;
		if (ft_eating(philosopher))
			break ;
		ft_print_philosopher(philosopher, "is thinking");
		ft_sleep(philosopher->details->time_to_think);
	}
	return (NULL);
}


void	ft_check_stop_routine(t_philosopher *philosophers, t_details *details)
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
			ft_philosopher_died(philosophers, 1);
			ft_print_philosopher(&philosophers[i], "died");
			break ;
		}
		i = (i + 1) % details->number_of_philosophers;
		usleep(200);
	}
	return ;
}

 void	destroy_mutexes(t_philosopher *number_of_philosophers, t_details *details)
{
	int	i;

	i = 0;
	while (i < number_of_philosophers->details->number_of_philosophers)
		pthread_mutex_destroy(&number_of_philosophers->fork[i++]);
	i = 0;
	while (i < M_NUM)
		pthread_mutex_destroy(&details->mutex[i++]);
}

int	ft_simulation(t_philosopher *philosopher, t_details *details)
{
	int			i;
	pthread_t	*thread;

	thread = malloc(sizeof(pthread_t) * (size_t)details->number_of_philosophers);
	if (!thread)
		return (1);
	i = -1;
	while (++i < details->number_of_philosophers)
	{
		if (pthread_create(&thread[i], NULL, ft_philosopher_routine, &philosopher[i]))
		{
			while (i--)
				pthread_join(thread[i], NULL);
			free(thread);
			return (1);
		}
	}
	ft_check_stop_routine(philosopher, details);
	i = -1;
	while (++i < details->number_of_philosophers)
		if (pthread_join(thread[i], NULL))
			return (1);
	return (destroy_mutexes(philosopher, details), free(thread), 0);
}

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

int	ft_init_details(t_details **details, int ac, char **av)
{
	(*details)->number_of_philosophers = ft_atoi(av[1]);
	(*details)->time_to_die = ft_atoi(av[2]);
	(*details)->time_to_eat = ft_atoi(av[3]);
	(*details)->time_to_think = ft_atoi(av[4]);
	(*details)->eating = 0;
	if (ac == 6)
		(*details)->eating = ft_atoi(av[5]);
	(*details)->t_start = get_time();
	(*details)->time_to_think = 0;
	if (((*details)->number_of_philosophers % 2 == 0) && (*details)->time_to_eat > (*details)->time_to_think)
		(*details)->time_to_think = (*details)->time_to_eat - (*details)->time_to_think;
	(*details)->finish = 0;
	(*details)->died = 0;
	if (ft_init_details_mutexes(details))
		return (1);
	return (0);
}

void	ft_free_philosophers(t_philosopher *number_of_philosophers, t_details *details)
{
	if (details && details->mutex)
		free(details->mutex);
	if (details)
		free(details);
	if (number_of_philosophers && number_of_philosophers->fork)
		free(number_of_philosophers->fork);
	if (number_of_philosophers)
		free(number_of_philosophers);
	return ;
}
int	ft_init_philo(t_philosopher **number_of_philosophers, t_details *details)
{
	pthread_mutex_t	*fork;
	int				i;

	fork = malloc(sizeof(pthread_mutex_t) * ((size_t)details->number_of_philosophers));
	if (fork == NULL)
		return (1);
	i = 0;
	while (i < details->number_of_philosophers)
		pthread_mutex_init(&fork[i++], NULL);
	i = -1;
	while (++i < details->number_of_philosophers)
	{
		(*number_of_philosophers)[i].id = i;
		(*number_of_philosophers)[i].last_meal = details->t_start;
		(*number_of_philosophers)[i].time_ate = 0;
		(*number_of_philosophers)[i].f[0] = i;
		(*number_of_philosophers)[i].f[1] = (i + 1) % details->number_of_philosophers;
		(*number_of_philosophers)[i].fork = fork;
		(*number_of_philosophers)[i].details = details;
	}
	return (0);
}

int	ft_init_program(t_philosopher **number_of_philosophers, t_details **details, int ac, char **av)
{
	*details = (t_details *)malloc(sizeof(t_details));
	if (!*details)
		return (1);
	(*details)->mutex = NULL;
	if (ft_init_details(details, ac, av) != 0)
		return (1);
	*number_of_philosophers = (t_philosopher *)malloc(sizeof(t_philosopher) * (size_t)(*details)->number_of_philosophers);
	if (!*number_of_philosophers)
		return (1);
	(*number_of_philosophers)->fork = NULL;
	if (ft_init_philo(number_of_philosophers, *details) != 0)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_details		*details;
	t_philosopher	*number_of_philosophers;

	if (ft_check_args(ac, av))
		return (EXIT_FAILURE);
	if (ft_init_program(&number_of_philosophers, &details, ac, av))
		return (ft_free_philosophers(number_of_philosophers, details), ft_error("The simulation could not be initialized"));
	if (ft_simulation(number_of_philosophers, details))
		return (ft_free_philosophers(number_of_philosophers, details), ft_error("The simulation could not be initialized"), 1);
	ft_free_philosophers(number_of_philosophers, details);
	return (0);
}
