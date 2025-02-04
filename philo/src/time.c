/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalado- <jsalado-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:14:08 by jsalado-          #+#    #+#             */
/*   Updated: 2025/02/04 15:31:39 by jsalado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

time_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		ft_error("\ngettimeofday()\n");
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_sleep(time_t ms)
{
	time_t	time;

	time = get_time();
	while (get_time() - time < ms)
		usleep(ms * 10);
}
