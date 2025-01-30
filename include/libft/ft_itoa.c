/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalado- <jsalado-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:15:54 by jsalado-          #+#    #+#             */
/*   Updated: 2024/12/10 19:35:35 by jsalado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_num_length(long int n)
{
	int	x;

	x = 0;
	while (n > 9)
	{
		n /= 10;
		x++;
	}
	return (x + 1);
}

char	*ft_itoa(int n)
{
	int			i;
	long int	li;
	char		*result;

	li = n;
	if (n < 0)
		li = -li;
	i = ft_num_length(li);
	if (n < 0)
		i++;
	result = (char *)malloc((i + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[i--] = 0;
	while (i >= 0)
	{
		result[i--] = (li % 10) + '0';
		li /= 10;
	}
	if (n < 0)
		result[0] = '-';
	return (result);
}
