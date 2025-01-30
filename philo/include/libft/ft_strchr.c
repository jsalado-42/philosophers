/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalado- <jsalado-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:54:55 by jsalado-          #+#    #+#             */
/*   Updated: 2024/12/10 19:12:31 by jsalado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	nc;
	int		i;

	i = 0;
	nc = (char)c;
	while (s[i])
	{
		if (s[i] == nc)
			return ((char *)&s[i]);
		i++;
	}
	if (nc == 0)
		return ((char *)&s[i]);
	return (0);
}
