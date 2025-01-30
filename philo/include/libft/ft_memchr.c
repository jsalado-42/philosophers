/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalado- <jsalado-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:42:21 by jsalado-          #+#    #+#             */
/*   Updated: 2024/12/10 18:27:21 by jsalado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	char			*p;
	unsigned char	uc;
	unsigned char	ucc;

	p = (char *)s;
	i = 0;
	ucc = (unsigned char)c;
	while (i < n)
	{
		uc = (unsigned char)p[i];
		if (uc == ucc)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}
