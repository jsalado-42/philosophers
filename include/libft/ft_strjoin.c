/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalado- <jsalado-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 10:52:50 by jsalado-          #+#    #+#             */
/*   Updated: 2025/01/27 15:10:16 by jsalado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	len;
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	result = (char *)malloc(len + 1);
	if (!result)
		return (0);
	while (s1[x])
	{
		result[x] = s1[x];
		x++;
	}
	while (s2[y])
	{
		result[x + y] = s2[y];
		y++;
	}
	result[x + y] = 0;
	return (result);
}
