/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalado- <jsalado-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:36:07 by jsalado-          #+#    #+#             */
/*   Updated: 2024/12/10 13:23:10 by jsalado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*new_src;
	size_t	len_dst;
	size_t	len_src;
	size_t	i;
	size_t	result;

	new_src = (char *)src;
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(new_src);
	result = 0;
	i = 0;
	if (size > len_dst)
		result = len_src + len_dst;
	else
		result = len_src + size;
	while (new_src[i] && (len_dst + 1) < size)
	{
		dst[len_dst] = new_src[i];
		len_dst++;
		i++;
	}
	dst[len_dst] = 0;
	return (result);
}
