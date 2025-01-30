/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalado- <jsalado-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:08:15 by jsalado-          #+#    #+#             */
/*   Updated: 2024/12/19 12:34:32 by jsalado-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*clean_vault(char *vault)
{
	char	*new_vault;
	char	*ptr;
	int		i;

	ptr = ft_strchr(vault, '\n');
	if (!ptr)
	{
		new_vault = NULL;
		return (ft_free(&vault));
	}
	else
		i = (ptr - vault) + 1;
	if (!vault[i])
		return (ft_free(&vault));
	new_vault = ft_substr(vault, i, ft_strlen(vault) - i);
	ft_free(&vault);
	if (!new_vault)
		return (NULL);
	return (new_vault);
}

char	*create_new_line(char *vault)
{
	char	*line;
	char	*ptr;
	int		len;

	ptr = ft_strchr(vault, '\n');
	len = (ptr - vault) + 1;
	line = ft_substr(vault, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

char	*read_buffer(int fd, char *vault)
{
	int		r;
	char	*buffer;

	r = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free(&buffer));
	buffer[0] = '\0';
	while (r > 0 && !ft_strchr(buffer, '\n'))
	{
		r = read(fd, buffer, BUFFER_SIZE);
		if (r > 0)
		{
			buffer[r] = 0;
			vault = ft_strjoin(vault, buffer);
		}
	}
	free(buffer);
	if (r == -1)
		return (ft_free(&vault));
	return (vault);
}

char	*get_next_line(int fd)
{
	static char	*vault;
	char		*line;

	if (fd < 0)
		return (NULL);
	if ((vault && !ft_strchr(vault, '\n')) || !vault)
		vault = read_buffer(fd, vault);
	if (!vault)
		return (NULL);
	line = create_new_line(vault);
	if (!line)
		return (ft_free(&vault));
	vault = clean_vault(vault);
	return (line);
}
