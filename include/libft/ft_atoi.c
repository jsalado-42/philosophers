/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalado- <jsalado-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:28:32 by jsalado-          #+#    #+#             */
/*   Updated: 2024/12/11 11:14:54 by jsalado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v'
		|| c == 32)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	is_positive;
	int	counter;
	int	result;

	result = 0;
	counter = 0;
	is_positive = 1;
	while (ft_isspace(str[counter]))
		counter++;
	if (str[counter] == '-' || str[counter] == '+')
	{
		if (str[counter] == '-')
			is_positive = -1;
		counter++;
	}
	while (ft_isdigit(str[counter]))
	{
		result = result * 10 + (str[counter] - '0');
		counter++;
	}
	return (result * is_positive);
}
