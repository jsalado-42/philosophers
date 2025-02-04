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

typedef struct s_details {
	int				number_of_philosophers;
	
	time_t			time_to_die;
	int				died;

	time_t			time_to_eat;
	int				eating;

	time_t			time_to_sleep;
	
	time_t			time_to_think;
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
} t_philosopher;


typedef enum e_mutexes
{
	M_PRINT,
	M_EATING,
	M_FINISHED,
	M_DIED,
	M_NUM
}					t_mutexes;

// void	asdprint(char *str);

#endif
