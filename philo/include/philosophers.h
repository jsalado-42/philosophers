/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_of_philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalado- <jsalado-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:18:11 by jsalado-          #+#    #+#             */
/*   Updated: 2025/02/04 10:17:22 by jsalado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>
# include "./libft/libft.h"

# define SIM_NOT_INIT "The simulation could not be initialized"
# define FORK_TAKEN "has taken a fork"

typedef struct s_details {
	int				philo_nb;
	
	time_t			time_to_die;
	int				died;

	time_t			t_eat;
	int				eating;

	time_t			time_to_sleep;
	
	time_t			t_think;
	int				finish;
	
	time_t			t_start;
	pthread_mutex_t	*mutex;
} t_details;

typedef struct s_philosopher
{
	int				id;
	time_t			last_meal;
	int				time_ate;
	int				f[2];
	
	pthread_mutex_t	*fork;
	t_details		*details;
} t_philo;


typedef enum e_mutexes
{
	M_PRINT,
	M_EATING,
	M_FINISHED,
	M_DIED,
	M_NUM
}					t_mutexes;

// Actions
int		take_fork(char s, int a, int b);
int		ft_eating(t_philo *philosopher);
int		ph_died(t_philo *philosopher, int n);
int		ft_philosopher_finished(t_philo *philosopher, int n);
void	ft_finish_eating(t_philo *philosopher);

// Checker
int		ft_isdigitstr(char *str);
int		ft_check_args(int ac, char **av);
int		ft_are_done(t_philo *number_of_philosophers, t_details *details);
void	ft_check_stop_routine(t_philo *philosophers, t_details *details);

// Free
void	destroy_mutexes(t_philo *number_of_philosophers, t_details *details);
void	ft_kill_philos(t_philo *number_of_philosophers, t_details *details);

// Init
int	ft_init_details_mutexes(t_details **details);
int	ft_init_details(t_details **details, int ac, char **av);
int	ft_init_philo(t_philo **number_of_philosophers, t_details *details);
int	ft_init_program(t_philo **number_of_philosophers, t_details **details, int ac, char **av);

// Philosopher
void	*ft_philo_routine(void *args);

// Printer
int		print_usage(void);
int		ft_error(char *str);
void	ft_print_philosopher(t_philo *philosopher, char *str);

// Time
time_t	get_time(void);
void	ft_sleep(time_t ms);

#endif
